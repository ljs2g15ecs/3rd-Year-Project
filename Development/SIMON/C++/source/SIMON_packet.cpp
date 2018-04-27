#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

U_64	PACKET::inputCount = 0;
U_64	PACKET::outputCount = 0;

//	CONSTUCTORS
PACKET::PACKET()
{
	flush();
}

///*
PACKET::PACKET(_INFO_ x) : PACKET()
{
	input();
	assign(x);
}
//*/

//	MUTATORS
void		PACKET::input	(								)
{
	iDATA.mode = MODE;
	iDATA.in_out = 0;
	iDATA.data_key = 0;	//	DEFAULT
	iDATA.enc_dec = 0;	//	DEFAULT
	iDATA.nBlocks = 0;	//	DEFAULT
	count = inputCount++;
}

void		PACKET::output	(	_INFO_	x					)
{
	iDATA = x;
	iDATA.in_out = 1;		//	CHANGE TO OUPUT
	count = outputCount++;
}

/*
void		PACKET::assign	(	_PACKET_	x				)
{
	pDATA = x;
	return;
}
//*/

void		PACKET::assign	(	_INFO_	x					)
{
	iDATA = x;
	return;
}

void		PACKET::assign	(	WORD	x,	TYPE(8)	i		)
{
	wDATA[i] = x;
	return;
}

/*
void		PACKET::assign	(	TYPE(N)	x,	TYPE(8)	i		)
{
	wDATA[i] = x;
	return;
}
//*/

TYPE(8)		PACKET::addWORD	(	WORD	x					)
{
	wDATA[nxtWORD++] = x;
	
	if( nxtWORD != 4 )	return 0;
	else
	{
		nxtWORD = 0;
		return 1;
	}
}

TYPE(8)		PACKET::addBLOCK(	BLOCK	x					)
{
	if(nxtBLOCK)
	{
		assign(x.get_w(0), 2);
		assign(x.get_w(1), 3);
		nxtBLOCK = 0;
		return 1;
	}
	else
	{
		assign(x.get_w(0), 0);
		assign(x.get_w(1), 1);
		nxtBLOCK = 1;
		return 0;
	}
	
}

/*
TYPE(8)		PACKET::addWORD	(	TYPE(N)	x					)
{
	wDATA[nxtWORD++] = x;
	
	if( nxtWORD != 4 )	return 0;
	else
	{
		nxtWORD = 0;
		return 1;
	}
}
//*/

void		PACKET::addKEY	(	KEY		x					)
{
#if (M==2)
	wDATA[0] = x.get_w(0);
	wDATA[1] = x.get_w(1);
	wDATA[2] = 0;
	wDATA[3] = 0;
#endif
#if (M==3)
	wDATA[0] = x.get_w(0);
	wDATA[1] = x.get_w(1);
	wDATA[2] = x.get_w(2);
	wDATA[3] = 0;
#endif
#if (M==4)
	wDATA[0] = x.get_w(0);
	wDATA[1] = x.get_w(1);
	wDATA[2] = x.get_w(2);
	wDATA[3] = x.get_w(3);
#endif
	iDATA.data_key = 1;
}

void		PACKET::pack	(								)
{
	TYPE(8) i;
	for(i=0; i<(2+(N/2)); i++)
	{
		pBYTES[i] = get_b(i);
	}
}

void		PACKET::flush	(								)
{
	nxtWORD = 0;
	nxtBLOCK = 0;
	iBYTE = 0;
	count = 0;
	
	wDATA[0].flush();
	wDATA[1].flush();
	wDATA[2].flush();
	wDATA[3].flush();
	
	return;
}

void		setCounts	(	U_64	x					)
{
	PACKET::inputCount = x;
	PACKET::outputCount = x;
	
	return;
}

void		setICount	(	U_64	x					)
{
	PACKET::inputCount = x;
	
	return;
}

void		setOCount	(	U_64	x					)
{
	PACKET::outputCount = x;
	
	return;
}

void		resetCounts	(								)
{
	PACKET::inputCount = 0;
	PACKET::outputCount = 0;
	
	return;
}

void		PresetICount	(								)
{
	PACKET::inputCount = 0;
	
	return;
}

void		resetOCount	(								)
{
	PACKET::outputCount = 0;
	
	return;
}

//	ACCESSORS
void		PACKET::test		(								)
{
	pack();
	cout 	<< setbase(10)\
			<< "|\tPACKET\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size() << "\t"\
			<< "|\t" << HEX_WORD() << "\t"\
			<< "|\t" << HEX_BYTES() << "\t" << "|" << endl\
			<< "|\t" << HEX_PKT() << "\t"\
			<< "|\t" << HEX_SV(0) << "\t"\
			<< "|" << endl << endl;
	
	return;
}

TYPE(8)		PACKET::checkIN		(	TYPE(16)	x					)
{
	if((!iDATA.in_out) & (iDATA.mode == MODE) & (count == x))
	{
		if(iDATA.data_key)	return 2;
		else				return 1;
	}
	else
	{
		cout << endl;
		cout << "<" << (TYPE(16))iDATA.in_out << ">\t";
		cout << "<" << (TYPE(16))iDATA.mode << " == " << (TYPE(16))MODE << ">\t";
		cout << "<" << (TYPE(16))count << " == " << x << ">" << endl;
		return 0;
	}
}

TYPE(8)		PACKET::get_b		(	TYPE(8)	i					)
{
	if		(	i == 0	)
	{
		return get_Ib();
	}
	else if	(	i == 1	)	
	{
		return get_c();
	}
	else if	(	i >= 2	)	
	{
		return wDATA[(i-2)/(N/8)].get_b((N/8)-1-(i-2)%(N/8));
	}
}

