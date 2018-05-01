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
		
		for(i=0; i<n; i++)	w.addBYTE(bufferBYTE[i]);
		
		delete bufferBYTE;
		
		file.close();
	}
	
	return w;
}

PACKET		DATA::readPACKET	(								)
{
	PACKET bufferPACKET;
	
	_INFO_ input;
	input.mode = MODE;
	input.in_out = 0;
	input.data_key = 0;	//	DEFAULT
	input.enc_dec = 1;	//	DEFAULT
	input.nBlocks = 1;
	
	bufferPACKET.input();		bufferPACKET.assign(input);
	
	bufferPACKET.addWORD(readWORD());
	bufferPACKET.addWORD(readWORD());
	bufferPACKET.addWORD(readWORD());
	bufferPACKET.addWORD(readWORD());
	
	bufferPACKET.pack();
	
	return bufferPACKET;
}

PACKET		DATA::readPACKET	(	_INFO_	x					)
{
	PACKET bufferPACKET;
	
	bufferPACKET.input();		bufferPACKET.assign(x);
	
	bufferPACKET.addWORD(readWORD());
	bufferPACKET.addWORD(readWORD());
	bufferPACKET.addWORD(readWORD());
	bufferPACKET.addWORD(readWORD());
	
	bufferPACKET.pack();
	
	return bufferPACKET;
}

PACKET		DATA::readPACKET	(	BLOCK	x0,	BLOCK	x1		)
{
	PACKET bufferPACKET;
	
	_INFO_ input;
	input.mode = MODE;
	input.in_out = 0;
	input.data_key = 0;	//	DEFAULT
	input.enc_dec = 1;	//	DEFAULT
	input.nBlocks = 1;
	
	bufferPACKET.input();		bufferPACKET.assign(input);
	
	bufferPACKET.addWORD(x0.get_w(0));
	bufferPACKET.addWORD(x0.get_w(1));
	bufferPACKET.addWORD(x1.get_w(0));
	bufferPACKET.addWORD(x1.get_w(1));
	
	bufferPACKET.pack();
	
	return bufferPACKET;
}

BLOCK		DATA::readBLOCK		(								)
{
	BLOCK b;
	b.addWORD(readWORD());
	b.addWORD(readWORD());
	return b;
}

PACKET		DATA::readKEY		(								)
{
	PACKET bufferPACKET;
	
	_INFO_ input;
	input.mode = MODE;
	input.in_out = 0;
	input.data_key = 0;	//	DEFAULT
	input.enc_dec = 1;	//	DEFAULT
	input.nBlocks = 1;
	
	bufferPACKET.input();		bufferPACKET.assign(input);
	
	bufferPACKET.addKEY(keyFILE);
	
	bufferPACKET.pack();
	
	return bufferPACKET;
}

void		DATA::readFILE_PKT	(								)
{
	sizeBYTE = 0;
	posFILE = 0;
	checkFILE();
	
	while(sizeBYTE < sizeFILE)
	{
		streamPKT_IN.push_back(readPACKET());
	}
	
	sizePACKET = streamPKT_IN.size();
}

void		DATA::readFILE_PKT	(	_INFO_	x					)
{
	streamPKT_IN.push_back(readKEY());
	
	while(sizeBYTE < sizeFILE)
	{
		streamPKT_IN.push_back(readPACKET(x));
	}
	
	sizePACKET = streamPKT_IN.size();
}

void		DATA::addFILE_PKT	(								)
{
	streamPKT_IN.push_back(readKEY());
	keyADDED = 1;
}

void		DATA::addFILE_PKT	(	BLOCK	x0,	BLOCK	x1		)
{
	streamPKT_IN.push_back(readPACKET(x0, x1));
}

void		DATA::addFILE_PKT	(	KEY		x					)
{
	assign(x);
	streamPKT_IN.push_back(readKEY());
}

TYPE(64)	DATA::computePKTs	(	TYPE(64)	i				)
{
	TYPE(64) j, total;
	total = sizePACKET >= i ? i : sizePACKET;
	
	CIPHER SIMON;
	
	for(j=0; j<total; j++)
	{
		streamPKT_OUT.push_back(SIMON.compute(streamPKT_IN.at(j)));
#ifdef	DEBUG
		cout << "|\t" << streamPKT_IN[j].HEX_WORD() << "\t|>>";
		cout << "|\t" << streamPKT_OUT[j].HEX_WORD() << "\t|" << endl;
#endif
	}
	
	return total;
}

