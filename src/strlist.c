/*
// @(#) strlist.c
*/

# include	<stdlib.h>
# include	"constant.h"
# include	"strlist.h"


int	strlist_grow (strlist_t* sl, size_t newsize) {
	int	result	= err;
	if (sl->size < newsize) {
		char**	new	= realloc (sl->list, newsize * sizeof(*new));
		if (new) {
			sl->list	= new;
			sl->size	= newsize;
			result		= ok;
		}
	}
	return	result;
}
int	strlist_Create (strlist_t** slp, size_t size) {
	int	result	= ok;
	strlist_t*	sl	= calloc (1, sizeof (*sl));
	if (sl) {
		sl->size	= 0;
		sl->used	= 0;
		sl->list	= 0;
		if (size > 0) {
			result	= strlist_grow (sl, size);
		}
		if (result==ok) {
			*slp	= sl;
		}
		else	{
			free (sl);
		}
	}
	return	result;
}
int	strlist_Delete (strlist_t** slp) {
	if (slp) {
		strlist_t*	sl	= *slp;
		if (sl->list) {
			free (sl->list);
		}
		free (sl);
		*slp	= 0;
	}
	return	ok;
}
int	strlist_append_nocopy (strlist_t* sl, char* s){
	int	result	= err;
	if (sl->used < sl->size) {
		sl->list [sl->used++]	= s;
		result	= ok;
	}
	else	{
		result	= strlist_grow (sl, sl->used+1);
		if (result==ok) {
			result	= strlist_append_nocopy (sl, s);
		}
	}
	return	result;
}
int	strlist_atget_nocopy (strlist_t* sl, size_t i, char** sp) {
	int	result	= err;
	if (i < sl->used) {
		*sp	= sl->list [i];
		result	= ok;
	}
	return	result;
}
