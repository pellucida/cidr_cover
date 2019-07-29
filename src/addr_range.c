/*
// @(#) addr_range.c
// @(License-CC0)
*/

# include	<stdio.h>
# include	"netaddr.h"
# include	"addr_range.h"

void	range_list_print (range_list_t* r, FILE* output) {
	int	i	= 0;
	for (i=0; i < r->nranges; ++i) {
		addr_range_t	ar	= r->ranges[i];
		char	addr [INET_ADDRSTRLEN];
		if (inet_htop (AF_INET, &ar.addr, addr, sizeof(addr)) != 0) {
			fprintf (output, "%s/%d\n", addr, ar.mask);
		}
		else	{
			error ("Invalid address %0lx", ar.addr);
		}
	}
}

