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

PACKET::PACKET(	_PACKET_	x	)
{
	flush();
	assign(x);
}

//	MUTATORS
void		PACKET::input		(								)
{
	pDATA.iDATA.mode = MODE;
	pDATA.iDATA.in_out = 0;
	pDATA.iDATA.data_key = 0;	//	DEFAULT
	pDATA.iDATA.enc_dec = 0;	//	DEFAULT
	pDATA.iDATA.nBlocks = 0;	//	DEFAULT
	pDATA.count = inputCount++;
}

void		PACKET::output		(	_INFO_	x					)
{
	pDATA.iDATA = x;
	pDATA.iDATA.in_out = 1;		//	CHANGE TO OUPUT
	outputCount++;
}

void		PACKET::assign		(	_PACKET_	x				)
{
	pDATA = x;
	return;
}

void		PACKET::assign		(	_INFO_	x					)
{
	pDATA.iDATA = x;
	return;
}

void		PACKET::assign		(	WORD	x,	TYPE(8)	i		)
{
	pDATA.wDATA[i] = x;
	return;
}

void		PACKET::assign		(	TYPE(N)	x,	TYPE(8)	i		)
{
	pDATA.wDATA[i] = x;
	return;
}

void		PACKET::addWORD		(	WORD	x					)
{
	pDATA.wDATA[nxtWORD++] = x;
	return;
}

void		PACKET::addWORD		(	TYPE(N)	x					)
{
	pDATA.wDATA[nxtWORD++] = x;
	return;
}

void		PACKET::flush		(								)
{
	nxtWORD = 0;
	pDATA.iBYTE = 0;
	pDATA.count = 0;
	pDATA.wDATA[0].flush();
	pDATA.wDATA[1].flush();
	pDATA.wDATA[2].flush();
	pDATA.wDATA[3].flush();
	
	return;
}

void		PACKET::setCounts	(	U_64	x					)
{
	inputCount = x;
	outputCount = x;
	
	return;
}

void		PACKET::setICount	(	U_64	x					)
{
	inputCount = x;
	
	return;
}

void		PACKET::setOCount	(	U_64	x					)
{
	outputCount = x;
	
	return;
}

void		PACKET::resetCounts	(								)
{
	inputCount = 0;
	outputCount = 0;
	
	return;
}

void		PACKET::resetICount	(								)
{
	inputCount = 0;
	
	return;
}

void		PACKET::resetOCount	(								)
{
	outputCount = 0;
	
	return;
}

//	ACCESSORS
void		PACKET::test		(								)
{
	cout 	<< setbase(10)\
			<< "|\tPACKET\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size() << "\t"\
			<< "|\t" << strHEX_WORD() << "\t"\
			<< "|\t" << strCHR_BYTES() << "\t"\
			<< "|\t" << strHEX_BYTES() << "\t" << "|" << endl;
	
	return;
}

_INFO_		PACKET::get_i		(								)
{
	return pDATA.iDATA;
}

TYPE(8)		PACKET::get_Ib		(								)
{
	return pDATA.iBYTE;
}

TYPE(16)	PACKET::get_IB		(								)
{
	return pDATA.iBYTE;
}

_PACKET_	PACKET::get_p		(								)
{
	return pDATA;
}

TYPE(8)		PACKET::get_c		(								)
{
	return pDATA.count;
}

TYPE(16)	PACKET::get_C		(								)
{
	return pDATA.count;
}

WORD		PACKET::get_w		(	TYPE(8)	i					)
{
	return pDATA.wDATA[i];
}

TYPE(N)		PACKET::get_W		(	TYPE(8)	i					)
{
	return pDATA.wDATA[i].get_v();
}

TYPE(8)		PACKET::get_Wb		(	TYPE(8)	i,	TYPE(8)	j		)
{
	return pDATA.wDATA[i].get_b(j);
}

TYPE(16)	PACKET::get_WB		(	TYPE(8)	i,	TYPE(8)	j		)
{
	return pDATA.wDATA[i].get_B(j);
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
	return sizeof(pDATA);
}

string		PACKET::strHEX_WORD	(								)
{
	stringstream ss;
	
	ss << "[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_IB();
	ss << "]-[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_C();
	ss << "]-[";
	ss << pDATA.wDATA[0].strHEX_WORD();
	ss << "-";
	ss << pDATA.wDATA[1].strHEX_WORD();
	ss << "-";
	ss << pDATA.wDATA[2].strHEX_WORD();
	ss << "-";
	ss << pDATA.wDATA[3].strHEX_WORD();
	ss << "]";
	
	return ss.str();
}

string		PACKET::strCHR_BYTES(								)
{
	stringstream ss;
	
	ss << "[";
	ss << (get_Ib() > 0 ? get_Ib() : (TYPE(8))0xFE);
	ss << "]-[";
	ss << (get_Ib() > 0 ? get_c() : (TYPE(8))0xFE);
	ss << "]-[";
	ss << pDATA.wDATA[0].strCHR_BYTES();
	ss << "-";
	ss << pDATA.wDATA[1].strCHR_BYTES();
	ss << "-";
	ss << pDATA.wDATA[2].strCHR_BYTES();
	ss << "-";
	ss << pDATA.wDATA[3].strCHR_BYTES();
	ss << "]";
	
	return ss.str();
}

string		PACKET::strHEX_BYTES(								)
{
	stringstream ss;
	
	ss << "[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_IB();
	ss << "]-[";
	ss << hex << uppercase << setfill('0') << setw(2) << get_C();
	ss << "]-[";
	ss << pDATA.wDATA[0].strHEX_BYTES();
	ss << "-";
	ss << pDATA.wDATA[1].strHEX_BYTES();
	ss << "-";
	ss << pDATA.wDATA[2].strHEX_BYTES();
	ss << "-";
	ss << pDATA.wDATA[3].strHEX_BYTES();
	ss << "]";
	
	return ss.str();
}

string		PACKET::strCHR		(								)
{
	stringstream ss;
	
	ss << (get_Ib() > 0 ? get_Ib() : (TYPE(8))0xFE);
	ss << (get_Ib() > 0 ? get_c() : (TYPE(8))0xFE);
	ss << pDATA.wDATA[0].strCHR_BYTES();
	ss << pDATA.wDATA[1].strCHR_BYTES();
	ss << pDATA.wDATA[2].strCHR_BYTES();
	ss << pDATA.wDATA[3].strCHR_BYTES();
	
	return ss.str();
}

















