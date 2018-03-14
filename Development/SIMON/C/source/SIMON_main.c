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
}