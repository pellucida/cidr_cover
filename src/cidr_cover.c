/*
// @(#) cidr_cover.c
// @(License-CC0)
*/
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>

# include	"constant.h"
# include	"strlist.h"
# include	"util.h"
# include	"netaddr.h"
# include	"addr_range.h"
# include	"calc_cover.h"

void    Usage() {
        fprintf (stderr, "Usage: %s [-R range [-R range]...] [files...]\n", progname());
        exit (EXIT_FAILURE);
}


static	int	process_line (char* line, FILE* output);
static  int     process_file (FILE* input, FILE* output);


main (int argc, char* argv[]) {
	FILE*	input	= stdin;
	FILE*	output	= stdout;
	int	opt	= EOF;

	strlist_t*	rlist	= 0;
	strlist_Create (&rlist, 0);

	setprogname (argv[0]);

	while ((opt = getopt (argc,argv, "hR:"))!=EOF) {
		switch (opt) {
		case	'R':
			strlist_append_nocopy (rlist, optarg);
		break;
			
		case	'h':
		default:
			Usage ();
		}
	}
	if (strlist_last (rlist) > 0) {
		int	i	= 0;
		for (i=0; i < strlist_last (rlist); ++i) {
			process_line (strlist_at_nocopy (rlist, i), output);
		}
	}
	else if (optind == argc) {
		process_file (input, output);
	}
	for (; optind < argc; optind++) {
		input	=  fopen (argv [optind], "r");
		if (input==0) {
			error ("Cannot open file: \"%s\"\n", argv [optind]);
		}
		else	{
			process_file (input, output);
			fclose (input);
		}
	}
}


static	int	process_line (char* line, FILE* output) {
	char*		t	= strpbrk (line, "-\t ");
	if (t != 0) {
		haddr_t	start	= 0;
		haddr_t	finish	= 0;
		*t++	= '\0';
		if (inet_ptoh (AF_INET, line, &start) == ADDR_OK) {
			if (inet_ptoh (AF_INET, t, &finish) == ADDR_OK) {

				range_list_t	r	= {.nranges = 0, };

				if (start > finish) {
					haddr_t	tmp	= start;
					warn ("Address range END < START %s-%s - swapping\n", line, t);
					start	= finish;
					finish	= tmp;
				}
				cidr_cover (start, finish, &r);
				range_list_print (&r, output);
			}
			else	{
				error ("Address range error (END) %s-%s\n", line, t);
			}
		}
		else	{
			error ("Address range error (START) %s-%s\n", line, t);
		}
	}
	return	ok;
}
static	int	process_file (FILE* input, FILE* output) {
	char	line [BUFSIZ];
	int	result	= ok;
	while (result == ok && fgetline (input, line, sizeof(line)) != EOF) {
		result	= process_line (line, output);
	}
	return	result;
}
