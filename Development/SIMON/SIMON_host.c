#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE	32
#define KEY_WORDS	4

typedef	uint8_t	BYTE;	//	1 BYTE	|	8 bits

typedef BYTE	WORD[BLOCK_SIZE/(2*8)];
typedef WORD	BLOCK[2];
typedef	WORD	KEY[KEY_WORDS];

void	printBYTE(void *ptr, BYTE size);
void	resetBYTE(void *ptr, BYTE size);
//void	roundF(BLOCK *plain, BLOCK *cipher, KEY *key);

int		main()
{
	printf("Hello There!!!\n\r");
	
	printf("%d\n\r", sizeof(BYTE)*8);
	printf("%d\n\r", sizeof(WORD)*8);
	printf("%d\n\r", sizeof(BLOCK)*8);
	printf("%d\n\r", sizeof(KEY)*8);
	
	BYTE a = 0xA3;
	
	uint64_t b = 0x0100000F0A3;
	WORD	*c = (WORD*) malloc(sizeof(WORD));	resetBYTE(c, sizeof(*c));
	KEY		*d = (KEY*) malloc(sizeof(KEY));	resetBYTE(d, sizeof(*d));
	
	printf("%d\n\r", sizeof(a)*8);
	printf("%d\n\r", sizeof(b)*8);
	printf("%d\n\r", sizeof(*c)*8);
	
	printBYTE(c, sizeof(*c));
	printBYTE(d, sizeof(*d));
	
	memcpy(c, &b, sizeof(b));
	memcpy(d, &b, sizeof(b));
	
	printf("\n\r");
	
	printBYTE(c, sizeof(*c));
	printBYTE(d, sizeof(*d));
	
	return 0;
}

void	printBYTE(void *ptr, BYTE size)
{
	int i;
	for(i=size-1; i>=0; i--)
	{
		printf("%02X", *((BYTE*)ptr+i));
	}
	printf("\t");
}

void	resetBYTE(void *ptr, BYTE size)
{
	int i;
	for(i=size-1; i>=0; i--)
	{
		*((BYTE*)ptr+i) = 0;;
	}
}

/*void	roundF(BLOCK *plain, BLOCK *cipher, KEY *key)
{
	WORD *x = ((WORD*)plain+(sizeof(WORD)-1));
	WORD *y = ((WORD*)plain);
	
	printf("P:\t%u\tX:\t%hu\tY:\t%hu", *plain, *x, *y);
	
}*/