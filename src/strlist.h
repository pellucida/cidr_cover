/*
// @(#) strlist.h
*/
# if	!defined( STRLIST_H)
# define	STRLIST_H

struct	strlist_t {	
	size_t	size;
	size_t	used;
	char**	list;
};
typedef	struct	strlist_t strlist_t;
int	strlist_grow (strlist_t* sl, size_t newsize);
int	strlist_Create (strlist_t** slp, size_t size);

static	inline	size_t	strlist_last (strlist_t* sl) {
	return	sl->used;
}
int	strlist_append_nocopy (strlist_t* sl, char* s);
int	strlist_atget_nocopy (strlist_t* sl, size_t i, char** sp);

static inline char*	strlist_at_nocopy (strlist_t* sl, size_t i) {
	char*	result	= 0;
	int	rv	= strlist_atget_nocopy (sl, i, &result);
	return	result;
}
# endif
