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

boverb(p1, p2) int p1, p2; {
	int h, b, treg, d;

	treg = oalloc();
	yyval.token = p1;
#ifndef NEQN
	d = VERT(EM(0.3, ps));
	h = eht[p1] + eht[p2] + d;
#else /* NEQN */
	d = VERT(1);
	h = eht[p1] + eht[p2];
#endif /* NEQN */
	b = eht[p2] - d;
	if(dbg)printf(".\tb:bob: S%d <- S%d over S%d; b=%d, h=%d\n", 
		yyval.token, p1, p2, b, h);
	nrwid(p1, ps, p1);
	nrwid(p2, ps, p2);
	printf(".nr %d \\n(%d\n", treg, p1);
	printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, treg, treg, p2);
#ifndef NEQN
	printf(".nr %d \\n(%d+\\s%d.5m\\s0\n", treg, treg, EFFPS(ps));
#endif /* NEQN */
	printf(".ds %d \\v'%du'\\h'\\n(%du-\\n(%du/2u'\\*(%d\\\n", 
		yyval.token, eht[p2]-ebase[p2]-d, treg, p2, p2);
	printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\*(%d\\\n", 
#ifndef NEQN
		p2, p1, -(eht[p2]-ebase[p2]+d+ebase[p1]), p1);
	printf("\\h'-\\n(%du-\\n(%du/2u+.1m'\\v'%du'\\l'\\n(%du-.2m'\\h'.1m'\\v'%du'\n", 
		 treg, p1, ebase[p1]+d, treg, d);
#else /* NEQN */
		p2, p1, -eht[p2]+ebase[p2]-ebase[p1], p1);
	printf("\\h'-\\n(%du-\\n(%du-2u/2u'\\v'%du'\\l'\\n(%du'\\v'%du'\n", 
		 treg, p1, ebase[p1], treg, d);
#endif /* NEQN */
	ebase[yyval.token] = b;
	eht[yyval.token] = h;
	lfont[yyval.token] = rfont[yyval.token] = 0;
	ofree(p2);
	ofree(treg);
}
