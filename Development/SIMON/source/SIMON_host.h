#ifndef	SIMON_HOST_H
#define SIMON_HOST_H

#include <stdint.h>

#if		defined	S32_64
	#define N 16
	#define M 4
	#define T 32
#elif	defined S48_72
	#define N 24
	#define M 3
	#define T 36
#elif	defined S48_96
	#define N 24
	#define M 4
	#define T 36
#elif	defined S64_96
	#define N 32
	#define M 3
	#define T 42
#elif	defined S64_128
	#define N 32
	#define M 4
	#define T 44
#elif	defined S96_96
	#define N 48
	#define M 2
	#define T 52
#elif	defined S96_144
	#define N 48
	#define M 3
	#define T 54
#elif	defined S128_128
	#define N 64
	#define M 2
	#define T 68
#elif	defined S128_192
	#define N 64
	#define M 3
	#define T 69
#elif	defined S128_256
	#define N 64
	#define M 4
	#define T 72
#else
	#error INVALID MODE
#endif

#define	C			(1<<N)-4

typedef uint32_t	uint24_t;
typedef uint64_t	uint48_t;
#define TYPE_(x)	uint ## x ## _t
#define TYPE(x)		TYPE_(x)
#define UINT(x, n)	typedef struct n	{	TYPE_(x) v : x;	}	n;
UINT(N, word);

typedef word 		block[2];
typedef word 		key[M];
typedef word		keys[T];

#define	PRINTHEX(x)	printf("%0*X", N/4, x	)
#define NEWLINE()	printf("\n\r"			)
#define TAB()		printf("\t"				)

TYPE(N)	ROTL		(word x,	uint8_t n	);
TYPE(N)	ROTR		(word x,	uint8_t n	);

TYPE(N)	F			(word x					);
void	ROUND		(block *b,	word k		);
void	KEXP		(keys *ks,	key *k		);
void	ENCRYPT		(block p,	block c,	key k		);

#endif