#include "SIMON_file.h"

#include <stdio.h>

void	readFILE(DATA *d)
{
	d->ptrFILE = fopen(d->nameFILE, "rb");
	fseek(d->ptrFILE, 0, SEEK_END);
	d->sizeBYTE = ftell(d->ptrFILE);
	rewind(d->ptrFILE);
	
	d->sizeWORD = d->sizeBYTE/(N/8);
	d->sizePACKET = d->sizeWORD/4;
	
	d->bufferBYTE = (TYPE(8) *)malloc((d->sizeBYTE+1)*sizeof(TYPE(8)));
	
	TYPE(64) i;
	for(i=0; i<=d->sizeBYTE; i++)	d->bufferBYTE[i] = 0;
	for(i=0; i<d->sizeBYTE; i++)	fread(d->bufferBYTE+i, 1, 1, d->ptrFILE);
	
	fclose(d->ptrFILE);
}

char*	sprintBYTES_CHR(DATA *d)
{
	return d->bufferBYTE;
}

char*	sprintBYTES_HEX(DATA *d)
{
	char *str = (char *)malloc((((d->sizeBYTE+1)*5)+(d->sizeBYTE/4))*sizeof(char));
	TYPE(64) i, pos = 0;
	///*
	for(i=0; i<d->sizeBYTE; i++)
	{
		pos += sprintf(&str[pos], "|\t%02X\t", d->bufferBYTE[i]);
		if((i%4) == 3)	pos += sprintf(&str[pos], "|\n");
	}
	//*/
	
	return str;
}

char*	sprintWORDS_HEX(DATA *d)
{
	char* str = (char *)malloc((((d->sizeWORD+1)*7)+(d->sizeWORD/4))*sizeof(char));
	TYPE(64) i, pos = 0;
	for(i=0; i<d->sizeWORD; i++)
	{
		pos += sprintf(&str[pos] , "|\t%0*X\t", N/4, d->bufferWORD[i].v);
		if((i%4) == 3)	pos += sprintf(&str[pos], "|\n");
	}
	return str;
}

/*
void	writeBYTES_CHR(DATA *d, TYPE(8) *ext)
{
	
}

void	writeBYTES_HEX(DATA *d, TYPE(8) *ext)
{
	
}

void	writeBYTES_DEC(DATA *d, TYPE(8) *ext)
{
	
}
//*/