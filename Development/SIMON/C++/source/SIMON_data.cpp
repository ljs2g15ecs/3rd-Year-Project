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

void		DATA::checkFILE		(								)
{
	ifstream file(nameFILE, ifstream::binary);
	
	if(file)
	{
		file.seekg(0, file.end);
		sizeFILE = file.tellg();
		file.seekg(0, file.beg);
		
		posFILE = file.tellg();
		
		file.close();
	}
	
	return;
}

void		DATA::readFILE		(								)
{
	ifstream file(nameFILE, ifstream::binary);
	
	if(file)
	{
		file.seekg(0, file.end);
		sizeFILE = file.tellg();
		file.seekg(0, file.beg);
		
		bufferBYTE = new char[sizeFILE];
		file.read(bufferBYTE, sizeFILE);
		
		file.close();
	}
	
	return;
}

void		DATA::readFILE		(	TYPE(8)	x					)
{
	TYPE(8) n = 0;
	ifstream file(nameFILE, ifstream::binary);
	
	if(file)
	{
		file.seekg(posFILE);
		
		if((sizeFILE-sizeBYTE) >= x) n = x;
		else						 n = sizeFILE-sizeBYTE;
		
		bufferBYTE = new char[n];
		
		file.read(bufferBYTE, n);
		posFILE = file.tellg();
		
		sizeBYTE += n;
		buildWORDS(n);
		
		delete bufferBYTE;
	}
	
	return;
}

void		DATA::buildWORDS	(	TYPE(8)	x 					)
{
	TYPE(64) i;
	
	bufferWORD.push_back(0);
	
	for(i=0; i<x; i++)
	{
		if( (bufferWORD.back().addBYTE(bufferBYTE[i])) && (i != x-1))
		{
			bufferWORD.push_back(0);
		}
	}
	
	sizeWORD = bufferWORD.size();
	
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
	sizeBYTE = 0;
	sizeWORD = 0;
	sizePACKET = 0;
}

//	ACCESSOR
void		DATA::test			(								)
{
	checkFILE();
	while(sizeBYTE < sizeFILE)	readFILE(N/2);
	buildPACKETS();
	
	cout 	<< "|\tFILE\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << sizeFILE << "\t"\
			<< "|\t" << sizeBYTE << "\t"\
			<< "|\t" << sizeWORD << "\t"\
			<< "|\t" << sizePACKET << "\t"\
			<< "|" << endl << endl;
			
	cout	<< CHR_BYTES() << endl;
	cout	<< HEX_WORDS();
	cout	<< HEX_PKT();
	
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

string		DATA::HEX_WORDS	(								)
{
	string str = "\n|\t";
	
	TYPE(64) i;
	for(i=0; i<sizeWORD; i++)
	{
		str += bufferWORD[i].HEX_BYTES();
		if(((i%4) == 3) && (i != sizeWORD-1))	str += "\t|\n|\t";
		else if(i != sizeWORD-1)	str += "-";
	}
	
	str += "\t|\n";
	
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
	str += "\t|\n";
	
	return str;
}



