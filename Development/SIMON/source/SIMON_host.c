#include "SIMON_host.h"

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
	return (ROTL(x,1) & ROTL(x,8)) ^ ROTL(x, 2);
}

void	ROUND	(block *b,	word k		)
{
	word tmp = *b[0];
	b[0]->v = b[1]->v ^ F(*b[1]) ^ k.v;
	*b[1] = tmp;
}

void	KEXP	(keys *ks,	key *k		)
{
	word tmp;
	TYPE(8) i;
	for(i=0; i<M; i++)	*ks[i] = *k[i];
	
	for(i=M; i<T; i++)
	{
		tmp.v = ROTR(*ks[i-1], 3);
#if (M == 4)
		tmp.v ^= ks[i-3]->v;
#endif
		tmp.v ^= ROTR(tmp, 1);
		ks[i]->v = ks[i-M]->v ^ tmp.v ^ 3;
	}
}

void	ENCRYPT	(block p,	block c,	key k		)
{
	c[0].v = p[0].v;
	c[1].v = p[1].v;
	keys ks;
	//KEXP(&ks, k);
	
	/*TYPE(8) i;
	for(i=0; i<T; i++)
	{
		ROUND(&c, ks[i]);
	}*/
}
