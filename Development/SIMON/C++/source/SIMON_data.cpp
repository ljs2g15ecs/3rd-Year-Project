#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

//	CONSTRUCTORS
DATA::DATA()
{
	flush();
}

DATA::DATA(string x) : DATA()
{
	assign(x);
}

//	MUTATORS
void		DATA::assign		(	string	x					)
{
	nameFILE = x;
}

void		DATA::assign		(	KEY		x					)
{
	keyFILE = x;
}

void		DATA::readFILE		(								)
{
	ifstream file(nameFILE, ifstream::binary);
	
	if(file)
	{
		file.seekg(0, file.end);
		sizeBYTE = file.tellg();
		file.seekg(0, file.beg);
		
		bufferBYTE = new char[sizeBYTE];
		file.read(bufferBYTE, sizeBYTE);
		
		file.close();
	}
	
	return;
}

void		DATA::buildWORDS	(								)
{
	TYPE(64) i, countWORD = 0;
	
	bufferWORD.push_back(0);
	
	for(i=0; i<sizeBYTE; i++)
	{
		if( bufferWORD[countWORD].addBYTE(bufferBYTE[i]) )
		{
			bufferWORD.push_back(0);
			countWORD++;
		}
	}
	
	sizeWORD = countWORD + (sizeBYTE % (N/8) ? 1 : 0);
	
	//delete bufferBYTE;
	
	return;
}

void		DATA::buildPACKETS	(								)
{
	TYPE(64) i, countPACKET = 1;
	
	_INFO_ input;
	input.mode = MODE;
	input.in_out = 0;
	input.data_key = 0;	//	DEFAULT
	input.enc_dec = 0;	//	DEFAULT
	input.nBlocks = 1;
	
	inSTREAM.push_back(input);
	inSTREAM[0].addKEY(keyFILE);
	inSTREAM.push_back(input);
	
	for(i=0; i<sizeWORD; i++)
	{
		if( inSTREAM[countPACKET].addWORD(&bufferWORD[i]) )
		{
			inSTREAM.push_back(input);
			countPACKET++;
		}
	}
	
	sizePACKET = countPACKET + (sizeWORD % 4 ? 1 : 0);
	
	return;
}

void		DATA::flush			(								)
{
	//bufferBYTE.clear();
	bufferWORD.clear();
	inSTREAM.clear();
	outSTREAM.clear();
	keyFILE.flush();
}

//	ACCESSOR
void		DATA::test			(								)
{
	readFILE();
	buildWORDS();
	buildPACKETS();
	
	cout 	<< setbase(10)\
			<< "|\tFILE\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << sizeBYTE << "\t"\
			<< "|\t" << sizeWORD << "\t"\
			<< "|\t" << sizePACKET << "\t|" << endl\
			<< CHR_BYTES() << endl\
			<< "|\t" << CHR_WORDS() << "\t"\
			<< "|\t" << HEX_PKT() << "\t|" << endl;
	
	return;
}

string		DATA::CHR_BYTES	(								)
{
	string str = "";
	
	TYPE(64) i;
	for(i=0; i<sizeWORD; i++)
	{
		str += bufferWORD[i].CHR_BYTES();
		if(i != sizeWORD-1)	str += "-";
	}
	
	return str;
}

string		DATA::CHR_WORDS	(								)
{
	string str = "";
	
	TYPE(64) i;
	for(i=0; i<sizeWORD; i++)
	{
		str += bufferWORD[i].HEX_BYTES();
		if(((i%4) == 3) && (i != sizeWORD-1))	str += "\t|\n|\t";
		else if(i != sizeWORD-1)	str += "-";
	}
	
	return str;
}

string		DATA::HEX_PKT	(								)
{
	string str = "\n|\t";
	
	TYPE(64) i;
	for(i=0; i<sizePACKET; i++)
	{
		str += inSTREAM[i].HEX_PKT();
		if(i!= sizePACKET-1)	str += "\t|\n|\t";
	}
	
	return str;
}



