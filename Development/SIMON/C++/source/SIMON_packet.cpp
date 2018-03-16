#include "SIMON_definitions.h"

#include <iostream>
#include <iomanip>
using namespace std;

//	CONSTUCTORS
PACKET::PACKET()
{
	flush();
}

PACKET::PACKET(	_PACKET_	x	)
{
	flush();
	assign(x);
}

//	MUTATORS
void		PACKET::input		(								)
{
	pDATA.iDATA.mode = MODE;
	pDATA.iDATA.in_out = 0;
	pDATA.iDATA.data_key = 0;	//	DEFAULT
	pDATA.iDATA.enc_dec = 0;	//	DEFAULT
	pDATA.iDATA.nBlocks = 0;	//	DEFAULT
	//pDATA.count = inputCount;
}

void		PACKET::output		(	_INFO_	x					)
{
	pDATA.iDATA = x;
	pDATA.iDATA.in_out = 1;		//	CHANGE TO OUPUT
	//outputCount++;
}

void		PACKET::assign		(	_PACKET_	x				)
{
	pDATA = x;
	return;
}

void		PACKET::assign		(	_INFO_	x					)
{
	pDATA.iDATA = x;
	return;
}

void		PACKET::assign		(	WORD	x,	TYPE(8)	i		)
{
	pDATA.wDATA[i] = x;
	return;
}

void		PACKET::assign		(	TYPE(N)	x,	TYPE(8)	i		)
{
	pDATA.wDATA[i] = x;
	return;
}

void		PACKET::addWORD		(	WORD	x					)
{
	pDATA.wDATA[nxtWORD++] = x;
	return;
}

void		PACKET::addWORD		(	TYPE(N)	x					)
{
	pDATA.wDATA[nxtWORD++] = x;
	return;
}

void		PACKET::flush		(								)
{
	nxtWORD = 0;
	pDATA.iBYTE = 0;
	pDATA.count = 0;
	pDATA.wDATA[0].flush();
	pDATA.wDATA[1].flush();
	pDATA.wDATA[2].flush();
	pDATA.wDATA[3].flush();
}

void		PACKET::setCounts	(	U_64	x					)
{
	//inputCount = x;
	//outputCount = x;
}

void		PACKET::setICount	(	U_64	x					)
{
	//inputCount = x;
}

void		PACKET::setOCount	(	U_64	x					)
{
	//outputCount = x;
}

void		PACKET::resetCounts	(								)
{
	//inputCount = 0;
	//outputCount = 0;
}

void		PACKET::resetICount	(								)
{
	//inputCount = 0;
}

void		PACKET::resetOCount	(								)
{
	//outputCount = 0;
}

//	ACCESSORS
void		PACKET::test		(								)
{
	
}


