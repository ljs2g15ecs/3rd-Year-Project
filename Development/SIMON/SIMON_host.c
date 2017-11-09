#include "SIMON_host.h"

int		main()
{
	printf("Hello There!!!\n\r");
	
	printf("|\tN:\t%d\t|\tM:\t%d\t|\tR:\t%d\t|\n", N, M, R);
	printf("|\tW:\t%d\t|\tB:\t%d\t|\tK:\t%d\t|\n", sizeof(word)*8, sizeof(block)*8, sizeof(key)*8);

	word a;
	a = (0xF<<(N-4));
	
	PRINTHEX(a);
	ROTL(&a, 2);
	PRINTHEX(a);
	ROTR(&a, 1);
	PRINTHEX(a);
	ROTR(&a, 1);
	PRINTHEX(a);
	
	return 0;
}

void	ROTL(word *x, uint8_t n)
{
	*x = (*x << n) | (*x >> (N-n));
	*x &= (1<<N)-1;
}

void	ROTR(word *x, uint8_t n)
{
	*x = (*x << (N-n)) | (*x >> n);
	*x &= (1<<N)-1;
}
	

