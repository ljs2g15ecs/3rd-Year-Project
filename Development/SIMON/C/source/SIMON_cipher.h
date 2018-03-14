#ifndef	SIMON_CIPHER_H
#define SIMON_CIPHER_H

#include "SIMON_definitions.h"

TYPE(N)	ROTL		(WORD x,	TYPE(8) n	);
TYPE(N)	ROTR		(WORD x,	TYPE(8) n	);

TYPE(N)	F			(WORD x					);
void	ROUND		(BLOCK b,	WORD k		);

void	CIPHER(PACKET *inData, PACKET *outDATA);
void	loadKEY(WORD in[4]);
void	encryptDATA(WORD in[4], TYPE(8) i);
void	decryptDATA(WORD in[4], TYPE(8) i);

#endif