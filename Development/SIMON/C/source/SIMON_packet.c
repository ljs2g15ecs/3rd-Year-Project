#include "SIMON_packet.h"

volatile TYPE(8)		inputCount = 0, outputCount = 0;

void	flushPACKET(PACKET *p)
{
	TYPE(8) i;
	for(i=0; i<sizeof(p->pBYTE); i++) p->pBYTE[i] = 0;
}

void	buildINPUT(PACKET *p)
{
	flushPACKET(p);
	p->pDATA.in_out = 0;
	p->pDATA.mode = MODE;
	p->pDATA.data_key = 0;	//	DEFAULT
	p->pDATA.enc_dec = 0;		//	DEFAULT
	p->pDATA.nBlocks = 0;
	p->pDATA.count = inputCount;
	TYPE(8) i;	for(i=0; i<4; i++)	p->pDATA.data[i].v = 0;
	inputCount++;
}

void	buildOUTPUT(PACKET *p, PACKET in)
{
	*p = in;
	p->pDATA.in_out = 1;
	outputCount++;
}

void	addWORD(PACKET *p, WORD w, TYPE(8) i)
{
	p->pDATA.data[i] = w;
	if(i>1)	p->pDATA.nBlocks = 1;
}

void	addKEY(PACKET *p, KEY k)
{
	TYPE(8) i;	for(i=0; i<M; i++)	p->pDATA.data[i] = k[i];
	p->pDATA.data_key = 1;
	if(M>2)	p->pDATA.nBlocks = 1;
}

void	addBLOCK(PACKET *p, BLOCK b)
{
	p->pDATA.data[0].v = b[0].v;
	p->pDATA.data[1].v = b[1].v;
	p->pDATA.data_key = 0;
}

void	addBLOCKS(PACKET *p, BLOCK b0, BLOCK b1)
{
	p->pDATA.data[0].v = b0[0].v;
	p->pDATA.data[1].v = b0[1].v;
	p->pDATA.data[2].v = b1[0].v;
	p->pDATA.data[3].v = b1[1].v;
	p->pDATA.data_key = 0;
	p->pDATA.nBlocks = 1;
}

void	buildSTREAM(DATA *d)
{
	d->inStream		= (PACKET *)malloc((d->sizePACKET+1)*sizeof(PACKET));
	d->outStream	= (PACKET *)malloc((d->sizePACKET+1)*sizeof(PACKET));
	
	buildINPUT(&d->inStream[0]);
	addKEY(&d->inStream[0], d->keyFILE);
	
	TYPE(64) i, a;
	for(i=1; i<=d->sizePACKET; i++)
	{
		buildINPUT(&d->inStream[i]);
		for(a=(i-1)*4; a<i*4; a++)	addWORD(&d->inStream[i], d->bufferWORD[a], a%4);
	}
}

char*	sprintPACKETDATA(PACKET *p)
{
	char tmp[1+(N/4)];
	char *str = (char *)malloc(sizeof(char)*(2+4*sizeof(tmp)));
	TYPE(64) pos = 0;
	
	pos += sprintf(&str[pos], "| ");
	SPRINTHEX(tmp, p->pDATA.data[0].v);	pos += sprintf(&str[pos], "%s ", tmp);
	SPRINTHEX(tmp, p->pDATA.data[1].v);	pos += sprintf(&str[pos], "%s ", tmp);
	SPRINTHEX(tmp, p->pDATA.data[2].v);	pos += sprintf(&str[pos], "%s ", tmp);
	SPRINTHEX(tmp, p->pDATA.data[3].v);	pos += sprintf(&str[pos], "%s ", tmp);
	
	//printf("\n<<%d>>\n", pos);
	//printf("\n<<%s>>\n", str);
	
	return str;
}

char*	sprintPACKET(PACKET *p)
{
	char tmp[10+N] = "";
	char *str = (char *)malloc(sizeof(char)*(30+sizeof(tmp)));
	TYPE(64) pos = 0;
	
	pos += sprintf(&str[pos], "| %01X ", p->pDATA.mode);
	
	if(p->pDATA.in_out)		pos += sprintf(&str[pos], "| OUT ");
	else					pos += sprintf(&str[pos], "| IN  ");
	
	if(p->pDATA.data_key)	pos += sprintf(&str[pos], "| KEY  ");
	else					pos += sprintf(&str[pos], "| DATA ");
	
	if(p->pDATA.enc_dec)	pos += sprintf(&str[pos], "| DEC ");
	else					pos += sprintf(&str[pos], "| ENC ");
	
	if(p->pDATA.nBlocks)	pos += sprintf(&str[pos], "| 2 ");
	else					pos += sprintf(&str[pos], "| 1 ");
	
	pos += sprintf(&str[pos], "| %02X ", p->pDATA.count);
	
	sprintf(tmp, "%s|", sprintPACKETDATA(p));
	pos += sprintf(&str[pos], tmp);
	
	return str;
}

char*	sprintSTREAM(DATA *d)
{
	char tmp[50+N] = "";
	char *str = (char *)malloc(sizeof(char)*((d->sizePACKET+1)*(50+N)));
	
	TYPE(64) i, pos = 0;
	for(i=0; i<=d->sizePACKET; i++)
	{
		sprintf(tmp, sprintPACKET(&d->inStream[i]));
		pos += sprintf(&str[pos], "%s\n", tmp);
	}
	
	return str;
}

char*	sprintPACKET_BYTE(PACKET *p)
{
	char *str = (char *)malloc(sizeof(char)*sizeof(PACKET));
	
	TYPE(64) i, pos = 0;
	
	for(i=0; i<sizeof(PACKET); i++)
	{
		pos += sprintf(&str[pos], "%c", (p->pBYTE[i] > 0 ? p->pBYTE[i]: 0xFE));
	}
	
	return str;
}

