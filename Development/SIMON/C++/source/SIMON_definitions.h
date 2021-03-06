#ifndef	SIMON_DEF_H
#define SIMON_DEF_H

using namespace std;

#if		defined	S3264
	#define 	MODE	0
	#define 	N 		16
	#define 	M 		4
	#define 	T 		32
	#define		J 		0
#elif	defined S4872
	#define 	MODE	1
	#define 	N 		24
	#define 	M 		3
	#define 	T 		36
	#define		J 		0
#elif	defined S4896
	#define 	MODE	2
	#define 	N 		24
	#define 	M 		4
	#define 	T 		36
	#define		J 		1
#elif	defined S6496
	#define 	MODE	3
	#define 	N 		32
	#define 	M 		3
	#define 	T 		42
	#define		J 		2
#elif	defined S64128
	#define 	MODE	4
	#define 	N 		32
	#define 	M 		4
	#define 	T 		44
	#define		J 		3
#elif	defined S9696
	#define 	MODE	5
	#define 	N 		48
	#define 	M 		2
	#define 	T 		52
	#define		J 		2
#elif	defined S96144
	#define 	MODE	6
	#define 	N 		48
	#define 	M 		3
	#define 	T 		54
	#define		J 		3
#elif	defined S128128
	#define 	MODE	7
	#define 	N 		64
	#define 	M 		2
	#define 	T 		68
	#define		J 		2
#elif	defined S128192
	#define 	MODE	8
	#define 	N 		64
	#define 	M 		3
	#define 	T 		69
	#define		J 		3
#elif	defined S128256
	#define 	MODE	9
	#define 	N 		64
	#define 	M 		4
	#define 	T 		72
	#define		J 		4
#else
	#error 		INVALID MODE
#endif

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

typedef uint32_t	uint24_t;
typedef uint64_t	uint48_t;
#define TYPE_(x)	uint ## x ## _t
#define TYPE(x)		TYPE_(x)

class 			WORD
{
public:
	//	COSNTUCTORS
	WORD();
	WORD(TYPE(N) x);
	//	MUTATORS
	void		assign		(	TYPE(N)	x					);
	void		assign		(	TYPE(8)	x, TYPE(8)	i		);
	TYPE(8)		addBYTE		(	TYPE(8)	x					);
	void		flush		(								);
	
	//	ACCESSORS
	void		test		(								);
	TYPE(N)		get_v		(								);
	TYPE(8)		get_b		(								);
	TYPE(8)		get_b		(	TYPE(8)	i					);
	TYPE(16)	get_B		(	TYPE(8)	i					);
	TYPE(16)	size_v		(								);
	TYPE(16)	size_b		(								);
	string		HEX_WORD	(								);
	string		CHR_BYTES	(								);
	string		HEX_BYTES	(								);
	
	//	OPERATORS
	WORD		operator~	(								);
	WORD		operator&	(	const	WORD	x			);
	WORD		operator^	(	const	WORD	x			);
	WORD		operator^=	(	const	WORD	x			);
	WORD		operator<<	(	const	TYPE(8)	i			);
	WORD		operator>>	(	const	TYPE(8)	i			);
	
private:
	TYPE(8)		w_nxtBYTE;
	TYPE(8)		r_nxtBYTE;
	union
	{
		TYPE(N)	val	:	N;
		TYPE(8)	bytes[N/8];
	};
};

class 			BLOCK
{
public:
	//	COSNTUCTORS
	BLOCK();
	BLOCK(TYPE(N) x0, TYPE(N) x1);
	BLOCK(WORD x0, WORD x1);
	//	MUTATORS
	void		assign		(	TYPE(N)	x0,	TYPE(N)	x1		);
	void		assign		(	WORD	x0, WORD	x1		);
	void		assign		(	TYPE(N)	x,	TYPE(8)	i		);
	void		assign		(	WORD	x,	TYPE(8)	i		);
	void		addWORD		(	WORD	x					);
	void		swap		(								);
	void		flush		(								);
	
	//	ACCESSORS
	void		test		(								);
	WORD		get_w		(	TYPE(8)	i					);
	WORD*		ref_w		(	TYPE(8)	i					);
	TYPE(N)		get_W		(	TYPE(8)	i					);
	TYPE(8)		get_Wb		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	get_WB		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	size		(								);
	string		HEX_WORD	(								);
	string		CHR_BYTES	(								);
	string		HEX_BYTES	(								);
	string		CHR			(								);
	string		HEX_SV		(	TYPE(64)	i				);
	
	//	OPERATORS
	TYPE(8)		operator==	(	BLOCK x						);
	
private:
	TYPE(8)		nxtWORD	:	1;
	WORD		B[2];
};

