/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/


/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved. The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*
 * Copyright (c) 1983, 1984 1985, 1986, 1987, 1988, Sun Microsystems, Inc.
 * All Rights Reserved.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI" 

#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include "refer..c"

main(argc, argv)	/* look in biblio for record matching keywords */
int argc;
char **argv;
{
	FILE *hfp, *fopen(), *popen();
	char s[BUFSIZ], hunt[64];

	(void) setlocale(LC_ALL, "");

	if (argc == 1 || argc > 2) {
		fputs(gettext("Usage:  lookbib database\n\
\tfinds citations specified on standard input\n"), stderr);
		exit(1);
	}
	sprintf(s, "%s.ia", argv[1]);
	if (access(s, 0) == -1) {
		sprintf (s, "%s", argv[1]);
		if (access(s, 0) == -1) {
			perror(s);
			fprintf(stderr, gettext("\tNeither index file %s.ia \
nor reference file %s found\n"), s, s);
			exit(1);
		}
	}
	sprintf(hunt, "/usr/lib/refer/hunt %s", argv[1]);
	if (isatty(fileno(stdin))) {
		fprintf(stderr, gettext("Instructions? "));
		fgets(s, BUFSIZ, stdin);
		if (*s == 'y')
			instruct();
	}
   again:
	fprintf(stderr, "> ");
	if (fgets(s, BUFSIZ, stdin)) {
		if (*s == '\n')
			goto again;
		if (strlen(s) <= 3)
			goto again;
		if ((hfp = popen(hunt, "w")) == NULL) {
			perror(gettext("lookbib: /usr/lib/refer/hunt"));
			exit(1);
		}
		map_lower(s);
		fputs(s, hfp);
		pclose(hfp);
		goto again;
	}
	fprintf(stderr, gettext("EOT\n"));
	exit(0);
	/* NOTREACHED */
}

map_lower(s)		/* map string s to lower case */
char *s;
{
	for ( ; *s; ++s)
		if (isupper(*s))
			*s = tolower(*s);
}

instruct()
{
	fputs(gettext(
"\nType keywords (such as author and date) after the > prompt.\n\
References with those keywords are printed if they exist;\n\
\tif nothing matches you are given another prompt.\n\
To quit lookbib, press CTRL-d after the > prompt.\n\n"), stderr);

}