TYPE(16)		PACKET::get_B		(	TYPE(8)	i					)
{
	if		(	i == 0			)
	{
		return get_Ib();
	}
	else if	(	i == 1			)	
	{
		return get_c();
	}
	else if	(	i < (2+(N/2))	)	
	{
		return wDATA[i/(N/8)].get_b();
	}
}

_INFO_		PACKET::get_i		(								)
{
	return iDATA;
}

TYPE(8)		PACKET::get_Ib		(								)
{
	return iBYTE;
}

TYPE(16)	PACKET::get_IB		(								)
{
	return iBYTE;
}

TYPE(8)*	PACKET::get_p		(								)
{
	return pBYTES;
}

TYPE(8)		PACKET::get_c		(								)
{
	return count;
}

TYPE(16)	PACKET::get_C		(								)
{
	return count;
}

WORD		PACKET::get_w		(	TYPE(8)	i					)
{
	return wDATA[i];
}

TYPE(N)		PACKET::get_W		(	TYPE(8)	i					)
{
	return wDATA[i].get_v();
}

TYPE(8)		PACKET::get_Wb		(	TYPE(8)	i,	TYPE(8)	j		)
{
	return wDATA[i].get_b(j);
}

TYPE(16)	PACKET::get_WB		(	TYPE(8)	i,	TYPE(8)	j		)
{
	return wDATA[i].get_B(j);
}

BLOCK		PACKET::get_BLK		(	TYPE(8)	i					)
{
	if(i)	return BLOCK(wDATA[2], wDATA[3]);
	else	return BLOCK(wDATA[0], wDATA[1]);
}

TYPE(8)		PACKET::get_nxtW	(								)
{
	return nxtWORD;
}

U_64		PACKET::get_ICount	(								)
{
	return inputCount;
}

U_64		PACKET::get_OCount	(								)
{
	return outputCount;
}

TYPE(16)	PACKET::size		(								)
{
	return sizeof(iBYTE) + sizeof(count) + 4*wDATA[0].size_b();
}

string		PACKET::HEX_WORD	(								)
{
	stringstream ss;
	
	ss << "[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_IB();
	ss << "]-[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_C();
	ss << "]-[";
	ss << wDATA[0].HEX_WORD();
	ss << "-";
	ss << wDATA[1].HEX_WORD();
	ss << "-";
	ss << wDATA[2].HEX_WORD();
	ss << "-";
	ss << wDATA[3].HEX_WORD();
	ss << "]";
	
	return ss.str();
}

string		PACKET::CHR_BYTES(								)
{
	stringstream ss;
	
	ss << "[";
	ss << (get_Ib() > 0 ? get_Ib() : (TYPE(8))0xFE);
	ss << "]-[";
	ss << (get_Ib() > 0 ? get_c() : (TYPE(8))0xFE);
	ss << "]-[";
	ss << wDATA[0].CHR_BYTES();
	ss << "-";
	ss << wDATA[1].CHR_BYTES();
	ss << "-";
	ss << wDATA[2].CHR_BYTES();
	ss << "-";
	ss << wDATA[3].CHR_BYTES();
	ss << "]";
	
	return ss.str();
}

string		PACKET::HEX_BYTES(								)
{
	stringstream ss;
	
	ss << "[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_IB();
	ss << "]-[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_C();
	ss << "]-[";
	ss << wDATA[0].HEX_BYTES();
	ss << "-";
	ss << wDATA[1].HEX_BYTES();
	ss << "-";
	ss << wDATA[2].HEX_BYTES();
	ss << "-";
	ss << wDATA[3].HEX_BYTES();
	ss << "]";
	
	return ss.str();
}

string		PACKET::CHR		(								)
{
	stringstream ss;
	
	ss << (get_Ib() > 0 ? get_Ib() : (TYPE(8))0xFE);
	ss << (get_Ib() > 0 ? get_c() : (TYPE(8))0xFE);
	ss << wDATA[0].CHR_BYTES();
	ss << wDATA[1].CHR_BYTES();
	ss << wDATA[2].CHR_BYTES();
	ss << wDATA[3].CHR_BYTES();
	
	return ss.str();
}

string		PACKET::HEX_PKT	(								)
{
	stringstream ss;
	
	ss << "[";
	ss << hex << uppercase << setfill('0') << setw(2) << (TYPE(16))pBYTES[0];
	ss << "]-[";
	ss << hex << uppercase << setfill('0') << setw(2) << (TYPE(16))pBYTES[1];
	ss << "]-[";
	
	TYPE(64) i;
	for(i=2; i<size(); i++)
	{
		ss << hex << uppercase << setfill('0') << setw(2) << (TYPE(16))pBYTES[i];
		
		if(((i-2) % (N/8) == (N/8)-1) && (i != size()-1))		ss << "]-[";
		else if(((i-2) % (N/8) == (N/8)-1) && (i != size()-1))	ss << "-";
		else if(i != size()-1)									ss << ":";
	}
	
	ss << "]";
	
	return ss.str();
}

string		PACKET::HEX_SV	(	TYPE(64)	i				)
{
	stringstream ss;
	
	ss << "in[" << i << "]\t= " << (2+(N/2))*8 << "'h";
	ss << hex << uppercase << setfill('0') << setw(2) << (TYPE(16))pBYTES[0];
	ss << hex << uppercase << setfill('0') << setw(2) << (TYPE(16))pBYTES[1];
	
	TYPE(64) j;
	for(j=2; j<size(); j++)
	{
		ss << hex << uppercase << setfill('0') << setw(2) << (TYPE(16))pBYTES[j];
	}
	
	ss << ";";
	
	return ss.str();
}























