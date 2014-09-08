/*	Co/pyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
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
  
#ident	"%Z%%M%	%I%	%E% SMI"	/* SVr4.0 1.1	*/

 /* t1.c: main control and input switching */
#
#include <locale.h>
# include "t..c"
#include <signal.h>
#include <stdlib.h>
# ifdef gcos
/* required by GCOS because file is passed to "tbl" by troff preprocessor */
# define _f1 _f
extern FILE *_f[];
# endif

# ifndef gcos
# define MACROS "/usr/doctools/tmac/tmac.s"
# define MACROSS TMACDIR "/s"
# define PYMACS "/usr/doctools/tmac/tmac.m"
# define PYMACSS TMACDIR "/m"
# define MEMACSS TMACDIR "/e"
# endif

# ifdef gcos
# define MACROS "cc/troff/smac"
# define PYMACS "cc/troff/mmac"
# endif

# define ever (;;)

main(argc,argv)
	char *argv[];
{
# ifndef gcos
void badsig();
# endif
	(void) setlocale(LC_ALL, "");
# ifndef gcos
signal(SIGPIPE, badsig);
# endif
# ifdef gcos
if(!intss()) tabout = fopen("qq", "w"); /* default media code is type 5 */
# endif
exit(tbl(argc,argv));
}


tbl(argc,argv)
	char *argv[];
{
char line[BIGBUF];
/* required by GCOS because "stdout" is set by troff preprocessor */
tabin=stdin; tabout=stdout;
setinp(argc,argv);
while (gets1(line, sizeof line))
	{
	fprintf(tabout, "%s\n",line);
	if (prefix(".TS", line))
		tableput();
	}
fclose(tabin);
return(0);
}
int sargc;
char **sargv;
setinp(argc,argv)
	char **argv;
{
	sargc = argc;
	sargv = argv;
	sargc--; sargv++;
	if (sargc>0)
		swapin();
}
swapin()
{
	while (sargc>0 && **sargv=='-') /* Mem fault if no test on sargc */
		{
		if (sargc<=0) return(0);
		if (match("-me", *sargv))
			{
			*sargv = MEMACSS;
			break;
			}
		if (match("-ms", *sargv))
			{
			*sargv = MACROSS;
			break;
			}
		if (match("-mm", *sargv))
			{
			*sargv = PYMACSS;
			break;
			}
		if (match("-TX", *sargv))
			pr1403=1;
		else {
			(void) fprintf(stderr, gettext("tbl: Invalid option "
			    "(%s).\n"), *sargv);
			(void) fprintf(stderr, gettext("Usage: tbl [ -me ] "
			    "[ -mm ] [ -ms ] [ filename ] ...\n"));
			exit(1);
		}
		sargc--; sargv++;
		}
	if (sargc<=0) return(0);
# ifndef gcos
/* file closing is done by GCOS troff preprocessor */
	if (tabin!=stdin) fclose(tabin);
# endif
	tabin = fopen(ifile= *sargv, "r");
	iline=1;
# ifndef gcos
/* file names are all put into f. by the GCOS troff preprocessor */
	fprintf(tabout, ".ds f. %s\n",ifile);
# endif
	if (tabin==NULL)
		error(gettext("Can't open file"));
	sargc--;
	sargv++;
	return(1);
}
# ifndef gcos
void badsig()
{
signal(SIGPIPE, SIG_IGN);
 exit(0);
}
# endif
