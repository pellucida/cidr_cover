/*
//	@(#) util.h
//	@(License-CC0)
*/
# if	!defined(UTIL_H)
# define	UTIL_H
# include	<stdio.h>

void	setprogname (const char* s);
const	char*	progname (void);
const	char*	basename (const char* s);
void	warn (char* fmt,...);
void	error (char* fmt,...);
void	fatal (char* fmt,...);
int	fgetline (FILE* f, char* b, size_t size);

# endif
