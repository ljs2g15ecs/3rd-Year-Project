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

#if (M == 2)
KEY::KEY						(	WORD	x0,	WORD	x1		)
{
	
}

KEY::KEY						(	TYPE(N)	x0,	TYPE(N)	x1		)
{
	
}

#endif
#if (M == 3)
KEY::KEY						(	WORD	x0,	WORD	x1,
									WORD	x2					)
{
	
}

KEY::KEY						(	TYPE(N)	x0,	TYPE(N)	x1,
									TYPE(N)	x2					)
{
	
}

#endif
#if (M == 4)
KEY::KEY						(	WORD	x0,	WORD	x1,
									WORD	x2, WORD	x3		)
{
	assign(x0, x1, x2, x3);
	return;
}

KEY::KEY						(	TYPE(N)	x0,	TYPE(N)	x1,
									TYPE(N)	x2, TYPE(N)	x3		)
{
	assign(x0, x1, x2, x3);
	return;
}

//	MUTATORS
void		KEY::assign			(	WORD	x0,	WORD	x1,
									WORD	x2, WORD	x3		)
{
	K[0] = x0;
	K[1] = x1;
	K[2] = x2;
	K[3] = x3;
	return;
}

void		KEY::assign			(	TYPE(N)	x0,	TYPE(N)	x1,
									TYPE(N)	x2, TYPE(N)	x3		)
{
	K[0] = x0;
	K[1] = x1;
	K[2] = x2;
	K[3] = x3;
	return;
}

void		KEY::flush			(								)
{
	K[0].flush();
	K[1].flush();
	K[2].flush();
	K[3].flush();
	return;
}

//	ACCESSOR
string		KEY::strHEX_WORD	(								)
{
	string str = "";
	
	str += K[0].strHEX_WORD();
	str += "-";
	str += K[1].strHEX_WORD();
	str += "-";
	str += K[2].strHEX_WORD();
	str += "-";
	str += K[3].strHEX_WORD();
	
	return str;
}

string		KEY::strCHR_BYTES	(								)
{
	string str = "";
	
	str += K[0].strCHR_BYTES();
	str += "-";
	str += K[1].strCHR_BYTES();
	str += "-";
	str += K[2].strCHR_BYTES();
	str += "-";
	str += K[3].strCHR_BYTES();
	
	return str;
}

string		KEY::strHEX_BYTES	(								)
{
	string str = "";
	
	str += K[0].strHEX_BYTES();
	str += "-";
	str += K[1].strHEX_BYTES();
	str += "-";
	str += K[2].strHEX_BYTES();
	str += "-";
	str += K[3].strHEX_BYTES();
	
	return str;
}

string		KEY::strCHR			(								)
{
	string str = "";
	
	str += K[0].strCHR_BYTES();
	str += K[1].strCHR_BYTES();
	str += K[2].strCHR_BYTES();
	str += K[3].strCHR_BYTES();
	
	return str;
}

#endif

//	ACCESSOR
void		KEY::test			(								)
{
	cout 	<< setbase(10)\
			<< "|\tKEY\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size() << "\t"\
			<< "|\t" << strHEX_WORD() << "\t"\
			<< "|\t" << strCHR_BYTES() << "\t"\
			<< "|\t" << strHEX_BYTES() << "\t" << "|" << endl;
	
	return;
}

WORD		KEY::get_w			(	TYPE(8)	i					)
{
	return K[i];
}

TYPE(N)		KEY::get_W			(	TYPE(8)	i					)
{
	return K[i].get_v();
}

TYPE(8)		KEY::get_Wb			(	TYPE(8)	i, TYPE(8)	j		)
{
	return K[i].get_b(j);
}

TYPE(16)	KEY::get_WB			(	TYPE(8)	i, TYPE(8)	j		)
{
	return K[i].get_B(j);
}

TYPE(16)	KEY::size			(								)
{
	return sizeof(K);
}