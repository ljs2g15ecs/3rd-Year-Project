#include "SIMON_definitions.h"
#include "SIMON_test.h"

#include <iostream>
#include <iomanip>
using namespace std;

#if	defined S3264	
	KEY 	K	=	{	0x1918, 0x1110,
						0x0908, 0x0100							};
	BLOCK 	P	=	{	0x6565, 0x6877							};
	BLOCK 	C	=	{	0xC69B, 0xE9BB							};
#elif	defined S4872	
	KEY 	K	=	{	0x121110, 0x0A0908,
						0x020100								};
	BLOCK 	P 	=	{	0x612067, 0x6E696C						};
	BLOCK 	C	=	{	0xDAE5AC, 0x292CAC						};
#elif	defined	S4896
	KEY 	K	=	{	0x1A1918, 0x121110,
						0x0A0908, 0x020100						};
	BLOCK	P	=	{	0x726963, 0x20646E						};
	BLOCK	C	=	{	0x6E06A5, 0xACF156						};
#elif	defined S6496
	KEY 	K	=	{	0x13121110, 0x0B0A0908,
						0x03020100								};
	BLOCK	P	=	{	0x6F722067, 0x6E696C63					};
	BLOCK	C	=	{	0x5CA2E27F, 0x111A8FC8					};
#elif	defined S64128
	KEY 	K	=	{	0x1B1A1918, 0x13121110,
						0x0B0A0908, 0x03020100					};
	BLOCK	P	=	{	0x656B696C, 0x20646E75					};
	BLOCK	C	=	{	0x44C8FC20, 0xB9DFA07A					};
#elif	defined S9696
	KEY 	K	=	{	0x0D0C0B0A0908, 0x050403020100			};
	BLOCK	P	=	{	0x2072616C6C69, 0x702065687420			};
	BLOCK	C	=	{	0x602807A462b4, 0x69063D8FF082			};
#elif	defined S96144
	KEY 	K	=	{	0x151413121110, 0x0D0C0B0A0908,
						0x050403020100							};
	BLOCK	P	=	{	0x746168742074, 0x73756420666f			};
	BLOCK	C	=	{	0xECAD1C6C451E, 0x3f59C5DB1AE9			};
#elif	defined S128128
	KEY 	K	=	{	0x0F0E0D0C0B0A0908, 0x0706050403020100	};
	BLOCK	P	=	{	0x6373656420737265, 0x6C6C657661727420	};
	BLOCK	C	=	{	0x49681B1E1E54FE3F, 0x65AA832AF84E0BBC	};
#elif	defined S128192
	KEY 	K	=	{	0x1716151413121110, 0x0F0E0D0C0B0A0908,
						0x0706050403020100						};
	BLOCK	P	=	{	0x206572656874206E, 0x6568772065626972	};
	BLOCK	C	=	{	0xC4AC61EFFCDC0D4F, 0x6C9C8D6E2597b85B	};
#elif	defined S128256
	KEY 	K	=	{	0x1F1E1D1C1B1A1918, 0x1716151413121110,
						0x0F0E0D0C0B0A0908, 0x0706050403020100	};
	BLOCK	P	=	{	0x74206E69206D6F6F, 0x6D69732061207369	};
	BLOCK	C	=	{	0x8D2B5579AFC8A3A0, 0x3BF72A87EfE7B868	};
#endif

void		testCLASSES		(						)
{
	cout << "|\tMODE\t|\t" << MODE << "\t|" << endl;
	cout << "|\tN\t|\t" << N << "\t|" << endl;
	cout << "|\tM\t|\t" << M << "\t|" << endl;
	cout << "|\tT\t|\t" << T << "\t|" << endl;
	cout << "|\tJ\t|\t" << J << "\t|" << endl;
	
	
	cout << "|\tTYPE(N)\t|\t" << sizeof(TYPE(N)) << "\t|" << endl;
	cout << "|\tWORD\t|\t" << sizeof(WORD) << "\t|" << endl;
	
	WORD a = 0xB, b = 0x4;			a.test();
	WORD c = a ^ b;	c.test();
	c = a << 4;		c.test();
	c = a >> 4;		c.test();
	c = ~a;			c.test();
	
	BLOCK d = P;	d.test();
	
	KEY e = K;		e.test();
	
	//KEY_S f;		f.test();
	
	_INFO_ input;\
	input.mode = MODE;\
	input.in_out = 0;\
	input.data_key = 0;\
	input.enc_dec = 0;\
	input.nBlocks = 1;\
	PACKET g(input);	g.addWORD(a);	g.addWORD(b);	g.test();
	
	DATA h("test");		h.assign(K);	h.test();
	
	resetCounts();
}

void		printPACKETS	(	PACKET	p,	PACKET	c	)
{
	cout << "|\t" << p.HEX_WORD() << "\t|";
	cout << ">>";
	cout << "|\t" << c.HEX_WORD() << "\t|" << endl; 
}

//	SETUP INPUT USING TEST VECTORS (TV)
PACKET		expandTV_PKT	(						)
{
	PACKET t;
	
	_INFO_ in;
	in.mode = MODE;\
	in.in_out = 0;\
	in.data_key = 0;\
	in.enc_dec = 1;\
	in.nBlocks = 1;\
		
	t.input();
	t.assign(in);
	t.addKEY(K);
	
	return t;
}

