#ifndef SIMON_TEST_H
#define SIMON_TEST_H

#include "SIMON_host.h"

#if	(N<=32)
#define	PRINTHEX(x)	printf("%0*X", N/4, x	)
#else
#define	PRINTHEX(x)	printf("%0*llX", N/4, x	)
#endif

#define NEWLINE()	printf("\n\r"			)
#define TAB()		printf("\t"				)

void	test();

#endif