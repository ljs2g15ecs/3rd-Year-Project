#include "SIMON_definitions.h"

#include <iostream>
using namespace std;

void	encryptFILE(string x)
{
	///*
	DATA FILE(x);
	KEY k;
	k.assign(0x1918, 0x1110, 0x0908, 0x0100);
	FILE.assign(k);
	FILE.checkFILE();
	
	PACKET p, o;
	CIPHER	ENC;
	
	cout << "| ";
	p = FILE.readKEY();
	cout << p.HEX_PKT() << " | ";
	
	o = ENC.compute(p);
	cout << " | " << o.HEX_PKT() << " |" << endl;
	
	do
	{
		cout << "| ";
		p = FILE.readPACKET();
		cout << p.HEX_PKT() << " | ";
		
		o = ENC.compute(p);
		cout << " | " << o.HEX_PKT() << " |" << endl;
	}
	while(FILE.check());
	
	return;
}

int		main()
{
	//testClass();
	
	encryptFILE("test");
}