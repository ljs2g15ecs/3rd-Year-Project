#include <stdio.h>

#include "SIMON_host.h"

int		main()
{
	printf("Hello There!!!\n\r");
	
	printf("|\tN:\t%d\t|\tM:\t%d\t|\tT:\t%d\t|\n", N, M, T);
	printf("|\tW:\t%d\t|\tB:\t%d\t|\tK:\t%d\t|\n", sizeof(word)*8, sizeof(block)*8, sizeof(key)*8);

	word a;
	a.v = 0xA<<(N-4);
	
						PRINTHEX(a);	TAB();
	a.v = ROTL(a, 2);	PRINTHEX(a);	TAB();
	a.v = ROTR(a, 1);	PRINTHEX(a);	TAB();
	a.v = ROTR(a, 1);	PRINTHEX(a);	TAB();
	
	NEWLINE();
	word b, c;
	b.v = 12, c.v = (1<<N)-4;
	PRINTHEX(a);	TAB();	PRINTHEX(b);	TAB();	PRINTHEX(c);	TAB();
	c.v ^= a.v ^ b.v;		NEWLINE();
	PRINTHEX(a);	TAB();	PRINTHEX(b);	TAB();	PRINTHEX(c);	TAB();
	
	NEWLINE();		NEWLINE();
	
	a.v = 0xA3C2;
	b = a;
							PRINTHEX(a);	NEWLINE();
	a.v = ROTL(a, 1);		PRINTHEX(a);	NEWLINE();				a.v = ROTR(a, 1);
	a.v = ROTL(a, 8);		PRINTHEX(a);	NEWLINE();				a.v = ROTR(a, 8);
	a.v = ROTL(a, 2);		PRINTHEX(a);	NEWLINE();				a.v = ROTR(a, 2);
	
	c.v = F(b);
							PRINTHEX(c);	NEWLINE();
	
	NEWLINE();		NEWLINE();

#if	defined S32_64	
	key k =		{ 0x1918, 0x1110, 0x0908, 0x0100	};
	block p =	{ 0x6565, 0x6877					};
#endif
#if	defined S48_72	
	key k =		{ 0x121110, 0x0A0908, 0x020100		};
	block p =	{ 0x612067, 0x6E696C				};
#endif
	
	TYPE(8) i;
	for(i=0; i<M; i++)		PRINTHEX(k[i].v);	NEWLINE();
	PRINTHEX(p[0].v);		PRINTHEX(p[1].v);	NEWLINE();
	
	block cipher;
	PRINTHEX(cipher[0].v);	PRINTHEX(cipher[1].v);	NEWLINE();
	
	ENCRYPT(p, cipher, k);
	PRINTHEX(cipher[0].v);	PRINTHEX(cipher[1].v);	NEWLINE();
	
	return 0;
}