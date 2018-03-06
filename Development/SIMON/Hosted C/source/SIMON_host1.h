#include "SIMON_host.h"

typedef struct	IN_OUT
{
	//	CONTROL I/O
	TYPE(8)	newData		:	1;	//	INPUT	-	NEW DATA AVAILABLE
	TYPE(8)	loadData	:	1;	//	OUTPUT	-	NEW DATA LOADED
	TYPE(8)	doneData	:	1;	//	OUTPUT	-	DATA COMPUTED
	TYPE(8)	readData	:	1;	//	INPUT	-	COMPUTED DATA READ
	TYPE(8)	newKey		:	1;	//	INPUT	-	NEW KEY AVAILABLE
	TYPE(8)	loadKey		:	1;	//	OUTPUT	-	NEW KEY LOADED
	TYPE(8)	doneKey		:	1;	//	OUTPUT	-	KEY COMPUTED
	TYPE(8)	enc_dec		:	1;	// 	INPUT	-	ENCRYPT/DECRYPT
	//TYPE(8)	FILLER0		:	8;	//	EXTRA BYTE (NOT NEEDED)
}				IN_OUT;

typedef struct	INTERNAL
{
	//	DATA I/O
	block	p;					//	PLAINTEXT INPUT TO ROUND FUNCTION
	block	c;					//	CIPHERTEXT OUTPUT OF ROUND FUNCTION
	//key		k;					//	KEY INPUT
	keys	ks;					//	COMPUTED KEY SCHEDULE
}				INTERNAL;

typedef struct	PACKET
{
	//	PACKET INFO
	TYPE(8)	mode		:	4;	//	CIPHER MODE
	TYPE(8)	enc_dec		:	1;	//	ENCRYPT/DECRYPT
	TYPE(8)	data_key	:	1;	//	DATA/KEY
	TYPE(8)	nWords		:	2;	//	NUMBER OF WORDS IN PACKET (1-4)
	TYPE(8)	FILLER0		:	8;	//	EXTRA BYTE (NOT NEEDED)
	//	PACKET DATA
	word	data[4];			//	PACKET DATA
}				PACKET;