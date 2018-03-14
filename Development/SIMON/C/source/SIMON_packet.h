#ifndef	SIMON_PACKET_H
#define SIMON_PACKET_H

#include "SIMON_definitions.h"

#include <stdlib.h>

void	buildINPUT(PACKET *p);
void	buildOUTPUT(PACKET *p, PACKET in);
void	addWORD(PACKET *p, TYPE(N) w, TYPE(8) i);
void	addKEY(PACKET *p, KEY k);
void	addBLOCK(PACKET *p, BLOCK b);
void	addBLOCKS(PACKET *p, BLOCK b0, BLOCK b1);

void	buildSTREAM(DATA *d);

char*	sprintPACKETDATA(PACKET *p);
char*	sprintPACKET(PACKET *p);

char*	sprintSTREAM(DATA *d);

#endif