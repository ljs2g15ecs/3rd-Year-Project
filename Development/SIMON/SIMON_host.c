#include "SIMON_host.h"

int		main()
{
	printf("Hello There!!!\n\r");
	
	printf("|\tN:\t%d\t|\tM:\t%d\t|\tT:\t%d\t|\n", N, M, T);
	printf("|\tW:\t%d\t|\tB:\t%d\t|\tK:\t%d\t|\n", sizeof(word)*8, sizeof(block)*8, sizeof(key)*8);

	word a = (0xA<<(N-4));
	
					PRINTHEX(a);	TAB();
	a = ROTL(a, 2);	PRINTHEX(a);	TAB();
	a = ROTR(a, 1);	PRINTHEX(a);	TAB();
	a = ROTR(a, 1);	PRINTHEX(a);	TAB();
	
	NEWLINE();
	word b = 12, c = (1<<N)-1;
	PRINTHEX(a);	TAB();	PRINTHEX(b);	TAB();	PRINTHEX(c);	TAB();
	c ^= a ^ b;
	PRINTHEX(a);	TAB();	PRINTHEX(b);	TAB();	PRINTHEX(c);	TAB();
	
	NEWLINE();		NEWLINE();
	
	return 0;
}

word	ROTL	(word x,	uint8_t n	)
{
	x = (x << n) | (x >> (N-n));
	return x &(1<<N)-1;
}

word	ROTR	(word x,	uint8_t n	)
{
	x = (x << (N-n)) | (x >> n);
	return x & (1<<N)-1;
}

word	F		(word x				)
{
	return ROTL(x,1) & ROTL(x,8) ^ ROTL(x, 2);
}

void	ROUND	(block *b,	word k		)
{
	word tmp = *b[0];
	*b[0] = *b[1] ^ F(*b[1]) ^ k;
	*b[1] = tmp;
}

void	KEXP	(key *k					)
{
	word tmp = ROTR(*k[M-1],3);
	if(M == 4)	tmp ^= *k[M-3];
	tmp ^= ROTR(tmp,1);
	//k[0] ^= tmp ^
}

word	ENCRYPT	(block p,	key k		)
{
	
}
	