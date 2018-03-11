#include "SIMON_host.h"
#include "SIMON_host1.h"
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
	return (ROTL(x,1) & ROTL(x,8)) ^ ROTL(x, 2);
}

void	ROUND	(block b,	word k		)
{	
	word tmp = b[0];
	b[0].v = b[1].v ^ F(b[0]) ^ k.v;
	b[1] = tmp;
}

void	KEXP_PRE	(keys ks,	key k		)
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
}

void	KEXP_INL	(key k,	TYPE(8) i		)
{
	word tmp;
	tmp.v = ROTR(k[M-1], 3);
#if (M==4)
	tmp.v ^= k[M-3].v;
#endif
	tmp.v ^= ROTR(tmp, 1);
	tmp.v ^= ~k[0].v ^ (z[j][i % 62]) ^ 3;
	
	k[0] = k[1];
#if (M>2)
	k[1] = k[2];
#endif
#if (M>3)
	k[2] = k[3];
#endif
	k[M-1] = tmp;
}

void	ENCRYPT_PRE	(const block p,	block c,	key k		)
{
	c[0].v = p[0].v;
	c[1].v = p[1].v;
	
	keys ks;
	KEXP_PRE(ks, k);
	
	TYPE(8) i;
	for(i=0; i<T; i++)
	{
		ROUND(c, ks[i]);		
	}
}

void	ENCRYPT_INL	(const block p,	block c,	key k		)
{
	c[0].v = p[0].v;
	c[1].v = p[1].v;
	key ks;
	
	TYPE(8) i;
	for(i=M; i>0; i--)	ks[i-1].v = k[M-i].v;
	
	for(i=0; i<T; i++)
	{
		ROUND(c, ks[0]);
		KEXP_INL(ks, i);		
	}
}

void	DECRYPT_PRE	(const block c, block p,	key k		)
{
	p[0].v = c[1].v;
	p[1].v = c[0].v;
	
	keys ks;
	KEXP_PRE(ks, k);
	
	TYPE(8) i;
	for(i=T; i>0; i--)
	{
		ROUND(p, ks[i-1]);
	}
	word tmp = p[0];
	p[0].v = p[1].v;
	p[1].v = tmp.v;
}

///////////////////////////////////////////////////////////

INTERNAL	STATE;	//STATE.count = 0;
TYPE(8)		inputCount = 0, outputCount = 0;

void	buildInputPACKET(PACKET *p)
{
	p->in_out = 0;
	p->mode = MODE;
	p->data_key = 0;	//	DEFAULT
	p->enc_dec = 0;		//	DEFAULT
	p->FILLER0 = 0;
	p->count = inputCount;
	TYPE(8) i;
	for(i=0; i<4; i++)	p->data[i].v = 0;
	inputCount++;
}

void	buildOutputPACKET(PACKET *p, PACKET in)
{
	*p = in;
	p->in_out = 1;
	outputCount++;
}

void	addBlock(PACKET *p, block b)
{
	p->data[0].v = b[0].v;
	p->data[1].v = b[1].v;
	p->data_key = 0;
}

void	addKey(PACKET *p, key k)
{
	TYPE(8) i;
	for(i=0; i<M; i++)	p->data[i] = k[i];
	p->data_key = 1;
}

PACKET	CIPHER(PACKET inData)
{
	PACKET outData;
	buildOutputPACKET(&outData, inData);
	if((!inData.in_out) && (inData.mode == MODE) && (inData.count == STATE.count))
	{
		if(inData.data_key)		loadKey(inData.data);
		else if(STATE.doneKey)
		{
			if(inData.enc_dec)	decryptData(inData.data);
			else				encryptData(inData.data);
			addBlock(&outData, STATE.o);
		}
		else					printf("\nERROR");
		STATE.count++;
		return outData;
	}
}

void	loadKey(word in[4])
{
	printf("\nLOAD KEY");
	///*
	word tmp;
	int8_t i;
	for(i=M; i>0; i--)	STATE.ks[i-1] = in[M-i];
	
	for(i=M; i<T; i++)
	{
		tmp.v = ROTR(STATE.ks[i-1], 3);
#if (M == 4)
		tmp.v ^= STATE.ks[i-3].v;
#endif
		tmp.v ^= ROTR(tmp, 1);
		STATE.ks[i].v = ~STATE.ks[i-M].v ^ tmp.v ^ (z[j][(i-M) % 62]) ^ 3;
	}
	//*/
	STATE.doneKey = 1;
}

void	encryptData(word in[4])
{
	printf("\nENCRYPT DATA");
	///*
	STATE.o[0] = in[0];
	STATE.o[1] = in[1];
	
	TYPE(8) i;
	for(i=0; i<T; i++)
	{
		ROUND(STATE.o, STATE.ks[i]);		
	}
	//*/
}

void	decryptData(word in[4])
{
	printf("\nDECRYPT DATA");
	///*
	STATE.o[0] = in[1];
	STATE.o[1] = in[0];
	
	TYPE(8) i;
	for(i=T; i>0; i--)
	{
		ROUND(STATE.o, STATE.ks[i-1]);
	}
	word tmp = STATE.o[0];
	STATE.o[0] = STATE.o[1];
	STATE.o[1] = tmp;
	//*/
}
