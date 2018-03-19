#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

//	CONSTRUCTORS
KEY_S::KEY_S()
{
	flush();
}

//	MUTATORS

void		KEY_S::assign		(	WORD	x,	TYPE(8)	i		)
{
	K[i] = x;
	return;
}

void		KEY_S::assign		(	TYPE(N)	x,	TYPE(8)	i		)
{
	K[i] = x;
	return;
}

void		KEY_S::flush		(								)
{
	TYPE(8) i;
	for(i=0; i<T; i++)	K[i].flush();
	return;
}

//	ACCESSORS
void		KEY_S::test			(								)
{
	cout 	<< setbase(10)\
			<< "|\tKEY\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << size() << "\t"\
			<< "|\t" << strHEX_WORD() << "\t"\
			<< "|\t" << strCHR_BYTES() << "\t"\
			<< "|\t" << strHEX_BYTES() << "\t" << "|" << endl;
	
	return;
}

WORD		KEY_S::get_w		(	TYPE(8)	i					)
{
	return K[i];
}

TYPE(N)		KEY_S::get_W		(	TYPE(8)	i					)
{
	return K[i].get_v();
}

TYPE(8)		KEY_S::get_Wb		(	TYPE(8)	i, TYPE(8)	j		)
{
	return K[i].get_b(j);
}

TYPE(16)	KEY_S::get_WB		(	TYPE(8)	i, TYPE(8)	j		)
{
	return K[i].get_B(j);
}

TYPE(16)	KEY_S::size			(								)
{
	return sizeof(K);
}

string		KEY_S::strHEX_WORD	(								)
{
	string str = "\n| ";
	TYPE(8) i;
	for(i=0; i<T; i++)
	{
		str += K[i].strHEX_WORD();
		
		if(i != T-1)	str += "-";
	}
	return str;
}

string		KEY_S::strCHR_BYTES	(								)
{
	string str = "\n| ";
	TYPE(8) i;
	for(i=0; i<T; i++)
	{
		str += K[i].strCHR_BYTES();
		
		if(i != T-1)	str += "-";
	}
	return str;
}

string		KEY_S::strHEX_BYTES	(								)
{
	string str = "\n| ";
	TYPE(8) i;
	for(i=0; i<T; i++)
	{
		str += K[i].strHEX_BYTES();
		
		if(i != T-1)	str += "-";
	}
	return str;
}

string		KEY_S::strCHR		(								)
{
	string str = "\n| ";
	TYPE(8) i;
	for(i=0; i<T; i++)
	{
		str += K[i].strCHR_BYTES();
	}
	return str;
}	
	