#ifndef	SIMON_HOST_H
#define SIMON_HOST_H

#include <stdio.h>
#include <stdint.h>

#if		defined	S32_64
	#define N 16
	#define M 4
	#define R 32
#elif	defined S48_72
	#define N 24
	#define M 3
	#define R 36
#elif	defined S48_96
	#define N 24
	#define M 4
	#define R 36
#elif	defined S64_96
	#define N 32
	#define M 3
	#define R 42
#elif	defined S64_128
	#define N 32
	#define M 4
	#define R 44
#elif	defined S96_96
	#define N 48
	#define M 2
	#define R 52
#elif	defined S96_144
	#define N 48
	#define M 3
	#define R 54
#elif	defined S128_128
	#define N 64
	#define M 2
	#define R 68
#elif	defined S128_192
	#define N 64
	#define M 3
	#define R 69
#elif	defined S128_256
	#define N 64
	#define M 4
	#define R 72
#else
	#define N 8
	#define M 1
	#define R 0
	#error "INVALID MODE"
#endif

typedef uint32_t	uint24_t;
typedef uint64_t	uint48_t;
#define TYPE(x)		uint ## x ## _t
#define UINT(x, n)	typedef TYPE(x) n 
UINT(N, word);

typedef word 		block[2];
typedef word 		key[M];

#define	PRINTHEX(x)	printf("%0*x\t", N/4, a)

void	ROTL(word *x, uint8_t n);
void	ROTR(word *x, uint8_t n);

#endif