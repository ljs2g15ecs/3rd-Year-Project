#ifndef SIMON_TEST_H
#define SIMON_TEST_H

#include "SIMON_host.h"
#include "SIMON_host1.h"

#if	(N<=32)
#define	PRINTHEX(x)	printf("%0*X", N/4, x	)
#else
#define	PRINTHEX(x)	printf("%0*llX", N/4, x	)
#endif

#define NEWLINE()	printf("\n\r"			)
#define TAB()		printf("\t"				)

void	test();
void	test1();
void	test2();

void	printPACKETDATA(PACKET p);
void	printSTREAM(PACKET in, PACKET out);

#endif