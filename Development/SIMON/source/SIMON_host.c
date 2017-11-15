#include "SIMON_host.h"
#include <stdio.h>

const TYPE(8) z[5][62] = {
	{1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0},
	{1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0},
	{1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,0,1,1},
	{1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,1,1,1},
	{1,1,0,1,0,0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,1,1,1,0,1,1,1,1}
};

TYPE(N)	ROTL	(word x,	uint8_t n	)
{
	return (x.v << n) | (x.v >> (N-n));
}

TYPE(N)	ROTR	(word x,	uint8_t n	)
{
	return (x.v << (N-n)) | (x.v >> n);
}

TYPE(N)	F		(word x					)
{
	/*PRINTHEX(x.v);			NEWLINE();	NEWLINE();
	PRINTHEX(ROTL(x,1));	NEWLINE();
	PRINTHEX(ROTL(x,8));	NEWLINE();
	PRINTHEX(ROTL(x,1) & ROTL(x,8));	NEWLINE();	NEWLINE();
	PRINTHEX(ROTL(x,1) & ROTL(x,8));	NEWLINE();
	PRINTHEX(ROTL(x,2));	NEWLINE();
	PRINTHEX((ROTL(x,1) & ROTL(x,8)) ^ ROTL(x, 2));	NEWLINE();*/
	return (ROTL(x,1) & ROTL(x,8)) ^ ROTL(x, 2);
}

void	ROUND	(block b,	word k		)
{
	/*
	PRINTHEX(b[0].v);	TAB();	PRINTHEX(b[1].v);	TAB();
	PRINTHEX(k.v);		NEWLINE();					NEWLINE();
	
	PRINTHEX(F(b[1]));	NEWLINE();
	PRINTHEX(k.v);		NEWLINE();
	PRINTHEX(F(b[1]) ^ k.v);	NEWLINE();
	PRINTHEX(b[1]);	NEWLINE();
	PRINTHEX(b[1].v ^ F(b[1]) ^ k.v);	NEWLINE();
	*/
	
	word tmp = b[0];
	b[0].v = b[1].v ^ F(b[0]) ^ k.v;
	b[1] = tmp;
	
	/*
	PRINTHEX(b[0].v);	TAB();	PRINTHEX(b[1].v);	TAB();
	PRINTHEX(k.v);		NEWLINE();
	*/
}

void	KEXP	(keys ks,	key k		)
{
	word tmp;
	int8_t i;
	for(i=M; i>0; i--)	ks[i-1].v = k[M-i].v;
	
	for(i=M; i<T; i++)
	{
		tmp.v = ROTR(ks[i-1], 3);
#if (M == 4)
		tmp.v ^= ks[i-3].v;
#endif
		tmp.v ^= ROTR(tmp, 1);
		ks[i].v = ~ks[i-M].v ^ tmp.v ^ (z[j][(i-M) % 62]) ^ 3;
	}
	
	/*for(i=0; i<T; i++)
	{
		PRINTHEX(ks[i].v);	NEWLINE();
	}*/
}

void	ENCRYPT	(const block p,	block c,	key k		)
{
	c[0].v = p[0].v;
	c[1].v = p[1].v;
	//keys ks;
	//KEXP(ks, k);
	
	word tmp;
	TYPE(8) i;
	for(i=0; i<T; i++)
	{
		/*
		PRINTHEX(c[0].v);	TAB();	PRINTHEX(c[1].v);	TAB();
		PRINTHEX(ks[i].v);	NEWLINE();
		*/
		ROUND(c, ks[i]);
		/*
		PRINTHEX(c[0].v);	TAB();	PRINTHEX(c[1].v);	TAB();
		PRINTHEX(ks[i].v);	NEWLINE();					NEWLINE();
		*/
	}
}
