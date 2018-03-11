#include "SIMON_test.h"
#include "SIMON_host.h"
#include <stdio.h>

#if	defined S32_64	
	key 	k	=	{	0x1918, 0x1110,
						0x0908, 0x0100							};
	block 	p	=	{	0x6565, 0x6877							};
	block 	c	=	{	0xC69B, 0xE9BB							};
#elif	defined S48_72	
	key 	k	=	{	0x121110, 0x0A0908,
						0x020100								};
	block 	p 	=	{	0x612067, 0x6E696C						};
	block 	c	=	{	0xDAE5AC, 0x292CAC						};
#elif	defined	S48_96
	key 	k	=	{	0x1A1918, 0x121110,
						0x0A0908, 0x020100						};
	block	p	=	{	0x726963, 0x20646E						};
	block	c	=	{	0x6E06A5, 0xACF156						};
#elif	defined S64_96
	key 	k	=	{	0x13121110, 0x0B0A0908,
						0x03020100								};
	block	p	=	{	0x6F722067, 0x6E696C63					};
	block	c	=	{	0x5CA2E27F, 0x111A8FC8					};
#elif	defined S64_128
	key 	k	=	{	0x1B1A1918, 0x13121110,
						0x0B0A0908, 0x03020100					};
	block	p	=	{	0x656B696C, 0x20646E75					};
	block	c	=	{	0x44C8FC20, 0xB9DFA07A					};
#elif	defined S96_96
	key 	k	=	{	0x0D0C0B0A0908, 0x050403020100			};
	block	p	=	{	0x2072616C6C69, 0x702065687420			};
	block	c	=	{	0x602807A462b4, 0x69063D8FF082			};
#elif	defined S96_144
	key 	k	=	{	0x151413121110, 0x0D0C0B0A0908,
						0x050403020100							};
	block	p	=	{	0x746168742074, 0x73756420666f			};
	block	c	=	{	0xECAD1C6C451E, 0x3f59C5DB1AE9			};
#elif	defined S128_128
	key 	k	=	{	0x0F0E0D0C0B0A0908, 0x0706050403020100	};
	block	p	=	{	0x6373656420737265, 0x6C6C657661727420	};
	block	c	=	{	0x49681B1E1E54FE3F, 0x65AA832AF84E0BBC	};
#elif	defined S128_192
	key 	k	=	{	0x1716151413121110, 0x0F0E0D0C0B0A0908,
						0x0706050403020100						};
	block	p	=	{	0x206572656874206E, 0x6568772065626972	};
	block	c	=	{	0xC4AC61EFFCDC0D4F, 0x6C9C8D6E2597b85B	};
#elif	defined S128_256
	key 	k	=	{	0x1F1E1D1C1B1A1918, 0x1716151413121110,
						0x0F0E0D0C0B0A0908, 0x0706050403020100	};
	block	p	=	{	0x74206E69206D6F6F, 0x6D69732061207369	};
	block	c	=	{	0x8D2B5579AFC8A3A0, 0x3BF72A87EfE7b868	};
#endif

