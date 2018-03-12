#include "SIMON_definitions.h"
#include "SIMON_cipher.h"
#include "SIMON_packet.h"

TYPE(N)	ROTL	(WORD x,	TYPE(8) n	)
{
	return (x.v << n) | (x.v >> (N-n));
}

TYPE(N)	ROTR	(WORD x,	TYPE(8) n	)
{
	return (x.v << (N-n)) | (x.v >> n);
}

TYPE(N)	F		(WORD x					)
{
	return (ROTL(x,1) & ROTL(x,8)) ^ ROTL(x, 2);
}

void	ROUND	(BLOCK b,	WORD k		)
{	
	WORD tmp = b[0];
	b[0].v = b[1].v ^ F(b[0]) ^ k.v;
	b[1] = tmp;
}

INTERNAL	STATE;

void	CIPHER(PACKET inDATA, PACKET *outDATA)
{
	TYPE(8) i;
	buildOUTPUT(outDATA, inDATA);
	if((!inDATA.in_out) && (inDATA.mode == MODE) && (inDATA.count == STATE.count))
	{
		if(inDATA.data_key)		loadKEY(inDATA.data);
		else if(STATE.doneKey)
		{
			for(i=0; i<=inDATA.nBlocks+1; i+=2)
			{
				if(inDATA.enc_dec)	decryptDATA(inDATA.data, i);
				else				encryptDATA(inDATA.data, i);
				outDATA->data[i] = STATE.o[0];
				outDATA->data[i+1] = STATE.o[1];
			}
		}
		STATE.count++;
	}
}

const TYPE(8) Z[5][62] = {
	{1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0},
	{1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0},
	{1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,0,1,1},
	{1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,1,1,1},
	{1,1,0,1,0,0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,1,1,1,0,1,1,1,1}
};

void	loadKEY(WORD in[4])
{
	WORD tmp;
	int8_t i;
	for(i=M; i>0; i--)	STATE.ks[i-1] = in[M-i];
	
	for(i=M; i<T; i++)
	{
		tmp.v = ROTR(STATE.ks[i-1], 3);
#if (M == 4)
		tmp.v ^= STATE.ks[i-3].v;
#endif
		tmp.v ^= ROTR(tmp, 1);
		STATE.ks[i].v = ~STATE.ks[i-M].v ^ tmp.v ^ (Z[j][(i-M) % 62]) ^ 3;
	}
	STATE.doneKey = 1;
}

void	encryptDATA(WORD in[4], TYPE(8) i)
{
	STATE.o[0] = in[i];
	STATE.o[1] = in[i+1];
	
	for(i=0; i<T; i++)
	{
		ROUND(STATE.o, STATE.ks[i]);		
	}
}

void	decryptDATA(WORD in[4], TYPE(8) i)
{
	STATE.o[0] = in[i+1];
	STATE.o[1] = in[i];
	
	for(i=T; i>0; i--)
	{
		ROUND(STATE.o, STATE.ks[i-1]);
	}
	
	WORD tmp = STATE.o[0];
	STATE.o[0] = STATE.o[1];
	STATE.o[1] = tmp;
}