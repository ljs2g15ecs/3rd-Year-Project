#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

//	OTHER
WORD		F					(	WORD	x					)
{
	WORD w = ((x << 1) & (x << 8)) ^ (x << 2);
	return w;
}

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
	WORD tmp = stateCIPHER.get_w(0);
	stateCIPHER.assign(stateCIPHER.get_w(1) ^ F(tmp) ^ x, 0);
	stateCIPHER.assign(tmp, 1);
}

WORD		CIPHER::expand		(	WORD	x,	TYPE(8)	i		)
{
	WORD w, tmp;
	
	if(i<M)	w = x;
	else
	{
		tmp = scheduleKEY.get_w(i-1) >> 3;
#if (M == 4)
		tmp = tmp ^ scheduleKEY.get_w(i-3);
#endif
		tmp = tmp ^ (tmp >> 1);
		w = tmp ^ ~scheduleKEY.get_w(i-M) ^ 3;
	}
	
	return w;
}

void		CIPHER::flush		(								)
{
	stateCIPHER.flush();
	scheduleKEY.flush();
	pktCOUNT = 0;
	doneKEY = 0;
}





