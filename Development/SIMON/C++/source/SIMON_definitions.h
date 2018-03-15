#ifndef	SIMON_DEF_H
#define SIMON_DEF_H

using namespace std;

#if		defined	S3264
	#define MODE	0
	#define N 		16
	#define M 		4
	#define T 		32
	#define	J 		0
#elif	defined S4872
	#define MODE	1
	#define N 		24
	#define M 		3
	#define T 		36
	#define	J 		0
#elif	defined S4896
	#define MODE	2
	#define N 		24
	#define M 		4
	#define T 		36
	#define	J 		1
#elif	defined S6496
	#define MODE	3
	#define N 		32
	#define M 		3
	#define T 		42
	#define	J 		2
#elif	defined S64128
	#define MODE	4
	#define N 		32
	#define M 		4
	#define T 		44
	#define	J 		3
#elif	defined S9696
	#define MODE	5
	#define N 		48
	#define M 		2
	#define T 		52
	#define	J 		2
#elif	defined S96144
	#define MODE	6
	#define N 		48
	#define M 		3
	#define T 		54
	#define	J 		3
#elif	defined S128128
	#define MODE	7
	#define N 		64
	#define M 		2
	#define T 		68
	#define	J 		2
#elif	defined S128192
	#define MODE	8
	#define N 		64
	#define M 		3
	#define T 		69
	#define	J 		3
#elif	defined S128256
	#define MODE	9
	#define N 		64
	#define M 		4
	#define T 		72
	#define	J 		4
#else
	#error INVALID MODE
#endif

#include <cstdint>
#include <string>

typedef uint32_t	uint24_t;
typedef uint64_t	uint48_t;
#define TYPE_(x)	uint ## x ## _t
#define TYPE(x)		TYPE_(x)

class WORD
{
public:
	//	COSNTUCTORS
	WORD					(								);
	WORD					(	TYPE(N)	x					);
	//	MUTATORS
	void		assign		(	TYPE(N)	x					);
	void		assign		(	TYPE(8)	x, TYPE(8)	i		);
	void		flush		(								);
	
	//	ACCESSORS
	void		test		(								);
	TYPE(N)		get_v		(								);
	TYPE(8)		get_b		(	TYPE(8)	i					);
	TYPE(16)	get_B		(	TYPE(8)	i					);
	TYPE(16)	size_v		(								);
	TYPE(16)	size_b		(								);
	string		strHEX_WORD	(								);
	string		strCHR_BYTES(								);
	string		strHEX_BYTES(								);
private:
	union
	{
		TYPE(N)	val	:	N;
		TYPE(8)	bytes[N/8];
	};
};

class BLOCK
{
public:
	//	COSNTUCTORS
	BLOCK					(								);
	BLOCK					(	TYPE(N)	x0,	TYPE(N)	x1		);
	BLOCK					(	WORD	x0, WORD	x1		);
	//	MUTATORS
	void		assign		(	TYPE(N)	x0,	TYPE(N)	x1		);
	void		assign		(	WORD	x0, WORD	x1		);
	void		assign		(	TYPE(N)	x,	TYPE(8)	i		);
	void		assign		(	WORD	x,	TYPE(8)	i		);
	void		flush		(								);
	
	//	ACCESSORS
	void		test		(								);
	WORD		get_w		(	TYPE(8)	i					);
	TYPE(N)		get_W		(	TYPE(8)	i					);
	TYPE(8)		get_Wb		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	get_WB		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	size		(								);
	string		strHEX_WORD	(								);
	string		strCHR_BYTES(								);
	string		strHEX_BYTES(								);
private:
	WORD		B[2];
};

class KEY
{
public:
	//	COSNTUCTORS
	KEY						(								);
	//KEY						(	WORD	x[M]				);
	//KEY						(	TYPE(N)	x[M]				);
#if (M == 2)
	KEY						(	WORD	x0,	WORD	x1		);
	KEY						(	TYPE(N)	x0,	TYPE(N)	x1		);
#endif
#if (M == 3)
	KEY						(	WORD	x0,	WORD	x1,
								WORD	x2					);
	KEY						(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2					);
#endif
#if (M == 4)
	KEY						(	WORD	x0,	WORD	x1,
								WORD	x2, WORD	x3		);
	KEY						(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2, TYPE(N)	x3		);
	//	MUTATORS
	void		assign		(	WORD	x0,	WORD	x1,
								WORD	x2, WORD	x3		);
	void		assign		(	TYPE(N)	x0,	TYPE(N)	x1,
								TYPE(N)	x2, TYPE(N)	x3		);
#endif
	//	MUTATORS
	void		flush		(								);
	//void		assign		(	WORD	x[M]				);
	//void		assignWORD	(	WORD	x,	TYPE(8)	i		);
	
	//	ACCESSORS
	void		test		(								);
	WORD		get_w		(	TYPE(8)	i					);
	TYPE(N)		get_W		(	TYPE(8)	i					);
	TYPE(8)		get_Wb		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	get_WB		(	TYPE(8)	i, TYPE(8)	j		);
	TYPE(16)	size		(								);
	string		strHEX_WORD	(								);
	string		strCHR_BYTES(								);
	string		strHEX_BYTES(								);
private:
	WORD		K[M];
};

/*
class KEY_S
{
public:
	//	COSNTUCTORS
	KEY_S					(							);
	KEY_S					(WORD	x[T]				);
	//	MUTATORS
	void		assign		(WORD	x[T]				);
	void		assignWORD	(WORD	x,	TYPE(8)	i		);
	void		flush		(							);
	
	//	ACCESSORS
	void		test		(							);
	WORD		get_b		(TYPE(8)	i				);
	TYPE(16)	size		(							);
	string		strHEX_WORD	(							);
	string		strCHR_BYTES(							);
	string		strHEX_BYTES(							);
private:
	WORD		b[T];
};
//*/

#endif