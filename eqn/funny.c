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
  
#ident	"%Z%%M%	%I%	%E% SMI"	/* SVr4.0 1.1	*/

#include "e.h"
#include "y.tab.h"
#include <locale.h>
extern YYSTYPE yyval;

funny(n) int n; {
	char *f;

	yyval.token = oalloc();
	switch(n) {
	case SUM:
		f = "\\(*S"; break;
	case UNION:
		f = "\\(cu"; break;
	case INTER:	/* intersection */
		f = "\\(ca"; break;
	case PROD:
		f = "\\(*P"; break;
	default:
		error(FATAL, gettext("funny type %d in funny"), n);
	}
#ifndef NEQN
	printf(".ds %d \\s%d\\v'.3m'\\s+5%s\\s-5\\v'-.3m'\\s%d\n", yyval.token, ps, f, ps);
	eht[yyval.token] = VERT(EM(1.0, ps+5) - EM(0.2, ps));
	ebase[yyval.token] = VERT(EM(0.3, ps));
#else /* NEQN */
	printf(".ds %d %s\n", yyval.token, f);
	eht[yyval.token] = VERT(2);
	ebase[yyval.token] = 0;
#endif /* NEQN */
	if(dbg)printf(".\tfunny: S%d <- %s; h=%d b=%d\n", 
		yyval.token, f, eht[yyval.token], ebase[yyval.token]);
	lfont[yyval.token] = rfont[yyval.token] = ROM;
}