PACKET		encryptTV_PKT	(						)
{
	PACKET t;
	
	_INFO_ in;
	in.mode = MODE;\
	in.in_out = 0;\
	in.data_key = 0;\
	in.enc_dec = 0;\
	in.nBlocks = 1;\
	
	t.input();
	t.assign(in);
	t.addBLOCK(P);	t.addBLOCK(P);
	
	return t;
}

//	TEST OPERATION
TYPE(8)		tCIPHER_TV_PKT	(							)
{
	cout << endl << "|\tTESTING PACKET HANDLING WITH TEST VECTORS\t|" << endl;
	
	PACKET p, c;
	CIPHER	SIMON;
	
	resetCounts();
	
	p = expandTV_PKT();
	c = SIMON.compute(p);
	printPACKETS(p, c);
	
	
	p = encryptTV_PKT();
	c = SIMON.compute(p);
	printPACKETS(p, c);
	
	if( (c.get_BLK(0) == C) && (c.get_BLK(1) == C) )
	{
		cout << "|\tENCRYPTING WORKING!\t|" << endl;
		return 1;
	}
	else
	{
		cout << "|\tENCRYPTING NOT WORKING!\t|" << endl;
		return 0;
	}
}

TYPE(8)		tCIPHER_TV_BLK	(							)
{
	cout << endl << "|\tTESTING CIPHER WITH TEST VECTORS\t|" << endl;
	
	CIPHER SIMON;
	
	cout << "|\tKEY\t|\t" << K.HEX_WORD() << "\t|" << endl;
	SIMON.expandKEY( K );
	
	cout << "|\tDATA\t|\t" << P.HEX_WORD() << "\t|>>";
	BLOCK c = SIMON.compute(P, 1);
	cout << "|\t" << c.HEX_WORD() << "\t|" << endl;
	
	if(c == C)
	{
		cout << "|\tENCRYPTING WORKING!\t|" << endl;
		return 1;
	}
	else
	{
		cout << "|\tENCRYPTING NOT WORKING!\t|" << endl;
		return 0;
	}
}

TYPE(64)	tTHROUGH_TV_PKT	(							)
{
	clock_t start, end;

	start = clock();

	//perform calculations for which performance needs to be checked
	CIPHER SIMON;
	resetCounts();
	
	SIMON.compute(expandTV_PKT());
	TYPE(16) i;
	for(i=0; i<(1<<16)-1; i++)
	{
		SIMON.compute(encryptTV_PKT());
	}
	

	end = clock();

	cout	<< "Time required for " << i << " executions: "\
			<< (double)(end-start)/CLOCKS_PER_SEC\
			<< " seconds." << endl;
	return 0;
}

TYPE(64)	tTHROUGH_TV_BLK	(							)
{
	clock_t start, end;

	start = clock();

	//perform calculations for which performance needs to be checked
	CIPHER SIMON;
	
	SIMON.expandKEY(K);
	TYPE(16) i;
	for(i=0; i<(1<<16)-1; i++)
	{
		SIMON.compute(P, 1);
	}
	

	end = clock();

	cout	<< "Time required for " << i << " executions: "\
			<< (double)(end-start)/CLOCKS_PER_SEC\
			<< " seconds." << endl;
	return 0;
}

//	SETUP INPUT DATA USING DATA FILE (DF)

DATA		testFILE;
void		encryptFILE_PKT	(							)
{
	testFILE.flush();
	resetCounts();
	
	testFILE.assign("test");
	testFILE.addFILE_PKT(K);
	//testFILE.addFILE_PKT(P, P);
	
	testFILE.readFILE_PKT();
}

void		encryptFILE_BLK	(							)
{
	testFILE.flush();
	
	testFILE.assign("test");
	testFILE.assign(K);
	
	testFILE.addFILE_BLK(P);
	
	testFILE.readFILE_BLK();
}

void		decryptFILE_PKT	(							)
{
	
}

void		decryptFILE_BLK	(							)
{
	
}

//	TEST OPERATION USING DATA FILE(DF)
TYPE(8)		tCIPHER_DF_PKT	(							)
{
	encryptFILE_PKT();
	testFILE.computePKTs(101);
}
TYPE(8)		tCIPHER_DF_BLK	(							)
{
	encryptFILE_BLK();
	testFILE.encryptBLKs(200);
}
TYPE(64)	tTHROUGH_DF_PKT	(							)
{
	clock_t start, end;
	
	encryptFILE_PKT();
	start = clock();

	//perform calculations for which performance needs to be checked
	TYPE(64) i = testFILE.computePKTs((1<<16)-1);
	
	end = clock();

	cout	<< "Time required for " << i << " executions: "\
			<< (double)(end-start)/CLOCKS_PER_SEC\
			<< " seconds." << endl;
	return 0;
}
TYPE(64)	tTHROUGH_DF_BLK	(							)
{
	clock_t start, end;

	encryptFILE_BLK();
	start = clock();

	//perform calculations for which performance needs to be checked
	TYPE(64) i = testFILE.encryptBLKs((1<<16)-1);
	
	end = clock();

	cout	<< "Time required for " << i << " executions: "\
			<< (double)(end-start)/CLOCKS_PER_SEC\
			<< " seconds." << endl;
	return 0;
}

//	SETUP DATA FOR MODELSIM SIMULATION
void		printFILE_PKT_SV(							)
{
	encryptFILE_PKT();
	cout << testFILE.HEX_PKT_SV();
}

void		printFILE_BLK_SV(							)
{
	
}