void		DATA::readFILE_BLK	(								)
{
	sizeBYTE = 0;
	posFILE = 0;
	checkFILE();
	
	while(sizeBYTE < sizeFILE)
	{
		streamBLK_IN.push_back(readBLOCK());
	}
	
	sizeBLOCK = streamBLK_IN.size();
}

void		DATA::addFILE_BLK	(	BLOCK	x					)
{
	streamBLK_IN.push_back(x);
	streamBLK_IN.push_back(x);
}

TYPE(64)	DATA::encryptBLKs	(	TYPE(64)	i				)
{
	TYPE(64) j, total;
	total = sizeBLOCK >= i ? i : sizeBLOCK;
	
	CIPHER SIMON;
	SIMON.expandKEY(keyFILE);
	
	for(j=0; j<total; j++)
	{
		streamBLK_OUT.push_back(SIMON.compute(streamBLK_IN.at(j), 1));
#ifdef	DEBUG
		cout << "|\t" << streamBLK_IN[j].HEX_WORD() << "\t|>>";
		cout << "|\t" << streamBLK_OUT[j].HEX_WORD() << "\t|" << endl;
#endif
	}
	
	return total;
}

void		DATA::flush			(								)
{
	bufferBYTE = new char;
	bufferWORD[0].flush();	bufferWORD[1].flush();
	bufferWORD[2].flush();	bufferWORD[3].flush();
	streamPKT_IN.clear();
	streamBLK_IN.clear();
	streamPKT_OUT.clear();
	streamBLK_OUT.clear();
	keyFILE.flush();
	posFILE = 0;
	sizeFILE = 0;
	sizeBYTE = 0;
	sizePACKET = 0;
	sizeBLOCK = 0;
	keyADDED = 0;
}

//	ACCESSOR
void		DATA::test			(								)
{
	checkFILE();
	readFILE_PKT();
	readFILE_BLK();
	
	cout 	<< "|\tFILE\t|\t" << sizeof(this) << "\t"\
			<< "|\t" << sizeFILE << "\t"\
			<< "|\t" << sizePACKET << "\t"\
			<< "|" << endl << endl;
	
	cout	<< HEX_PKT();
	cout	<< HEX_PKT_SV();
	
	cout	<< HEX_BLK();
	cout	<< HEX_BLK_SV();
	
	return;
}

TYPE(8)		DATA::check		(								)
{
	return (sizeFILE-sizeBYTE) > 0;
}

string		DATA::HEX_PKT	(								)
{
	string str = "\n|\t";
	
	TYPE(64) i;
	for(i=0; i<sizePACKET; i++)
	{
		str += streamPKT_IN[i].HEX_PKT();
		if(i!= sizePACKET-1)	str += "\t|\n|\t";
	}
	str += "\t|\n";
	
	return str;
}

string		DATA::HEX_PKT_SV(								)
{
	string str = "\n\t";
	
	TYPE(64) i;
	for(i=0; i<sizePACKET; i++)
	{
		str += streamPKT_IN[i].HEX_SV(i);
		if(i!= sizePACKET-1)	str += "\n\t";
	}
	str += "\n";
	
	return str;
}

string		DATA::HEX_BLK	(								)
{
	string str = "\n|\t";
	
	TYPE(64) i;
	for(i=0; i<sizeBLOCK; i++)
	{
		str += streamBLK_IN[i].HEX_WORD();
		if(i!= sizeBLOCK-1)	str += "\t|\n|\t";
	}
	str += "\t|\n";
	
	return str;
}

string		DATA::HEX_BLK_SV(								)
{
	string str = "\n|\t";
	
	TYPE(64) i;
	for(i=0; i<sizeBLOCK; i++)
	{
		str += streamBLK_IN[i].HEX_SV(i);
		if(i!= sizeBLOCK-1)	str += "\t|\n|\t";
	}
	str += "\t|\n";
	
	return str;
}



