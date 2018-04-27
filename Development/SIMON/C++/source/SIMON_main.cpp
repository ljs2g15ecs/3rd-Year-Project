#include "SIMON_definitions.h"
#include "SIMON_test.h"

#include <iostream>
using namespace std;

int		main()
{
	//testCLASSES();
	
	//tCIPHER_TV_PKT();\
	tCIPHER_TV_BLK();
	//tTHROUGH_TV_PKT();\
	tTHROUGH_TV_BLK();
	
	tCIPHER_DF_PKT();
}