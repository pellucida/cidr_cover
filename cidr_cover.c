/*
// @(#) cidr_cover.c - cover [begin..end] addresses (IPv4) with net/mask pairs.
*/
# include	<stdio.h>
# include       <stdlib.h>
# include       <errno.h>
# include       <arpa/inet.h>

enum    { IPV4_ADDR_BITS  = 32, };
typedef	in_addr_t	haddr_t;	// Reminds us that its Host Byte Order

//
// Work in Host Byte Order - as we never actually use the net addresses.
//
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
		a	= a + (1lu<<(IPV4_ADDR_BITS-masks[i]));
	}
}

// -----


// Algorithm to calculate the cover.

const	unsigned long	MASK	= ~((~0ul)<<IPV4_ADDR_BITS);

int	cidr_cover (haddr_t A, haddr_t B, CIDR_COVER* cc) {
	unsigned long	a	= A;
	unsigned long	b	= B;

	int	m	= IPV4_ADDR_BITS;
	int	n	= 0;

	cc->address	= A;	// Start address HBO
	cc->nmasks	= 0;

	while (a!=(b+1)) {
		if (n==m) {
			// a & MASK>>n == 0
			while ((a & (MASK>>(n-1)))==0) {
				n	= n - 1;
			}
			// ~G: a & MASK>>(n-1) !=0, INV: a & MASK>>n == 0
		}
		else	{
			while ((a & (MASK>>(n)))!=0) {
				n	= n + 1;
			}
			// ~G: a & MASK>>n == 0, INV: a & MASK>>n-1 != 0
		}
		//    n==m => ~G: a & MASK>>(n-1) !=0, INV: a & MASK>>n == 0
		// || n!=m => ~G: a & MASK>>n == 0, INV: a & MASK>>n-1 != 0
		// =>    a & MASK>>n == 0 && a & MASK>>n-1 !=0 (n maximal)

		m	= n;
		while ((a + (1lu<<(IPV4_ADDR_BITS-n))) > (b+1)) {
			n	= n + 1;
		}
		// ~G: a + 2^32-n  <= b+1, INV: a + 2^32-(n-1) > b+1 (n maximal)

		cidr_cover_append (cc, n); // Add a/n

		a	= a + (1lu<<(IPV4_ADDR_BITS-n));
	}
	// ~G: a == b+1
}

# if	defined(TEST)

main (int argc, char* argv[]) {
	CIDR_COVER	cc;
	in_addr_t	start	= 0;
	in_addr_t	finish	= MASK;
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
