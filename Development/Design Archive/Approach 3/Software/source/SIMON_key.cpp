#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

KEY::KEY()
{
	flush();
}

/*
KEY::KEY(	WORD	x[M]				)
{
	assign(x);
}

KEY::KEY(	TYPE(N)	x[M]				)
{
	assign(x);
}

void	KEY::assign(	WORD	x[M]				)
{
	
}

void	KEY::assign(	TYPE(N)	x[M]				)
{
	
}
//*/

KEY::KEY(WORD x0, WORD x1) : KEY()
{
	assign(x0, x1);
}

KEY::KEY(TYPE(N) x0, TYPE(N) x1) : KEY()
{
	assign(x0, x1);
}

KEY::KEY(WORD x0, WORD x1, WORD	x2) : KEY()
{
	assign(x0, x1, x2);
}

KEY::KEY(TYPE(N)x0, TYPE(N) x1, TYPE(N) x2) : KEY()
{
	assign(x0, x1, x2);
}

KEY::KEY(WORD x0, WORD x1, WORD x2, WORD x3) : KEY()
{
	assign(x0, x1, x2, x3);
	return;
}

KEY::KEY(TYPE(N) x0, TYPE(N) x1, TYPE(N) x2, TYPE(N) x3) : KEY()
{
	assign(x0, x1, x2, x3);
	return;
}

//	MUTATORS
void		KEY::assign		(	WORD	x0,	WORD	x1		)
{
	K[0] = x0;
	K[1] = x1;
	return;
}

void		KEY::assign		(	TYPE(N)	x0,	TYPE(N)	x1		)
{
	K[0] = x0;
	K[1] = x1;
	return;
}

//	MUTATORS
void		KEY::assign		(	WORD	x0,	WORD	x1,
								WORD	x2					)
{
	K[0] = x0;
	K[1] = x1;
	K[2] = x2;
	return;
}

void		KEY::assign		(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2					)
{
	K[0] = x0;
	K[1] = x1;
	K[2] = x2;
	return;
}

//	MUTATORS
void		KEY::assign		(	WORD	x0,	WORD	x1,
								WORD	x2, WORD	x3		)
{
	K[0] = x0;
	K[1] = x1;
#if (M>2)
	K[2] = x2;
#endif
#if (M>3)
	K[3] = x3;
#endif
	return;
}

void		KEY::assign		(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2, TYPE(N)	x3		)
{
	K[0] = x0;
	K[1] = x1;
#if (M>2)
	K[2] = x2;
#endif
#if (M>3)
	K[3] = x3;
#endif
	return;
}

#if (M == 2)
KEY		KEY::reverse	(								)
{
	return KEY( get_w(1), get_w(0) );
}

void		KEY::flush		(								)
{
	K[0].flush();
	K[1].flush();
	return;
}

//	ACCESSOR
string		KEY::HEX_WORD	(								)
{
	string str = "";
	
	str += K[0].HEX_WORD();
	str += "-";
	str += K[1].HEX_WORD();
	
	return str;
}

string		KEY::CHR_BYTES	(								)
{
	string str = "";
	
	str += K[0].CHR_BYTES();
	str += "-";
	str += K[1].CHR_BYTES();
	
	return str;
}

string		KEY::HEX_BYTES	(								)
{
	string str = "";
	
	str += K[0].HEX_BYTES();
	str += "-";
	str += K[1].HEX_BYTES();
	
	return str;
}

string		KEY::CHR		(								)
{
	string str = "";
	
	str += K[0].CHR_BYTES();
	str += K[1].CHR_BYTES();
	
	return str;
}

#endif
#if (M == 3)
KEY		KEY::reverse	(								)
{
	return KEY( get_w(2), get_w(1), get_w(0) );
}

void		KEY::flush		(								)
{
	K[0].flush();
	K[1].flush();
	K[2].flush();
	return;
}

//	ACCESSOR
string		KEY::HEX_WORD	(								)
{
	string str = "";
	
	str += K[0].HEX_WORD();
	str += "-";
	str += K[1].HEX_WORD();
	str += "-";
	str += K[2].HEX_WORD();
	
	return str;
}

string		KEY::CHR_BYTES	(								)
{
	string str = "";
	
	str += K[0].CHR_BYTES();
	str += "-";
	str += K[1].CHR_BYTES();
	str += "-";
	str += K[2].CHR_BYTES();
	
	return str;
}

string		KEY::HEX_BYTES	(								)
{
	string str = "";
	
	str += K[0].HEX_BYTES();
	str += "-";
	str += K[1].HEX_BYTES();
	str += "-";
	str += K[2].HEX_BYTES();
	
	return str;
}

string		KEY::CHR		(								)
{
	string str = "";
	
	str += K[0].CHR_BYTES();
	str += K[1].CHR_BYTES();
	str += K[2].CHR_BYTES();
	
	return str;
}

#endif
#if (M == 4)
KEY		KEY::reverse	(								)
{
	return KEY( get_w(3), get_w(2), get_w(1), get_w(0) );
}

void		KEY::flush		(								)
{
	K[0].flush();
	K[1].flush();
	K[2].flush();
	K[3].flush();
	return;
}

//	ACCESSOR
string		KEY::HEX_WORD	(								)
{
	string str = "";
	
	str += K[0].HEX_WORD();
	str += "-";
	str += K[1].HEX_WORD();
	str += "-";
	str += K[2].HEX_WORD();
	str += "-";
	str += K[3].HEX_WORD();
	
	return str;
}

string		KEY::CHR_BYTES	(								)
{
	string str = "";
	
	str += K[0].CHR_BYTES();
	str += "-";
	str += K[1].CHR_BYTES();
	str += "-";
	str += K[2].CHR_BYTES();
	str += "-";
	str += K[3].CHR_BYTES();
	
	return str;
}

string		KEY::HEX_BYTES	(								)
{
	string str = "";
	
	str += K[0].HEX_BYTES();
	str += "-";
	str += K[1].HEX_BYTES();
	str += "-";
	str += K[2].HEX_BYTES();
	str += "-";
	str += K[3].HEX_BYTES();
	
	return str;
}

string		KEY::CHR		(								)
{
	string str = "";
	
	str += K[0].CHR_BYTES();
	str += K[1].CHR_BYTES();
	str += K[2].CHR_BYTES();
	str += K[3].CHR_BYTES();
	
	return str;
}

#endif

//	ACCESSOR
void		KEY::test		(								)
{
	cout 	<< setbase(10)\
			<< "|\tKEY\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size() << "\t"\
			<< "|\t" << HEX_WORD() << "\t"\
			<< "|\t" << CHR_BYTES() << "\t"\
			<< "|\t" << HEX_BYTES() << "\t" << "|" << endl;
	
	return;
}

WORD		KEY::get_w		(	TYPE(8)	i					)
{
	return K[i];
}

WORD*		KEY::ref_w		(	TYPE(8)	i					)
{
	return &K[i];
}

TYPE(N)		KEY::get_W		(	TYPE(8)	i					)
{
	return K[i].get_v();
}

TYPE(8)		KEY::get_Wb		(	TYPE(8)	i, TYPE(8)	j		)
{
	return K[i].get_b(j);
}

TYPE(16)	KEY::get_WB		(	TYPE(8)	i, TYPE(8)	j		)
{
	return K[i].get_B(j);
}

TYPE(16)	KEY::size		(								)
{
	return sizeof(K);
}