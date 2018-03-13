#ifndef	SIMON_FILE_H
#define SIMON_FILE_H

#include "SIMON_definitions.h"

#include <stdlib.h>

void	readFILE(DATA *d);

char*	sprintBYTES_CHR(DATA *d);
char*	sprintBYTES_HEX(DATA *d);

char*	sprintWORDS_HEX(DATA *d);

/*
void	writeBYTES_CHR(DATA *d, TYPE(8) *ext);
void	writeBYTES_HEX(DATA *d, TYPE(8) *ext);
void	writeBYTES_DEC(DATA *d, TYPE(8) *ext);
//*/

#endif