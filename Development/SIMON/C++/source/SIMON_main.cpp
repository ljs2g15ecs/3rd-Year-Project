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
	KEY e;			e.test();
	//KEY_S f;		f.test();
	PACKET g;		g.test();
	DATA h("test");	h.test();
	
	return 0;
}