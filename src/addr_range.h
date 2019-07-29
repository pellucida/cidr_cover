/*
// @(#) addr_range.h
// @(License-CC0)
*/

# if	!defined( ADDR_RANGE_H)
# define	ADDR_RANGE_H

# include	<stdio.h>
# include	"netaddr.h"

enum	{ MAXRANGES	= 63, };

typedef	struct	addr_range addr_range_t;
struct	addr_range {
	haddr_t	addr;
	int	mask;
};

typedef	struct	range_list	range_list_t;
struct	range_list	{
	size_t		nranges;
	addr_range_t	ranges [MAXRANGES];
};

static	inline	void	range_list_init (range_list_t* r) {
	r->nranges	= 0;
}

static	inline void	range_list_append (range_list_t* r, haddr_t addr, int mask) {
	addr_range_t	ar	= { .addr = addr, .mask = mask };
	r->ranges[r->nranges++]	= ar;
}

void	range_list_print (range_list_t* r, FILE* output);

# endif