void	test()
{
	///*
	printf("|\tTESTING PRE KEY EXPANSION\t\t|");
	
	NEWLINE();
	printf("|\tKEY:\t\t");
	TYPE(8) i;
	for(i=0; i<M; i++)	{	PRINTHEX(k[i].v);	}
	printf("\t|\n");
	
	block cipher, plain;
	cipher[0].v = 0;
	cipher[1].v = 0;
	printf("|\tPLAIN->CIPHER:\t");
	PRINTHEX(p[0].v);		PRINTHEX(p[1].v);
	printf("->");
	PRINTHEX(cipher[0].v);	PRINTHEX(cipher[1].v);
	printf("\t|\tSTART\t|\n");
	
	ENCRYPT_PRE(p, cipher, k);
	printf("|\tPLAIN->CIPHER:\t");
	PRINTHEX(p[0].v);		PRINTHEX(p[1].v);
	printf("->");
	PRINTHEX(cipher[0].v);	PRINTHEX(cipher[1].v);
	printf("\t|\tENCRYPT\t|\n");
	
	printf("|\tPLAIN->CIPHER:\t");
	PRINTHEX(p[0].v);		PRINTHEX(p[1].v);
	printf("->");
	PRINTHEX(c[0].v);	PRINTHEX(c[1].v);
	printf("\t|\tTEST\t|\n");
	
	///*
	plain[0].v = 0;
	plain[1].v = 0;
	DECRYPT_PRE(c, plain, k);
	printf("|\tPLAIN<-CIPHER:\t");
	PRINTHEX(plain[0].v);		PRINTHEX(plain[1].v);
	printf("<-");
	PRINTHEX(c[0].v);	PRINTHEX(c[1].v);
	printf("\t|\tDECRYPT\t|\n");
	//*/
	
	printf("|\tTESTING IN LOOP KEY EXPANSION\t\t|");
	
	NEWLINE();
	printf("|\tKEY:\t\t");
	for(i=0; i<M; i++)	{	PRINTHEX(k[i].v);}
	printf("\t|\n");
	
	cipher[0].v = 0;
	cipher[1].v = 0;
	printf("|\tPLAIN->CIPHER:\t");
	PRINTHEX(p[0].v);		PRINTHEX(p[1].v);
	printf("->");
	PRINTHEX(cipher[0].v);	PRINTHEX(cipher[1].v);
	printf("\t|\tSTART\t|\n");
	
	ENCRYPT_INL(p, cipher, k);
	printf("|\tPLAIN->CIPHER:\t");
	PRINTHEX(p[0].v);		PRINTHEX(p[1].v);
	printf("->");
	PRINTHEX(cipher[0].v);	PRINTHEX(cipher[1].v);
	printf("\t|\tENCRYPT\t|\n");
	
	printf("|\tPLAIN->CIPHER:\t");
	PRINTHEX(p[0].v);		PRINTHEX(p[1].v);
	printf("->");
	PRINTHEX(c[0].v);	PRINTHEX(c[1].v);
	printf("\t|\tTEST\t|\n");
	//*/
	
	/*
	word a;
	a = k[0];
	PRINTHEX(a.v);
	//*/
}

void	test1()
{
	printf("WORD SIZE:\t%d\n", sizeof(word));
	printf("BLOCK SIZE:\t%d\n", sizeof(block));
	printf("KEY SIZE:\t%d\n", sizeof(key));
	printf("KEY SCHEDULE SIZE:\t%d\n", sizeof(keys));
	
	printf("-----------------------------------\n");
	
	printf("INTERNAL SIZE:\t%d\n", sizeof(INTERNAL));
	printf("PACKET SIZE:\t%d\n", sizeof(PACKET));
	
	printf("-----------------------------------\n");
	
	PACKET inStream[2], outStream[2];
	
	buildInputPACKET(&inStream[0]);	addKey(&inStream[0], k);
	buildInputPACKET(&inStream[1]);	addBlock(&inStream[1], p);
	
	outStream[0] = CIPHER(inStream[0]);
	outStream[1] = CIPHER(inStream[1]);
	
	printSTREAM(inStream[0], outStream[0]);
	printSTREAM(inStream[1], outStream[1]);
}

void	printPACKETDATA(PACKET p)
{
	printf("|\t");	PRINTHEX(p.data[0].v);
	printf("\t");	PRINTHEX(p.data[1].v);
	printf("\t");	PRINTHEX(p.data[2].v);
	printf("\t");	PRINTHEX(p.data[3].v);	printf("\t");
}

void	printSTREAM(PACKET in, PACKET out)
{
	if((in.in_out != out.in_out) && (in.mode == out.mode) && (in.data_key == out.data_key) && (in.enc_dec == out.enc_dec) && (in.count == out.count))
	NEWLINE();
	printf("|\t%d\t", in.mode);
	if(in.data_key)	printf("|\tKEY\t");
	else			printf("|\tDATA\t");
	if(in.enc_dec)	printf("|\tDEC\t");
	else			printf("|\tENC\t");
	printf("|\t%d\t", in.count);
	printPACKETDATA(in);	printPACKETDATA(out);
	printf("|");
}