#include "SIMON_host.h"
#include "SIMON_file.h"

word	readWORD(char* fileNAME, int pos)
{
	FILE *filePTR;
	
	filePTR = fopen("test.txt", "rb");
	fseek(filePTR, 0, pos);
	
	char* buffer;
	buffer = (char*)malloc(((N/8)+1)*sizeof(char));
	fread(buffer, (N/8), 1, filePTR);
	
	TYPE(8) i;
	for(i=0; i<(N/8); i++)
	{
		printf("\n<%c>", buffer[i]);
	}
	
	fclose(filePTR);
}