class 			KEY
{
public:
	//	COSNTUCTORS
	KEY();
	//KEY(WORD x[M]);
	//KEY(TYPE(N) x[M]);
	KEY						(	WORD	x0,	WORD	x1		);
	KEY						(	TYPE(N)	x0,	TYPE(N)	x1		);
	KEY						(	WORD	x0,	WORD	x1,
								WORD	x2					);
	KEY						(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2					);
	KEY						(	WORD	x0,	WORD	x1,
								WORD	x2, WORD	x3		);
	KEY						(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2, TYPE(N)	x3		);
	//	MUTATORS
	void		assign		(	WORD	x0,	WORD	x1		);
	void		assign		(	TYPE(N)	x0,	TYPE(N)	x1		);
	void		assign		(	WORD	x0,	WORD	x1,
								WORD	x2					);
	void		assign		(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2					);
	void		assign		(	WORD	x0,	WORD	x1,
								WORD	x2, WORD	x3		);
	void		assign		(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2, TYPE(N)	x3		);
	KEY			reverse		(								);
	void		flush		(								);
	//void		assign		(	WORD	x[M]				);
	//void		assignWORD	(	WORD	x,	TYPE(8)	i		);
	
	//	ACCESSORS
	void		test		(								);
	WORD		get_w		(	TYPE(8)	i					);
	WORD*		ref_w		(	TYPE(8)	i					);
	TYPE(N)		get_W		(	TYPE(8)	i					);
	TYPE(8)		get_Wb		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	get_WB		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	size		(								);
	string		HEX_WORD	(								);
	string		CHR_BYTES	(								);
	string		HEX_BYTES	(								);
	string		CHR			(								);
	
private:
	WORD		K[M];
};

class 			KEY_S
{
public:
	//	COSNTUCTORS
	KEY_S();
	//KEY_S(WORD x[T]);
	
	//	MUTATORS
	//void		assign		(	WORD	x[T]				);
	void		assign		(	WORD	x,	TYPE(8)	i		);
	void		assign		(	TYPE(N)	x,	TYPE(8)	i		);
	void		flush		(								);
	
	//	ACCESSORS
	void		test		(								);
	WORD		get_w		(	TYPE(8)	i					);
	WORD*		ref_w		(	TYPE(8)	i					);
	TYPE(N)		get_W		(	TYPE(8)	i					);
	TYPE(8)		get_Wb		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	get_WB		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	size		(								);
	string		HEX_WORD	(								);
	string		CHR_BYTES	(								);
	string		HEX_BYTES	(								);
	string		CHR			(								);
	
private:
	WORD		K[T];
};

typedef struct	_INFO_
{
	//	PACKET INFO
	TYPE(8)		mode		:	4;	//	CIPHER MODE
	TYPE(8)		in_out		:	1;	//	INPUT/OUTPUT
	TYPE(8)		data_key	:	1;	//	DATA/KEY
	TYPE(8)		enc_dec		:	1;	//	ENCRYPT/DECRYPT
	TYPE(8)		nBlocks		:	1;	//	NUMBER OF BLOCKS (1/2)
}				_INFO_;

typedef TYPE(64)	U_64;

class 			PACKET
{
public:
	//	CONSTRUCTORS
	PACKET();
	PACKET(_INFO_ x);
	
	//	MUTATORS
	void		input		(								);
	void		output		(	_INFO_	x					);
	//void		assign		(	_PACKET_	x				);
	void		assign		(	_INFO_	x					);
	void		assign		(	WORD	x,	TYPE(8)	i		);
	void		assign		(	BLOCK	x,	TYPE(8) i		);
	//void		assign		(	TYPE(N)	x,	TYPE(8)	i		);
	TYPE(8)		addWORD		(	WORD	x					);
	TYPE(8)		addBLOCK	(	BLOCK	x					);
	//TYPE(8)		addWORD		(	TYPE(N)	x					);
	void		addKEY		(	KEY		x					);
	void		pack		(								);
	void		flush		(								);
	
