#include "SIMON_definitions.h"

#include <iostream>
using namespace std;

int		main()
{
	cout << "|\tMODE\t|\t" << MODE << "\t|" << endl;
	cout << "|\tN\t|\t" << N << "\t|" << endl;
	cout << "|\tM\t|\t" << M << "\t|" << endl;
	cout << "|\tT\t|\t" << T << "\t|" << endl;
	cout << "|\tJ\t|\t" << J << "\t|" << endl;
	cout << "|\tTYPE(N)\t|\t" << sizeof(TYPE(N)) << "\t|" << endl;
	cout << "|\tWORD\t|\t" << sizeof(WORD) << "\t|" << endl;
	
	WORD a = 0xB, b = 0x4;			a.test();
	WORD c = a ^ b;	c.test();
	c = a << 4;		c.test();
	c = a >> 4;		c.test();
	c = ~a;			c.test();
	BLOCK d;		d.test();
	KEY e;
	e.assign(0x1918, 0x1110, 0x0908, 0x0100);
	e.test();
	//KEY_S f;		f.test();
	
	//_INFO_ input;\
	input.mode = MODE;\
	input.in_out = 0;\
	input.data_key = 0;\
	input.enc_dec = 0;\
	input.nBlocks = 1;\
	PACKET g(input);	g.addWORD(0x6565);	g.test();\
	DATA h("test");	h.test();\
	/*
	
	DATA FILE("test");
	FILE.assign(e);
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
	
	/*
	cout << "|\tREADING KEY\t";
	ENC.compute(FILE.readKEY());
	cout << "|\tKEY READ\t|" << endl;
	
	cout << "|\tREADING PACKET\t";
	ENC.compute(FILE.readPACKET());/*
	cout << "|\tPACKET READ\t|" << endl;
	//*/
	
	return 0;
}