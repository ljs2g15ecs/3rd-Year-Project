#include "SIMON_definitions.h"
#include "SIMON_test.h"

#include <iostream>
using namespace std;

int		main()
{
#ifdef	DEBUG
	//testCLASSES();
	
	//tCIPHER_TV_PKT();\
	tCIPHER_TV_BLK();
	
	//tCIPHER_DF_PKT();\
	tCIPHER_DF_BLK();
	
	printFILE_PKT_SV();
#endif

#ifndef	DEBUG
	tTHROUGH_TV_PKT();\
	tTHROUGH_TV_BLK();
	
	tTHROUGH_DF_PKT();\
	tTHROUGH_DF_BLK();
#endif
}