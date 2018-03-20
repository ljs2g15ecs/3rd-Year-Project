#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//	CONSTRUCTORS
WORD::WORD()
{
	flush();
}

WORD::WORD(TYPE(N) x) : WORD()
{
	assign(x);
}

//	MUTATORS
void		WORD::assign	(	TYPE(N)	x					)
{
	val = x;
	return;
}

void		WORD::assign	(	TYPE(8)	x, TYPE(8)	i		)
{
	bytes[i] = x;
	return;
}

TYPE(8)		WORD::addBYTE	(	TYPE(8)	x					)
{
	bytes[--w_nxtBYTE] = x;
	///*
	if(w_nxtBYTE != 0)	return 0;
	else
	{
		w_nxtBYTE = N/8;
		return 1;
	}
	//*/
}

void		WORD::flush		(								)
{
	w_nxtBYTE = N/8;
	r_nxtBYTE = N/8;
	val = 0;
	return;
}

//	ACCESSORS
void		WORD::test		(								)
{
	cout 	<< setbase(10)\
			<< "|\tWORD\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size_v() << "\t"\
			<< "|\t" << size_b() << "\t"\
			<< "|\t" << HEX_WORD() << "\t"\
			<< "|\t" << CHR_BYTES() << "\t"\
			<< "|\t" << HEX_BYTES() << "\t|" << endl;
	return;
}

TYPE(N)		WORD::get_v		(								)
{
	return val;
}

TYPE(8)		WORD::get_b		(								)
{
	if(w_nxtBYTE == 0)	r_nxtBYTE = N/8;
	return bytes[--r_nxtBYTE];
}

TYPE(8)		WORD::get_b		(	TYPE(8)	i					)
{
	return bytes[i];
}

TYPE(16)	WORD::get_B		(	TYPE(8)	i					)
{
	return bytes[i];
}

TYPE(16)	WORD::size_v	(								)
{
	return sizeof(TYPE(N));
}

TYPE(16)	WORD::size_b	(								)
{
	return sizeof(bytes);
}

string		WORD::HEX_WORD	(								)
{
	stringstream ss;
	ss	<< hex << uppercase << setfill('0')\
		<< setw(N/4) << get_v();
	return ss.str();
}

string		WORD::CHR_BYTES	(								)
{
	string str = "";
	TYPE(64) i;
	for(i=size_b(); i>0; i--)
	{
		str += (get_b(i-1) > 0 ? get_b(i-1) : 0xFE);
	}
	return str;
}

string		WORD::HEX_BYTES	(								)
{
	stringstream ss;
	TYPE(64) i;
	for(i=size_b(); i>0; i--)
	{
		ss 	<< hex << uppercase << setfill('0')\
			<< setw(2) << get_B(i-1);
		if(i != 1)	ss << ":";
	}
	return ss.str();
}

