/*
// @(#) cidr_cover.c - cover [begin..end] addresses (IPv4) with net/mask pairs.
*/
# include	<stdio.h>
# include       <stdlib.h>
# include       <errno.h>
# include       <arpa/inet.h>

enum    { IPV4_ADDR_BITS  = 32, };
typedef	in_addr_t	haddr_t;	// Reminds us that its Host Byte Order

typedef	long long	num;

static	num	powerof2 (unsigned n) { // Inefficient but obvious
	num	result	=	1;
	unsigned	i	= 0;
	for (i=0; i < n; ++i) {
		result	= result * 2;
	}
	return	result;
}

/*
// Work in Host Byte Order - as we never actually use the net addresses.
*/
int	inet_ptoh (int family, const char* src, void* dst) {
	in_addr_t	addr	= 0;
	int	result	= -1;
	if (family != AF_INET) {
		errno	= EAFNOSUPPORT;
	}
	else	{
		result	= inet_pton (family, src, &addr);
		if (result == 1) {
			*((haddr_t*)(dst))	= ntohl(addr);
		}
	}
	return	result;
}
const char*  inet_htop (int family,const void *src,char *dst,socklen_t size) {
	const	char*	result	= 0;
	if (family != AF_INET) {
		errno	= EAFNOSUPPORT;
	}
	else	{	
		haddr_t	addr	= *((haddr_t*)(src));
		in_addr_t	naddr	= htonl (addr);
		result	= inet_ntop (family, &naddr, dst, size);
	}
	return	result;
}
// ----

// ---- cover data structure 

enum	{ MAXMASKS	= 63, };
typedef	unsigned char	cidr_t;

struct	cidr_cover	{		// 68 bytes
	haddr_t	address;	// start address NBO
	cidr_t	nmasks;
	cidr_t	masks[MAXMASKS];
};
typedef	struct	cidr_cover	CIDR_COVER;

static	inline	void cidr_cover_init (CIDR_COVER* cc, haddr_t start) {
	cc->address	= start;
	cc->nmasks	= 0;
}
static	inline	cidr_cover_append (CIDR_COVER* cc, cidr_t mask) {
	cc->masks[cc->nmasks++]	= mask;
}

int	print_cidr_cover (FILE* output, CIDR_COVER* cc) {
	cidr_t	i	= 0;
	unsigned long	a	= cc->address;
	cidr_t		nmasks	= cc->nmasks;
	cidr_t*		masks	= cc->masks;

	for (i=0; i < nmasks; ++i) {
		char    addr[INET_ADDRSTRLEN];
		haddr_t	ha	= a;		// easier than casting
		inet_htop (AF_INET, &ha, addr, sizeof(addr));

		fprintf (output, "%s/%d\n", addr, masks[i]);
		a	= a + powerof2 (IPV4_ADDR_BITS - masks[i]);
	}
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
int	cidr_cover (haddr_t A, haddr_t B, CIDR_COVER* cc) {

	num	b	= (num)A - 1;
	cidr_cover_init (cc, A);

//	k	= 0

	do	{
//INV:		b == A + Sum(1<=j<=k)(2^c[j]) - 1

		num	a	= b + 1;
		int	n	= z (a, B);

//		c[k+1],k,b	= z (a,B),k+1,b+2^z(a, b)

		cidr_cover_append (cc, IPV4_ADDR_BITS-n);
		b	= b + powerof2 (n);
	} while (b != B);

//	b==B and b == A + Sum(1<=j<=k)(2^c[j]) - 1
// ==>	B == A + Sum(1<=j<=k)(2^c[j]) - 1
}


# if	defined(TEST)

main (int argc, char* argv[]) {
	CIDR_COVER	cc;
	in_addr_t	start	= 0;
	in_addr_t	finish	= 0;
	if (argc != 3) {
		fprintf (stderr, "Usage: %s start-address end-address\n", argv[0]);
		exit (1);
	}
	inet_ptoh (AF_INET, argv[1], &start);
	inet_ptoh (AF_INET, argv[2], &finish);
	cidr_cover (start, finish, &cc);	
	print_cidr_cover (stdout, &cc);
}
# endif
