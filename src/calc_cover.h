/*
// @(#) calc_cover.h
// @(License-CC0)
*/
# if	!defined( CALC_COVER_H)
# include	"netaddr.h"
# include	"addr_range.h"

int	cidr_cover (haddr_t A, haddr_t B, range_list_t* c); 

# endif
