#include "SIMON_definitions.h"
#include "SIMON_cipher.h"
#include "SIMON_packet.h"
#include "SIMON_file.h"

int		main()
{
	DATA test;
	test.nameFILE = "test";
	
	test.keyFILE[0].v = 0;
	test.keyFILE[1].v = 0;
	test.keyFILE[2].v = 0;
	test.keyFILE[3].v = 0;
	
	readFILE(&test);
	printf("%s\n", sprintBYTES_CHR(&test));
	printf("%s\n", sprintBYTES_HEX(&test));
	
	printf("%s\n", sprintWORDS_HEX(&test));
	
	buildSTREAM(&test);
	printf("%s\n", sprintSTREAM(&test));
	
	printf("PACKET SIZE:\t%d\n", sizeof(PACKET));

	TYPE(8) i;
	for(i=0; i<sizeof(PACKET); i++)
	{
		printf("<%02X>\t", test.inStream[0].pBYTE[i]);
		printf("<%02X>\t", test.inStream[1].pBYTE[i]);
		printf("<%02X>\t", test.inStream[2].pBYTE[i]);
		printf("<%02X>\n", test.inStream[3].pBYTE[i]);
	}
	
	printf("<%s>\n", sprintPACKET_BYTE(&test.inStream[0]));
	printf("<%s>\n", sprintPACKET_BYTE(&test.inStream[1]));
	printf("<%s>\n", sprintPACKET_BYTE(&test.inStream[2]));
	printf("<%s>\n", sprintPACKET_BYTE(&test.inStream[3]));
}