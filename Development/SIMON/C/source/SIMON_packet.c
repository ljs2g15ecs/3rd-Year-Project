#include "SIMON_definitions.h"
#include "SIMON_packet.h"

TYPE(8)		inputCount = 0, outputCount = 0;

void	buildINPUT(PACKET *p)
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

void	buildOUTPUT(PACKET *p, PACKET in)
{
	*p = in;
	p->in_out = 1;
	outputCount++;
}

void	addWORD(PACKET *p, TYPE(N) w, TYPE(8) i)
{
	p->data[i].v = w;
}

void	addKEY(PACKET *p, KEY k)
{
	TYPE(8) i;	for(i=0; i<M; i++)	p->data[i] = k[i];
	p->data_key = 1;
}

void	addBLOCK(PACKET *p, BLOCK b)
{
	p->data[0].v = b[0].v;
	p->data[1].v = b[1].v;
	p->data_key = 0;
}

void	addBLOCKS(PACKET *p, BLOCK b0, BLOCK b1)
{
	p->data[0].v = b0[0].v;
	p->data[1].v = b0[1].v;
	p->data[2].v = b1[0].v;
	p->data[3].v = b1[1].v;
	p->data_key = 0;
	p->nBlocks = 1;
}