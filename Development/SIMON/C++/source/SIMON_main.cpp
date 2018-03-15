#include "SIMON_definitions.h"

#include <iostream>
using namespace std;

int		main()
{
	WORD a = 0x6565;			a.test();
	BLOCK b(0x6565, 0x6877);	b.test();
	KEY c;						c.test();
}