	//	ACCESSORS
	void		test		(								);
	TYPE(8)		checkIN		(	TYPE(16)	x				);
	TYPE(8)		get_b		(	TYPE(8)	i					);
	TYPE(16)	get_B		(	TYPE(8)	i					);
	_INFO_		get_i		(								);
	TYPE(8)		get_Ib		(								);
	TYPE(16)	get_IB		(								);
	TYPE(8)*	get_p		(								);
	TYPE(8)		get_c		(								);
	TYPE(16)	get_C		(								);
	WORD		get_w		(	TYPE(8)	i					);
	TYPE(N)		get_W		(	TYPE(8)	i					);
	TYPE(8)		get_Wb		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	get_WB		(	TYPE(8)	i, TYPE(8)	j		);
	BLOCK		get_BLK		(	TYPE(8)	i					);
	TYPE(8)		get_nxtW	(								);
	U_64		get_ICount	(								);
	U_64		get_OCount	(								);
	TYPE(16)	size		(								);
	string		HEX_WORD	(								);
	string		CHR_BYTES	(								);
	string		HEX_BYTES	(								);
	string		CHR			(								);
	string		HEX_PKT		(								);
	string		HEX_SV		(	TYPE(64)	i				);
	
	static U_64	inputCount;
	static U_64	outputCount;
	
private:
	TYPE(8)		nxtWORD;
	TYPE(8)		nxtBLOCK	:	1;
	union
	{
		TYPE(8)	iBYTE;
		_INFO_	iDATA;
	};
	TYPE(8)		count;				//	DATA COUNT
	//	PACKET DATA
	WORD		wDATA[4];			//	PACKET DATA
	
	TYPE(8)		pBYTES[2+(N/2)];
};

void			setCounts	(	U_64	x					);
void			setICount	(	U_64	x					);
void			setOCount	(	U_64	x					);
void			resetCounts	(								);
void			resetICount	(								);
void			resetOCount	(								);

typedef PACKET	PKT;
typedef BLOCK	BLK;
typedef TYPE(8)	U_8;
typedef WORD	WRD;

class			DATA
{
public:
	//	CONSTUCTORS
	DATA();
	DATA(string x);
	
	//	MUTATORS
	void		assign		(	string	x					);
	void		assign		(	KEY		x					);
	void		checkFILE	(								);
	WORD		readWORD	(								);
	PACKET		readPACKET	(								);
	PACKET		readPACKET	(	_INFO_	x					);
	PACKET		readPACKET	(	BLOCK	x0,	BLOCK	x1		);
	BLOCK		readBLOCK	(								);
	PACKET		readKEY		(								);
	void		readFILE_PKT(								);
	void		readFILE_PKT(	_INFO_	x					);
	void		addFILE_PKT	(								);
	void		addFILE_PKT	(	BLOCK	x0,	BLOCK	x1		);
	void		addFILE_PKT	(	KEY		x					);
	TYPE(64)	computePKTs	(	TYPE(64)	i				);
	void		readFILE_BLK(								);
	void		addFILE_BLK	(	BLOCK	x					);
	TYPE(64)	encryptBLKs	(	TYPE(64)	i				);
	void		decryptBLKs	(	TYPE(64)	i				);
	void		flush		(								);
	
	//	ACCESSORS
	void		test		(								);
	TYPE(8)		check		(								);
	void		writeFILE	(								);
	void		writeFILE	(	string	x					);
	string		HEX_PKT		(								);
	string		HEX_PKT_SV	(								);
	string		HEX_BLK		(								);
	string		HEX_BLK_SV	(								);
	
private:
	streampos	posFILE;
	string		nameFILE;
	TYPE(64)	sizeFILE;
	TYPE(64)	sizeBYTE;
	TYPE(64)	sizePACKET;
	TYPE(64)	sizeBLOCK;
	KEY			keyFILE;
	TYPE(8)		keyADDED	:	1;
	char		*bufferBYTE;
	WORD		bufferWORD[4];
	vector<PKT>	streamPKT_IN;
	vector<BLK>	streamBLK_IN;
	vector<PKT>	streamPKT_OUT;
	vector<BLK>	streamBLK_OUT;
	
};

class			CIPHER
{
public:
	//	CONSTRUCTORS
	CIPHER();
	
	//	MUTATORS
	PACKET		compute		(	PACKET	p					);
	BLOCK		compute		(	BLOCK	b, TYPE(8)	enc_dec	);
	void		expandKEY	(	KEY		x					);
	void		encryptDATA	(	WORD	x0,	WORD	x1		);
	void		encryptDATA	(	BLOCK	x					);
	void		decryptDATA	(	WORD	x0,	WORD	x1		);
	void		decryptDATA	(	BLOCK	x					);
	void		resetCount	(								);
	BLOCK		round		(	WORD	x					);
	WORD		expand		(	KEY		x,	TYPE(8)	i		);
	
	void		flush		(								);
	
	//	ACCESSORS
	
private:
	TYPE(8)		pktCOUNT;
	BLOCK		stateCIPHER;
	KEY_S		scheduleKEY;
	TYPE(8)		roundCOUNT;
	TYPE(8)		doneKEY	:	1;
	
};



#endif