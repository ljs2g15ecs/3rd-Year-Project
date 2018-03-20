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
	
	WORD a;			a.test();
	BLOCK b;		b.test();
	KEY c;			c.test();
	//KEY_S d;		d.test();
	PACKET e;		e.test();
	DATA f("test");	f.test();
}