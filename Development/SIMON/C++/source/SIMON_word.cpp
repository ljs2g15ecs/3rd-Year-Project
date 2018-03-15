#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//	CONSTRUCTORS
			WORD::WORD			(								)
{
	flush();
}

			WORD::WORD			(	TYPE(N)	x					)
{
	assign(x);
}

//	MUTATORS
void		WORD::assign		(	TYPE(N)	x					)
{
	val = x;
	return;
}

void		WORD::assign		(	TYPE(8)	x, TYPE(8)	i		)
{
	bytes[i] = x;
	return;
}

void		WORD::flush			(								)
{
	val = 0;
	return;
}

//	ACCESSORS
void		WORD::test			(								)
{
	cout 	<< setbase(10)\
			<< "|\tWORD\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size_v() << "\t"\
			<< "|\t" << size_b() << "\t"\
			<< "|\t" << strHEX_WORD() << "\t"\
			<< "|\t" << strCHR_BYTES() << "\t"\
			<< "|\t" << strHEX_BYTES() << "\t|" << endl;
	return;
}

TYPE(N)		WORD::get_v			(								)
{
	return val;
}

TYPE(8)		WORD::get_b			(	TYPE(8)	i					)
{
	return bytes[i];
}

TYPE(16)	WORD::get_B			(	TYPE(8)	i					)
{
	return bytes[i];
}

TYPE(16)	WORD::size_v		(								)
{
	return sizeof(TYPE(N));
}

TYPE(16)	WORD::size_b		(								)
{
	return sizeof(bytes);
}

string		WORD::strHEX_WORD	(								)
{
	stringstream ss;
	ss << hex << uppercase << setfill('0') << setw(N/4) << get_v();
	return ss.str();
}

string		WORD::strCHR_BYTES	(								)
{
	string str = "";
	TYPE(64) i;
	for(i=size_b(); i>0; i--)
	{
		str += (get_b(i-1) > 0 ? get_b(i-1) : 0xFE);
	}
	return str;
}

string		WORD::strHEX_BYTES	(								)
{
	stringstream ss;
	TYPE(64) i;
	for(i=size_b(); i>0; i--)
	{
		ss << hex << uppercase << setfill('0') << setw(2) << get_B(i-1);
		if(i != 1)	ss << ":";
	}
	return ss.str();
}
