#ifndef SIMON_HOST1_H
#define SIMON_HOST1_H

#include "SIMON_host.h"

/*
typedef struct	IO
{
	//	CONTROL IO
	TYPE(8)	newData		:	1;	//	INPUT	-	NEW DATA AVAILABLE
	TYPE(8)	loadData	:	1;	//	OUTPUT	-	NEW DATA LOADED
	TYPE(8)	doneData	:	1;	//	OUTPUT	-	DATA COMPUTED
	TYPE(8)	readData	:	1;	//	INPUT	-	COMPUTED DATA READ
	TYPE(8)	newKey		:	1;	//	INPUT	-	NEW KEY AVAILABLE
	TYPE(8)	loadKey		:	1;	//	OUTPUT	-	NEW KEY LOADED
	TYPE(8)	doneKey		:	1;	//	OUTPUT	-	KEY COMPUTED
	TYPE(8)	enc_dec		:	1;	// 	INPUT	-	ENCRYPT/DECRYPT
	//TYPE(8)	FILLER0		:	8;	//	EXTRA BYTE (NOT NEEDED)
}				IO;
//*/

typedef struct	INTERNAL
{
	//	DATA
	block	o;					//	CIPHERTEXT OUTPUT OF ROUND FUNCTION
	keys	ks;					//	COMPUTED KEY SCHEDULE
	//	CONTROL
	TYPE(8)	count		:	8;	//	DATA COUNT
	TYPE(8)	doneKey		:	1;	//	OUTPUT	-	KEY COMPUTED
	TYPE(8)	doneData	:	1;	//	OUTPUT	-	DATA COMPUTED
	TYPE(8)	ENC_DEC		:	1;	// 	INPUT	-	ENCRYPT/DECRYPT
	TYPE(8)	nBlocks		:	1;	//	INPUT	-	NUMBER OF BLOCKS (1/2)
	TYPE(8)	FILLER0		:	4;	//	FILLER
}				INTERNAL;

typedef struct	PACKET
{
	//	PACKET INFO
	TYPE(8)	in_out		:	1;	//	INPUT/OUTPUT
	TYPE(8)	mode		:	4;	//	CIPHER MODE
	TYPE(8)	data_key	:	1;	//	DATA/KEY
	TYPE(8)	enc_dec		:	1;	//	ENCRYPT/DECRYPT
	TYPE(8)	nBlocks		:	1;	//	NUMBER OF BLOCKS (1/2)
	TYPE(8)	count		:	8;	//	DATA COUNT
	//	PACKET DATA
	word	data[4];			//	PACKET DATA
}				PACKET;

void	buildInputPACKET(PACKET *p);
void	buildOutputPACKET(PACKET *p, PACKET in);
void	addWord(PACKET *p, TYPE(N) w, TYPE(8) i);
void	addBlock(PACKET *p, block b);
void	addBlocks(PACKET *p, block b0, block b1);
void	addKey(PACKET *p, key k);
PACKET	CIPHER(PACKET inData);
void	loadKey(word in[4]);
void	encryptData(word in[4], TYPE(8) i);
void	decryptData(word in[4], TYPE(8) i);

#endif