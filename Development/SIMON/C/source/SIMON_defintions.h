#ifndef	SIMON_DEF_H
#define SIMON_DEF_H

#include <stdint.h>

#if	(N<=32)
#define	PRINTHEX(x)	printf("%0*X", N/4, x	)
#else
#define	PRINTHEX(x)	printf("%0*llX", N/4, x	)
#endif

#define NEWLINE()	printf("\n\r"			)
#define TAB()		printf("\t"				)

#if		defined	S32_64
	#define MODE	0
	#define N 		16
	#define M 		4
	#define T 		32
	#define	j 		0
#elif	defined S48_72
	#define MODE	1
	#define N 		24
	#define M 		3
	#define T 		36
	#define	j 		0
#elif	defined S48_96
	#define MODE	2
	#define N 		24
	#define M 		4
	#define T 		36
	#define	j 		1
#elif	defined S64_96
	#define MODE	3
	#define N 		32
	#define M 		3
	#define T 		42
	#define	j 		2
#elif	defined S64_128
	#define MODE	4
	#define N 		32
	#define M 		4
	#define T 		44
	#define	j 		3
#elif	defined S96_96
	#define MODE	5
	#define N 		48
	#define M 		2
	#define T 		52
	#define	j 		2
#elif	defined S96_144
	#define MODE	6
	#define N 		48
	#define M 		3
	#define T 		54
	#define	j 		3
#elif	defined S128_128
	#define MODE	7
	#define N 		64
	#define M 		2
	#define T 		68
	#define	j 		2
#elif	defined S128_192
	#define MODE	8
	#define N 		64
	#define M 		3
	#define T 		69
	#define	j 		3
#elif	defined S128_256
	#define MODE	9
	#define N 		64
	#define M 		4
	#define T 		72
	#define	j 		4
#else
	#error INVALID MODE
#endif

typedef uint32_t	uint24_t;
typedef uint64_t	uint48_t;
#define TYPE_(x)	uint ## x ## _t
#define TYPE(x)		TYPE_(x)
#define UINT(x, n)	typedef struct n	{	TYPE(x) v : x;	}	n;
UINT(N, WORD);

typedef WORD 		BLOCK[2];
typedef WORD 		KEY[M];
typedef WORD		KEY_S[T];

typedef struct	INTERNAL
{
	//	DATA
	BLOCK	o;					//	CIPHERTEXT OUTPUT OF ROUND FUNCTION
	KEY_S	ks;					//	COMPUTED KEY SCHEDULE
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
	WORD	data[4];			//	PACKET DATA
}				PACKET;

#endif