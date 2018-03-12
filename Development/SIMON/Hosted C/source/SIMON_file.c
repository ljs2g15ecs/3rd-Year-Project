#include "SIMON_file.h"
#include "SIMON_host.h"
#include "SIMON_test.h"
#include "SIMON_host1.h"

typedef struct 	DATA
{
	union
	{
		TYPE(8)	*byteBuf;
		TYPE(N)	*wordBuf;
	};
	TYPE(64)	byteLength;
	TYPE(32)	wordLength;
	TYPE(8)		PACKETLength;
	char 		*fName;
	FILE 		*fileptr;
}				DATA;

DATA read;

PACKET *inStream;
PACKET *outStream;

void	readFile()
{
    unsigned int i, a;

	read.fName = "test";
    read.fileptr = fopen(read.fName, "rb");         
    fseek(read.fileptr, 0, SEEK_END);          
    read.byteLength = ftell(read.fileptr);
	read.wordLength = read.byteLength/(N/8);
	read.PACKETLength = read.wordLength/4;
    rewind(read.fileptr);                      
    read.byteBuf = (TYPE(8) *)malloc((read.byteLength)*sizeof(TYPE(8))); 
	read.wordBuf = (TYPE(N) *)malloc((read.byteLength/(N/8))*sizeof(TYPE(N)));

	for(i = 0; i < read.byteLength; i++) {
       fread(read.byteBuf+i, 1, 1, read.fileptr); 
	}

	/*
    printf("File len: %ld\n", read.byteLength);
	
	for(i=0; i<read.byteLength; i++)
	{
		printf("\n%0*X", 2, read.byteBuf[i]);
	}
	
	for(i=0; i<read.wordLength; i++)
	{
		printf("\n%0*X", N/4, read.wordBuf[i]);
	}
	//*/

    fclose(read.fileptr); // Close the file
	
	buildStream(&read);
}

void	buildStream(DATA *in)
{
	unsigned int i, a;
	inStream = (PACKET *)malloc((read.PACKETLength+2)*sizeof(PACKET));
	outStream = (PACKET *)malloc((read.PACKETLength+2)*sizeof(PACKET));
	
	buildInputPACKET(&inStream[0]);
	key k = {0,0,0,0};
	addKey(&inStream[0], k);
	
	for(i=1; i<=read.PACKETLength; i++)
	{
		buildInputPACKET(&inStream[i]);
		inStream[i].nBlocks = 1;
		for(a=0; a<4; a++)	addWord(&inStream[i], read.wordBuf[i-1+a], a);
	}
	
	for(i=0; i<=read.PACKETLength; i++)
	{
		buildOutputPACKET(&outStream[i], inStream[i]);
		outStream[i] = CIPHER(inStream[i]);
		printSTREAM(inStream[i], outStream[i]);
	}
	
	buildInputPACKET(&inStream[read.PACKETLength+1]);
	for(i=0; i<4; i++)	inStream[read.PACKETLength+1].data[i] = outStream[read.PACKETLength].data[i];
	inStream[read.PACKETLength+1].enc_dec = 1;
	inStream[read.PACKETLength+1].nBlocks = 1;
	outStream[read.PACKETLength+1] = CIPHER(inStream[read.PACKETLength+1]);
	
	printSTREAM(inStream[read.PACKETLength+1], outStream[read.PACKETLength+1]);
}