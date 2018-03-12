#include "SIMON_host.h"
#include "SIMON_host1.h"

#include <stdio.h>

INTERNAL	STATE;
TYPE(8)		inputCount = 0, outputCount = 0;

const TYPE(8) Z[5][62] = {
	{1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0},
	{1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0},
	{1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,0,1,1},
	{1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,1,1,1},
	{1,1,0,1,0,0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,1,1,1,0,1,1,1,1}
};

void	buildInputPACKET(PACKET *p)
{
	p->in_out = 0;
	p->mode = MODE;
	p->data_key = 0;	//	DEFAULT
	p->enc_dec = 0;		//	DEFAULT
	p->nBlocks = 0;
	p->count = inputCount;
	TYPE(8) i;	for(i=0; i<4; i++)	p->data[i].v = 0;
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

void	addBlocks(PACKET *p, block b0, block b1)
{
	p->data[0].v = b0[0].v;
	p->data[1].v = b0[1].v;
	p->data[2].v = b1[0].v;
	p->data[3].v = b1[1].v;
	p->data_key = 0;
	p->nBlocks = 1;
}

void	addKey(PACKET *p, key k)
{
	TYPE(8) i;	for(i=0; i<M; i++)	p->data[i] = k[i];
	p->data_key = 1;
}

PACKET	CIPHER(PACKET inData)
{
	PACKET outData;
	buildOutputPACKET(&outData, inData);
	TYPE(8) i;
	if((!inData.in_out) && (inData.mode == MODE) && (inData.count == STATE.count))
	{
		if(inData.data_key)		loadKey(inData.data);
		else if(STATE.doneKey)
		{
			for(i=0; i<=inData.nBlocks+1; i+=2)
			{
				if(inData.enc_dec)	decryptData(inData.data, i);
				else				encryptData(inData.data, i);
				outData.data[i] = STATE.o[0];
				outData.data[i+1] = STATE.o[1];
			}
		}
		STATE.count++;
		return outData;
	}
}

void	loadKey(word in[4])
{
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
		STATE.ks[i].v = ~STATE.ks[i-M].v ^ tmp.v ^ (Z[j][(i-M) % 62]) ^ 3;
	}
	STATE.doneKey = 1;
}

void	encryptData(word in[4], TYPE(8) i)
{
	STATE.o[0] = in[i];
	STATE.o[1] = in[i+1];
	
	for(i=0; i<T; i++)
	{
		ROUND(STATE.o, STATE.ks[i]);		
	}
}

void	decryptData(word in[4], TYPE(8) i)
{
	STATE.o[0] = in[i+1];
	STATE.o[1] = in[i];
	
	for(i=T; i>0; i--)
	{
		ROUND(STATE.o, STATE.ks[i-1]);
	}
	
	word tmp = STATE.o[0];
	STATE.o[0] = STATE.o[1];
	STATE.o[1] = tmp;
}