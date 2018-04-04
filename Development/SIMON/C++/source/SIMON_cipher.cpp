#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

#define		F(x)	((x << 1) & (x << 8)) ^ (x << 2)

//	OTHER
/*
WORD		F					(	WORD	x					)
{
	WORD w = ((x << 1) & (x << 8)) ^ (x << 2);
	return w;
}
//*/

//	CONSTRUCTORS
CIPHER::CIPHER()
{
	flush();
}

//	MUTATORS
PACKET		CIPHER::compute		(	PACKET	x					)
{
	PACKET out;
	out.output(x.get_i());
	
	switch(x.checkIN(pktCOUNT))
	{
		case	0:	// ERROR
			cout << "ERR1";
			break;
		case	1:	// DATA
			if(doneKEY)
			{
				cout << "DATA";
				if(x.get_i().enc_dec)	decryptDATA(x.get_w(0), x.get_w(1));
				else					encryptDATA(x.get_w(0), x.get_w(1));
				out.assign(stateCIPHER.get_w(0), 0);
				out.assign(stateCIPHER.get_w(1), 1);
				pktCOUNT++;
				if(!x.get_i().nBlocks) break;
				
				if(x.get_i().enc_dec)	decryptDATA(x.get_w(2), x.get_w(3));
				else					encryptDATA(x.get_w(2), x.get_w(3));
				out.assign(stateCIPHER.get_w(0), 2);
				out.assign(stateCIPHER.get_w(1), 3);
			}
			break;
		case	2:	// KEY
			cout << "KEY!";
			expandKEY( KEY(x.get_w(3), x.get_w(2), x.get_w(1), x.get_w(0)) );
			pktCOUNT++;
			break;
		default	 :	//	ERROR
			cout << "ERR2";
			break;
	}
	
	out.pack();
	
	return out;
}

void		CIPHER::expandKEY	(	KEY		x					)
{
	for(roundCOUNT=0; roundCOUNT<T; roundCOUNT++)
	{
		scheduleKEY.assign(expand(x,roundCOUNT), roundCOUNT);
	}
	doneKEY = 1;
}

void		CIPHER::encryptDATA	(	WORD	x0,	WORD	x1		)
{
	stateCIPHER.assign(x0, 0);
	stateCIPHER.assign(x1, 1);
	
	for(roundCOUNT=0; roundCOUNT<T; roundCOUNT++)
	{
		stateCIPHER = round(scheduleKEY.get_w(roundCOUNT));
	}
}

void		CIPHER::decryptDATA	(	WORD	x0,	WORD	x1		)
{
	stateCIPHER.assign(x1, 0);
	stateCIPHER.assign(x0, 1);
	
	for(roundCOUNT=T; roundCOUNT>0; roundCOUNT--)
	{
		stateCIPHER = round(scheduleKEY.get_w(roundCOUNT));
	}
	
	stateCIPHER.swap();
}

BLOCK		CIPHER::round		(	WORD	x					)
{
	BLOCK b;
	b.assign(stateCIPHER.get_w(1) ^ F(stateCIPHER.get_w(0)) ^ x, 0);
	b.assign(stateCIPHER.get_w(0), 1);
	return b;
}

const TYPE(8) Z[5][62] =
{
	{1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0},
	{1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0},
	{1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,0,1,1},
	{1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,1,1,1},
	{1,1,0,1,0,0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,1,1,1,0,1,1,1,1}
};

WORD		CIPHER::expand		(	KEY		x,	TYPE(8)	i		)
{
	WORD w, tmp;
	
	if(i<M)	w = x.get_w(i);
	else
	{
		tmp = scheduleKEY.get_w(i-1) >> 3;
#if (M == 4)
		tmp = tmp ^ scheduleKEY.get_w(i-3);
#endif
		tmp = tmp ^ (tmp >> 1);
		w = tmp ^ ~scheduleKEY.get_w(i-M) ^ (Z[J][(i-M)%62]) ^ 3;
	}
	
	return w;
}

void		CIPHER::flush		(								)
{
	stateCIPHER.flush();
	scheduleKEY.flush();
	roundCOUNT = 0;
	pktCOUNT = 0;
	doneKEY = 0;
}





