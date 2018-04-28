#ifndef	SIMON_TEST_H
#define SIMON_TEST_H

#include "SIMON_definitions.h"

void		testCLASSES		(							);
void		printPACKETS	(	PACKET	p,	PACKET	c	);

//	SETUP INPUT USING TEST VECTORS (TV)
PACKET		expandTV_PKT	(							);
PACKET		encryptTV_PKT	(							);
PACKET		decryptTV_PKT	(	PACKET	x				);

//	TEST OPERATION USING TEST VECTORS (TV)
TYPE(8)		tCIPHER_TV_PKT	(							);
TYPE(8)		tCIPHER_TV_BLK	(							);
TYPE(64)	tTHROUGH_TV_PKT	(							);
TYPE(64)	tTHROUGH_TV_BLK	(							);

//	SETUP INPUT DATA USING DATA FILE (DF)
void		encryptFILE_PKT	(							);
void		encryptFILE_BLK	(							);
void		decryptFILE_PKT	(							);
void		decryptFILE_BLK	(							);

//	TEST OPERATION USING DATA FILE(DF)
TYPE(8)		tCIPHER_DF_PKT	(							);
TYPE(8)		tCIPHER_DF_BLK	(							);
TYPE(64)	tTHROUGH_DF_PKT	(							);
TYPE(64)	tTHROUGH_DF_BLK	(							);

//	SETUP DATA FOR MODELSIM SIMULATION
void		printFILE_PKT_SV(							);
void		printFILE_BLK_SV(							);

#endif

