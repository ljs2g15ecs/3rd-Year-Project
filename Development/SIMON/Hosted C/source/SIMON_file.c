#include "SIMON_file.h"
#include "SIMON_host.h"
#include "SIMON_host1.h"

typedef struct 	DATA
{
	TYPE(8)	*byteBuf;
	TYPE(N)	*wordBuf;
	TYPE(64)	filelen;
}				DATA;

DATA read;
PACKET *inStream;

void	readFile()
{
	FILE *fileptr;
    unsigned int i, a;

    fileptr = fopen("test", "rb");         
    fseek(fileptr, 0, SEEK_END);          
    read.filelen = ftell(fileptr);            
    rewind(fileptr);                      
    read.byteBuf = (TYPE(8) *)malloc((read.filelen)*sizeof(TYPE(8))); 
	read.wordBuf = (TYPE(N) *)malloc((read.filelen/(N/8))*sizeof(TYPE(N)));

    ///*
	for(i = 0; i < read.filelen; i++) {
       fread(read.byteBuf+i, 1, 1, fileptr); 
	}
	//*/

    printf("File len: %ld\n", read.filelen);
	
	for(i=0; i<read.filelen; i++)
	{
		printf("\n%0*X", 2, read.byteBuf[i]);
	}
	
	for(i=0; i<read.filelen/(N/8); i++)
	{
		read.wordBuf[i] = 0;
		for(a=0; a<(N/8); a++)	read.wordBuf[i] += read.byteBuf[(i*(N/8)+a)] << 8*(((N/8)-1)-a);
		printf("\n%0*X", N/4, read.wordBuf[i]);
	}

    fclose(fileptr); // Close the file
}

void	buildStream(DATA *in)
{
	unsigned int i, a;
	inStream = (PACKET *)malloc((read.filelen/(N/2))*sizeof(PACKET));
	
	for(i=0; i<read.filelen/(N/2); i++)
	{
		buildInputPACKET(&inStream[i]);
	}
}