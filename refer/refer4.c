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

#include <string.h>
#include "refer..c"
#include <locale.h>

#define punctuat(c) (c=='.' || c=='?' || c=='!' || c==',' || c==';' || c==':')

static gate = 0;
static char buff[BUFSIZ];

output(s)
char *s;
{
	if (gate)
		fputs(buff,ftemp);
	else
		gate = 1;
	strcpy(buff, s);
	if (strlen(buff) > BUFSIZ)
		err(gettext("one buff too big (%d)!"), BUFSIZ);
}

append(s)
char *s;
{
	char *p;
	int lch;

	trimnl(buff);
	for (p = buff; *p; p++)
		;
	lch = *--p;
	if (postpunct && punctuat(lch))
		*p = 0;
	else /* pre-punctuation */
		switch (lch) {
		case '.': 
		case '?':
		case '!':
		case ',':
		case ';':
		case ':':
			*p++ = lch;
			*p = 0;
		}
	strcat(buff, s);
	if (postpunct)
		switch(lch) {
		case '.': 
		case '?':
		case '!':
		case ',':
		case ';':
		case ':':
			for(p = buff; *p; p++)
				;
			if (*--p == '\n')
				*p = 0;
			*p++ = lch;
			*p++ = '\n';
			*p = 0;
		}
	if (strlen(buff) > BUFSIZ)
		err(gettext("output buff too long (%d)"), BUFSIZ);
}

flout()
{
	if (gate)
		fputs(buff,ftemp);
	gate = 0;
}

char *
trimnl(ln)
char *ln;
{
	register char *p = ln;

	while (*p)
		p++;
	p--;
	if (*p == '\n')
		*p = 0;
	return(ln);
}
