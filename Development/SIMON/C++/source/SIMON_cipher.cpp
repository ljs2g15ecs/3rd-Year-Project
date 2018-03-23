#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

//	CONSTRUCTORS
CIPHER::CIPHER()
{
	flush();
}

//	MUTATORS
void		CIPHER::compute		(	PACKET	p					)
{
	
}

void		CIPHER::expandKEY	(	KEY		x					)
{
	
}

void		CIPHER::encryptDATA	(	WORD	x0,	WORD	x1		)
{
	
}

void		CIPHER::decryptDATA	(	WORD	x0,	WORD	x1		)
{
	
}

BLOCK		CIPHER::round		(	WORD	x					)
{
	/*
	word tmp = b[0];
	b[0].v = b[1].v ^ F(b[0]) ^ k.v;
	b[1] = tmp;
	//*/
	
	WORD tmp = stateCIPHER.get_w(0);
	//stateCIPHER.assign(stateCIPHER.get_w(1) ^ F(stateCIPHER.get_w(0)) ^ x, 0);
	stateCIPHER.assign(tmp, 0);
}

WORD		CIPHER::expand		(								)
{
	
}

void		CIPHER::flush		(								)
{
	stateCIPHER.flush();
	scheduleKEY.flush();
	pktCOUNT = 0;
	doneKEY = 0;
}

