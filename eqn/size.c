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
extern YYSTYPE yyval;

setsize(p)	/* set size as found in p */
char *p;
{
	if (*p == '+')
		ps += atoi(p+1);
	else if (*p == '-')
		ps -= atoi(p+1);
	else
		ps = atoi(p);
	if(dbg)printf(".\tsetsize %s; ps = %d\n", p, ps);
}

size(p1, p2) int p1, p2; {
		/* old size in p1, new in ps */
	int effps, effp1;

	yyval.token = p2;
	if(dbg)printf(".\tb:sb: S%d <- \\s%d S%d \\s%d; b=%d, h=%d\n", 
		yyval.token, ps, p2, p1, ebase[yyval.token], eht[yyval.token]);
	effps = EFFPS(ps);
	effp1 = EFFPS(p1);
	printf(".ds %d \\s%d\\*(%d\\s%d\n", 
		yyval.token, effps, p2, effp1);
	ps = p1;
}

globsize() {
	char temp[20];

	getstr(temp, 20);
	if (temp[0] == '+')
		gsize += atoi(temp+1);
	else if (temp[0] == '-')
		gsize -= atoi(temp+1);
	else
		gsize = atoi(temp);
	yyval.token = eqnreg = 0;
	setps(gsize);
	ps = gsize;
	if (gsize >= 12)	/* sub and sup size change */
		deltaps = gsize / 4;
	else
		deltaps = gsize / 3;
}
