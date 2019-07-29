/*
// @(#) calc_cover.c - cover [begin..end] addresses (IPv4) with net/mask pairs.
*/
# include	<stdio.h>
# include       <stdlib.h>
# include       <string.h>
# include       <errno.h>

# include       "util.h"
# include	"netaddr.h"
# include	"addr_range.h"
# include	"calc_cover.h"

typedef	long long	num;

static	num	powerof2 (unsigned n) { // Inefficient but obvious
	num	result	=	1;
	unsigned	i	= 0;
	for (i=0; i < n; ++i) {
		result	= result * 2;
	}
	return	result;
}
// -----


// Algorithm to calculate the cover.

// largest (z) : (a mod 2^z) = 0 and (a + (2^z)-1) <= b
// ie a mod 2^(z+1) != 0 or a + (2^z)-1 > b

static	int	z (num a, num b) {
	int	i	= 0;
	while ((a % powerof2 (i+1)) == 0 && (a + powerof2 (i+1) - 1) <= b) {
		++i;
	}
	return	i;
}

// c[i] == IPV4_ADDR_BITS - cc->masks[i-1]
int	cidr_cover (haddr_t A, haddr_t B, range_list_t* c) {

	num	b	= (num)A - 1;
	range_list_init (c);

//	k	= 0

	do	{
//INV:		b == A + Sum(1<=j<=k)(2^c[j]) - 1

		num	a	= b + 1;
		int	n	= z (a, B); 

//		c[k+1],k,b	= z (a,B),k+1,b+2^z(a, b)

		range_list_append (c, (haddr_t)a, IPV4_ADDR_BITS - n);

		b	= b + powerof2 (n);
	} while (b != B);

//	b==B and b == A + Sum(1<=j<=k)(2^c[j]) - 1
// ==>	B == A + Sum(1<=j<=k)(2^c[j]) - 1
}

