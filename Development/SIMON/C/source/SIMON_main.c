#include "SIMON_definitions.h"
#include "SIMON_cipher.h"
#include "SIMON_packet.h"
#include "SIMON_file.h"

int		main()
{
	DATA test;
	test.nameFILE = "test";
	
	readFILE(&test);
	printf("%s\n", sprintBYTES_CHR(&test));
	printf("%s\n", sprintBYTES_HEX(&test));
	
	printf("%s\n", sprintWORDS_HEX(&test));
	
	PACKET ptest;
	buildINPUT(&ptest);
	printf("%s\n", sprintPACKETDATA(&ptest));
}