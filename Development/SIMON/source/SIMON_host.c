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
	/*
	PRINTHEX(x.v);			NEWLINE();	NEWLINE();
	PRINTHEX(ROTL(x,1));	NEWLINE();
	PRINTHEX(ROTL(x,8));	NEWLINE();
	PRINTHEX(ROTL(x,1) & ROTL(x,8));	NEWLINE();	NEWLINE();
	PRINTHEX(ROTL(x,1) & ROTL(x,8));	NEWLINE();
	PRINTHEX(ROTL(x,2));	NEWLINE();
	PRINTHEX((ROTL(x,1) & ROTL(x,8)) ^ ROTL(x, 2));	NEWLINE();
	*/
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
		
		/*
		PRINTHEX(ks[i-3].v);	TAB();	PRINTHEX(ks[i-2].v);	TAB();
		PRINTHEX(ks[i-1].v);	TAB();	PRINTHEX(ks[i].v);		TAB();
		PRINTHEX(ks[i-M].v);
		NEWLINE();
		*/
	}
	
	/*
	for(i=0; i<T; i++)
	{
		PRINTHEX(ks[i].v);	NEWLINE();
	}*/
}

void	ENCRYPT	(const block p,	block c,	key k		)
{
	c[0].v = p[0].v;
	c[1].v = p[1].v;
	key ks;
	//keys ks;
	//KEXP(ks, k);
	
	word tmp;
	TYPE(8) i, l;
	for(i=M; i>0; i--)	ks[i-1].v = k[M-i].v;
	
	for(i=0; i<T; i++)
	{
		/*
		PRINTHEX(c[0].v);			PRINTHEX(c[1].v);	TAB();
		for(l=0; l<M; l++)	{		PRINTHEX(ks[l]);	TAB();	}
		NEWLINE();		
		//*/
		ROUND(c, ks[0]);
		/*
		PRINTHEX(c[0].v);			PRINTHEX(c[1].v);	TAB();
		for(l=0; l<M; l++)	{		PRINTHEX(ks[l]);	TAB();	}
		NEWLINE();	NEWLINE();
		//*/
		
		///*
		//	Testing Key Expansion in Loop
		tmp.v = ROTR(ks[M-1], 3);
#if (M==4)
		tmp.v ^= ks[M-3].v;
#endif
		tmp.v ^= ROTR(tmp, 1);
		tmp.v = ~ks[0].v ^ tmp.v ^ (z[j][i % 62]) ^ 3;
		
		/*
		PRINTHEX(c[0].v);			PRINTHEX(c[1].v);	TAB();
		//for(l=0; l<M; l++)	{		PRINTHEX(ks[l]);	TAB();	}
		PRINTHEX(tmp.v);	TAB();
		PRINTHEX(ks[3]);	TAB();	PRINTHEX(ks[2]);	TAB();
		PRINTHEX(ks[1]);	TAB();	PRINTHEX(ks[0]);	TAB();
		NEWLINE();		
		//*/
		ks[0] = ks[1];
#if (M>2)
		ks[1] = ks[2];
#endif
#if (M>3)
		ks[2] = ks[3];
#endif
		ks[M-1] = tmp;		
	}
}
