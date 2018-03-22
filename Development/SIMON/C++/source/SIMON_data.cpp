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

WORD		DATA::readWORD		(								)
{
	WORD w;
	TYPE(16) i, n = 0;
	ifstream file(nameFILE, ifstream::binary);
	
	if(file)
	{
		file.seekg(posFILE, ios::beg);
		
		if((sizeFILE-sizeBYTE) >= N/8)	n = N/8;
		else						 	n = sizeFILE-sizeBYTE;
		
		bufferBYTE = new char[n];
		
		file.read(bufferBYTE, n);
		posFILE = file.tellg();
		
		sizeBYTE += n;
		
		for(i=0; i<n; i++)
		{
			w.addBYTE(bufferBYTE[i]);
			streamBYTE.push_back(bufferBYTE[i]);
		}
		
		delete bufferBYTE;
	}
	
	return w;
}

PACKET		DATA::readPACKET	(								)
{
	bufferPACKET = new PACKET;
	
	_INFO_ input;
	input.mode = MODE;
	input.in_out = 0;
	input.data_key = 0;	//	DEFAULT
	input.enc_dec = 0;	//	DEFAULT
	input.nBlocks = 1;
	
	bufferPACKET->input();		bufferPACKET->assign(input);
	
	bufferWORD[0] = readWORD();
	bufferWORD[1] = readWORD();
	bufferWORD[2] = readWORD();
	bufferWORD[3] = readWORD();
	
	streamWORD.push_back(bufferWORD[0]);
	streamWORD.push_back(bufferWORD[1]);
	streamWORD.push_back(bufferWORD[2]);
	streamWORD.push_back(bufferWORD[3]);
	
	bufferPACKET->addWORD(bufferWORD[0]);
	bufferPACKET->addWORD(bufferWORD[1]);
	bufferPACKET->addWORD(bufferWORD[2]);
	bufferPACKET->addWORD(bufferWORD[3]);
	
	bufferPACKET->pack();
	
	return *bufferPACKET;
}

void		DATA::readFILE		(								)
{
	while(sizeBYTE < sizeFILE)
	{
		streamIN.push_back(readPACKET());
	}
	
	sizeWORD = streamWORD.size();
	sizePACKET = streamIN.size();
}

void		DATA::flush			(								)
{
	//bufferBYTE = new char;
	bufferWORD[0].flush();	bufferWORD[1].flush();
	bufferWORD[2].flush();	bufferWORD[3].flush();
	bufferPACKET = new PACKET;
	streamBYTE.clear();		//streamBYTE.push_back(0);
	streamWORD.clear();		//streamWORD.push_back(0);
	streamIN.clear();		//streamIN.push_back(0);
	streamOUT.clear();		//streamOUT.push_back(0);
	keyFILE.flush();
	posFILE = 0;
	sizeFILE = 0;
	sizeBYTE = 0;
	sizeWORD = 0;
	sizePACKET = 0;
}

//	ACCESSOR
void		DATA::test			(								)
{
	checkFILE();
	readFILE();
	
	cout 	<< "|\tFILE\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << sizeFILE << "\t"\
			<< "|\t" << sizeBYTE << "\t"\
			<< "|\t" << sizeWORD << "\t"\
			<< "|\t" << sizePACKET << "\t"\
			<< "|" << endl << endl;
	
	///*
	cout	<< CHR_BYTES() << endl;
	cout	<< HEX_WORDS();
	cout	<< HEX_PKT();
	//*/
	
	return;
}

string		DATA::CHR_BYTES	(								)
{
	string str = "";
	
	TYPE(64) i;
	for(i=0; i<sizeWORD; i++)
	{
		str += streamWORD.at(i).CHR_BYTES();
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
		str += streamWORD.at(i).HEX_BYTES();
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
		str += streamIN[i].HEX_PKT();
		if(i!= sizePACKET-1)	str += "\t|\n|\t";
	}
	str += "\t|\n";
	
	return str;
}



