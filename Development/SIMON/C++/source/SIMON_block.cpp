#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

//	CONSTUCTORS
BLOCK::BLOCK()
{
	flush();
}

BLOCK::BLOCK(TYPE(N) x0, TYPE(N) x1) : BLOCK()
{
	assign(x0, x1);
}

BLOCK::BLOCK				(	WORD	x0, WORD	x1		)
{
	assign(x0, x1);
}

//	MUTATORS
void		BLOCK::assign	(	TYPE(N)	x0,	TYPE(N)	x1		)
{
	B[0] = x0;
	B[1] = x1;
	return;
}

void		BLOCK::assign	(	WORD	x0, WORD	x1		)
{
	B[0] = x0;
	B[1] = x1;
	return;
}

void		BLOCK::assign	(	TYPE(N)	x,	TYPE(8)	i		)
{
	B[i] = x;
	return;
}

void		BLOCK::assign	(	WORD	x,	TYPE(8)	i		)
{
	B[i] = x;
	return;
}

void		BLOCK::flush	(								)
{
	B[0] = 0;
	B[1] = 0;
	return;
}

//	ACCESSORS
void		BLOCK::test		(								)
{
	cout 	<< setbase(10)\
			<< "|\tBLOCK\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size() << "\t"\
			<< "|\t" << HEX_WORD() << "\t"\
			<< "|\t" << CHR_BYTES() << "\t"\
			<< "|\t" << HEX_BYTES() << "\t" << "|" << endl;
	
	return;
}

WORD		BLOCK::get_w	(	TYPE(8)	i					)
{
	return B[i];
}

WORD*		BLOCK::ref_w	(	TYPE(8)	i					)
{
	return &B[i];
}

TYPE(N)		BLOCK::get_W	(	TYPE(8)	i					)
{
	return B[i].get_v();
}

TYPE(8)		BLOCK::get_Wb	(	TYPE(8)	i, TYPE(8)	j		)
{
	return B[i].get_b(j);
}

TYPE(16)	BLOCK::get_WB	(	TYPE(8)	i, TYPE(8)	j		)
{
	return B[i].get_B(j);
}

TYPE(16)	BLOCK::size		(								)
{
	return sizeof(B);
}

string	BLOCK::HEX_WORD		(								)
{
	string str = "";
	str += B[0].HEX_WORD();
	str += "-";
	str += B[1].HEX_WORD();
	return str;
}

string	BLOCK::CHR_BYTES	(								)
{
	string str = "";
	str += B[0].CHR_BYTES();
	str += "-";
	str += B[1].CHR_BYTES();
	return str;
}

string	BLOCK::HEX_BYTES	(								)
{
	string str = "";
	str += B[0].HEX_BYTES();
	str += "-";
	str += B[1].HEX_BYTES();
	return str;
}

string	BLOCK::CHR			(								)
{
	string str = "";
	str += B[0].CHR_BYTES();
	str += B[1].CHR_BYTES();
	return str;
}

















