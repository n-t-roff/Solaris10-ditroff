/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/


/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved. The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

/*
 * checknr: check an nroff/troff input file for matching macro calls.
 * we also attempt to match size and font changes, but only the embedded
 * kind.  These must end in \s0 and \fP resp.  Maybe more sophistication
 * later but for now think of these restrictions as contributions to
 * structured typesetting.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define gettext(x) x
#define	MAXSTK	100	/* Stack size */
static	int	maxstk;
#define	MAXBR	100	/* Max number of bracket pairs known */
#define	MAXCMDS	500	/* Max number of commands known */

/*
 * The stack on which we remember what we've seen so far.
 */
static struct stkstr {
	int opno;	/* number of opening bracket */
	int pl;		/* '+', '-', ' ' for \s, 1 for \f, 0 for .ft */
	int parm;	/* parm to size, font, etc */
	int lno;	/* line number the thing came in in */
} *stk;
static int stktop;

/*
 * The kinds of opening and closing brackets.
 */
static struct brstr {
	char *opbr;
	char *clbr;
} br[MAXBR] = {
	/* A few bare bones troff commands */
#define	SZ	0
	"sz",	"sz",	/* also \s */
#define	FT	1
	"ft",	"ft",	/* also \f */
	/* the -mm package */
	"AL",	"LE",
	"AS",	"AE",
	"BL",	"LE",
	"BS",	"BE",
	"DF",	"DE",
	"DL",	"LE",
	"DS",	"DE",
	"FS",	"FE",
	"ML",	"LE",
	"NS",	"NE",
	"RL",	"LE",
	"VL",	"LE",
	/* the -ms package */
	"AB",	"AE",
	"BD",	"DE",
	"CD",	"DE",
	"DS",	"DE",
	"FS",	"FE",
	"ID",	"DE",
	"KF",	"KE",
	"KS",	"KE",
	"LD",	"DE",
	"LG",	"NL",
	"QS",	"QE",
	"RS",	"RE",
	"SM",	"NL",
	"XA",	"XE",
	"XS",	"XE",
	/* The -me package */
	"(b",	")b",
	"(c",	")c",
	"(d",	")d",
	"(f",	")f",
	"(l",	")l",
	"(q",	")q",
	"(x",	")x",
	"(z",	")z",
	/* Things needed by preprocessors */
	"EQ",	"EN",
	"TS",	"TE",
	/* Refer */
	"[",	"]",
	0,	0
};

/*
 * All commands known to nroff, plus macro packages.
 * Used so we can complain about unrecognized commands.
 */
static char *knowncmds[MAXCMDS] = {
"$c", "$f", "$h", "$p", "$s", "(b", "(c", "(d", "(f", "(l", "(q", "(t",
"(x", "(z", ")b", ")c", ")d", ")f", ")l", ")q", ")t", ")x", ")z", "++",
"+c", "1C", "1c", "2C", "2c", "@(", "@)", "@C", "@D", "@F", "@I", "@M",
"@c", "@e", "@f", "@h", "@m", "@n", "@o", "@p", "@r", "@t", "@z", "AB",
"AE", "AF", "AI", "AL", "AM", "AS", "AT", "AU", "AX", "B",  "B1", "B2",
"BD", "BE", "BG", "BL", "BS", "BT", "BX", "C1", "C2", "CD", "CM", "CT",
"D",  "DA", "DE", "DF", "DL", "DS", "DT", "EC", "EF", "EG", "EH", "EM",
"EN", "EQ", "EX", "FA", "FD", "FE", "FG", "FJ", "FK", "FL", "FN", "FO",
"FQ", "FS", "FV", "FX", "H",  "HC", "HD", "HM", "HO", "HU", "I",  "ID",
"IE", "IH", "IM", "IP", "IX", "IZ", "KD", "KE", "KF", "KQ", "KS", "LB",
"LC", "LD", "LE", "LG", "LI", "LP", "MC", "ME", "MF", "MH", "ML", "MR",
"MT", "ND", "NE", "NH", "NL", "NP", "NS", "OF", "OH", "OK", "OP", "P",
"P1", "PF", "PH", "PP", "PT", "PX", "PY", "QE", "QP", "QS", "R",  "RA",
"RC", "RE", "RL", "RP", "RQ", "RS", "RT", "S",  "S0", "S2", "S3", "SA",
"SG", "SH", "SK", "SM", "SP", "SY", "T&", "TA", "TB", "TC", "TD", "TE",
"TH", "TL", "TM", "TP", "TQ", "TR", "TS", "TX", "UL", "US", "UX", "VL",
"WC", "WH", "XA", "XD", "XE", "XF", "XK", "XP", "XS", "[",  "[-", "[0",
"[1", "[2", "[3", "[4", "[5", "[<", "[>", "[]", "]",  "]-", "]<", "]>",
"][", "ab", "ac", "ad", "af", "am", "ar", "as", "b",  "ba", "bc", "bd",
"bi", "bl", "bp", "br", "bx", "c.", "c2", "cc", "ce", "cf", "ch", "cs",
"ct", "cu", "da", "de", "di", "dl", "dn", "ds", "dt", "dw", "dy", "ec",
"ef", "eh", "el", "em", "eo", "ep", "ev", "ex", "fc", "fi", "fl", "fo",
"fp", "ft", "fz", "hc", "he", "hl", "hp", "ht", "hw", "hx", "hy", "i",
"ie", "if", "ig", "in", "ip", "it", "ix", "lc", "lg", "li", "ll", "ln",
"lo", "lp", "ls", "lt", "m1", "m2", "m3", "m4", "mc", "mk", "mo", "n1",
"n2", "na", "ne", "nf", "nh", "nl", "nm", "nn", "np", "nr", "ns", "nx",
"of", "oh", "os", "pa", "pc", "pi", "pl", "pm", "pn", "po", "pp", "ps",
"q",  "r",  "rb", "rd", "re", "rm", "rn", "ro", "rr", "rs", "rt", "sb",
"sc", "sh", "sk", "so", "sp", "ss", "st", "sv", "sz", "ta", "tc", "th",
"ti", "tl", "tm", "tp", "tr", "u",  "uf", "uh", "ul", "vs", "wh", "xp",
"yr", 0
};

static	int	lineno;		/* current line number in input file */
static	char	line[256];	/* the current line */
static	char	*cfilename;	/* name of current file */
static	int	nfiles;		/* number of files to process */
static	int	fflag;		/* -f: ignore \f */
static	int	sflag;		/* -s: ignore \s */
static	int	ncmds;		/* size of knowncmds */
static	int	slot;		/* slot in knowncmds found by binsrch */

static void growstk();
static void usage();
static void process(FILE *f);
static void complain(int i);
static void prop(int i);
static void chkcmd(char *line, char *mac);
static void nomatch(char *mac);
static int eq(char *s1, char *s2);
static void pe(int lineno);
static void checkknown(char *mac);
static void addcmd(char *line);
static void addmac(char *mac);
static int binsrch(char *mac);

static void
growstk()
{
	stktop++;
	if (stktop >= maxstk) {
		maxstk *= 2;
		stk = (struct stkstr *)realloc(stk,
		    sizeof (struct stkstr) * maxstk);
	}
}

int
main(argc, argv)
int argc;
char **argv;
{
	FILE *f;
	int i;
	char *cp;
	char b1[4];

	(void) setlocale(LC_ALL, "");
	stk = (struct stkstr *)calloc(sizeof (struct stkstr), 100);
	maxstk = 100;
	/* Figure out how many known commands there are */
	while (knowncmds[ncmds])
		ncmds++;
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {

		/* -a: add pairs of macros */
		case 'a':
			i = strlen(argv[1]) - 2;
			if (i % 6 != 0)
				usage();
			/* look for empty macro slots */
			for (i = 0; br[i].opbr; i++)
				;
			for (cp = argv[1]+3; cp[-1]; cp += 6) {
				br[i].opbr = malloc(3);
				(void) strncpy(br[i].opbr, cp, 2);
				br[i].clbr = malloc(3);
				(void) strncpy(br[i].clbr, cp+3, 2);
				/* knows pairs are also known cmds */
				addmac(br[i].opbr);
				addmac(br[i].clbr);
				i++;
			}
			break;

		/* -c: add known commands */
		case 'c':
			i = strlen(argv[1]) - 2;
			if (i % 3 != 0)
				usage();
			for (cp = argv[1]+3; cp[-1]; cp += 3) {
				if (cp[2] && cp[2] != '.')
					usage();
				(void) strncpy(b1, cp, 2);
				addmac(b1);
			}
			break;

		/* -f: ignore font changes */
		case 'f':
			fflag = 1;
			break;

		/* -s: ignore size changes */
		case 's':
			sflag = 1;
			break;
		default:
			usage();
		}
		argc--; argv++;
	}

	nfiles = argc - 1;

	if (nfiles > 0) {
		for (i = 1; i < argc; i++) {
			cfilename = argv[i];
			f = fopen(cfilename, "r");
			if (f == NULL) {
				perror(cfilename);
				exit(1);
				}
			else
				process(f);
		}
	} else {
		cfilename = "stdin";
		process(stdin);
	}
	return (0);
}

static void
usage()
{
	(void) printf(gettext("Usage: \
checknr [ -fs ] [ -a.xx.yy.xx.yy...] [-c.xx.xx.xx...] [ filename .. ]\n"));
	exit(1);
}

static void
process(FILE *f)
{
	int i, n;
	char mac[5];	/* The current macro or nroff command */
	int pl;

	stktop = -1;
	for (lineno = 1; fgets(line, sizeof (line), f); lineno++) {
		if (line[0] == '.') {
			/*
			 * find and isolate the macro/command name.
			 */
			(void) strncpy(mac, line+1, 4);
			if (isspace(mac[0])) {
				pe(lineno);
				(void) printf(gettext("Empty command\n"));
			} else if (isspace(mac[1])) {
				mac[1] = 0;
			} else if (isspace(mac[2])) {
				mac[2] = 0;
			} else if (mac[0] != '\\' || mac[1] != '\"') {
				pe(lineno);
				(void) printf(gettext("Command too long\n"));
			}

			/*
			 * Is it a known command?
			 */
			checkknown(mac);

			/*
			 * Should we add it?
			 */
			if (eq(mac, "de"))
				addcmd(line);

			chkcmd(line, mac);
		}

		/*
		 * At this point we process the line looking
		 * for \s and \f.
		 */
		for (i = 0; line[i]; i++)
			if (line[i] == '\\' && (i == 0 || line[i-1] != '\\')) {
				if (!sflag && line[++i] == 's') {
					pl = line[++i];
					if (isdigit(pl)) {
						n = pl - '0';
						pl = ' ';
					} else
						n = 0;
					while (isdigit(line[++i]))
						n = 10 * n + line[i] - '0';
					i--;
					if (n == 0) {
						if (stk[stktop].opno == SZ) {
							stktop--;
						} else {
							pe(lineno);
							(void) printf(
						gettext("unmatched \\s0\n"));
						}
					} else {
						growstk();
						stk[stktop].opno = SZ;
						stk[stktop].pl = pl;
						stk[stktop].parm = n;
						stk[stktop].lno = lineno;
					}
				} else if (!fflag && line[i] == 'f') {
					n = line[++i];
					if (n == 'P') {
						if (stk[stktop].opno == FT) {
							stktop--;
						} else {
							pe(lineno);
							(void) printf(
						gettext("unmatched \\fP\n"));
						}
					} else {
						growstk();
						stk[stktop].opno = FT;
						stk[stktop].pl = 1;
						stk[stktop].parm = n;
						stk[stktop].lno = lineno;
					}
				}
			}
	}
	/*
	 * We've hit the end and look at all this stuff that hasn't been
	 * matched yet!  Complain, complain.
	 */
	for (i = stktop; i >= 0; i--) {
		complain(i);
	}
}

static void
complain(int i)
{
	pe(stk[i].lno);
	(void) printf(gettext("Unmatched "));
	prop(i);
	(void) printf("\n");
}

static void
prop(int i)
{
	if (stk[i].pl == 0)
		(void) printf(".%s", br[stk[i].opno].opbr);
	else switch (stk[i].opno) {
	case SZ:
		(void) printf("\\s%c%d", stk[i].pl, stk[i].parm);
		break;
	case FT:
		(void) printf("\\f%c", stk[i].parm);
		break;
	default:
		(void) printf(gettext("Bug: stk[%d].opno = %d = .%s, .%s"),
			i, stk[i].opno, br[stk[i].opno].opbr,
			br[stk[i].opno].clbr);
	}
}

/* ARGSUSED */
static void
chkcmd(char *line, char *mac)
{
	int i;

	/*
	 * Check to see if it matches top of stack.
	 */
	if (stktop >= 0 && eq(mac, br[stk[stktop].opno].clbr))
		stktop--;	/* OK. Pop & forget */
	else {
		/* No. Maybe it's an opener */
		for (i = 0; br[i].opbr; i++) {
			if (eq(mac, br[i].opbr)) {
				/* Found. Push it. */
				growstk();
				stk[stktop].opno = i;
				stk[stktop].pl = 0;
				stk[stktop].parm = 0;
				stk[stktop].lno = lineno;
				break;
			}
			/*
			 * Maybe it's an unmatched closer.
			 * NOTE: this depends on the fact
			 * that none of the closers can be
			 * openers too.
			 */
			if (eq(mac, br[i].clbr)) {
				nomatch(mac);
				break;
			}
		}
	}
}

static void
nomatch(char *mac)
{
	int i, j;

	/*
	 * Look for a match further down on stack
	 * If we find one, it suggests that the stuff in
	 * between is supposed to match itself.
	 */
	for (j = stktop; j >= 0; j--)
		if (eq(mac, br[stk[j].opno].clbr)) {
			/* Found.  Make a good diagnostic. */
			if (j == stktop-2) {
				/*
				 * Check for special case \fx..\fR and don't
				 * complain.
				 */
				if (stk[j+1].opno == FT &&
				    stk[j+1].parm != 'R' &&
				    stk[j+2].opno == FT &&
				    stk[j+2].parm == 'R') {
					stktop = j -1;
					return;
				}
				/*
				 * We have two unmatched frobs.  Chances are
				 * they were intended to match, so we mention
				 * them together.
				 */
				pe(stk[j+1].lno);
				prop(j+1);
				(void) printf(gettext(" does not match %d: "),
					stk[j+2].lno);
				prop(j+2);
				(void) printf("\n");
			} else for (i = j+1; i <= stktop; i++) {
				complain(i);
			}
			stktop = j-1;
			return;
		}
	/* Didn't find one.  Throw this away. */
	pe(lineno);
	(void) printf(gettext("Unmatched .%s\n"), mac);
}

/* eq: are two strings equal? */
static int
eq(char *s1, char *s2)
{
	return (strcmp(s1, s2) == 0);
}

/* print the first part of an error message, given the line number */
static void
pe(int lineno)
{
	if (nfiles > 1)
		(void) printf("%s: ", cfilename);
	(void) printf("%d: ", lineno);
}

static void
checkknown(char *mac)
{

	if (eq(mac, "."))
		return;
	if (binsrch(mac) >= 0)
		return;
	if (mac[0] == '\\' && mac[1] == '"')	/* comments */
		return;

	pe(lineno);
	(void) printf(gettext("Unknown command: .%s\n"), mac);
}

/*
 * We have a .de xx line in "line".  Add xx to the list of known commands.
 */
static void
addcmd(char *line)
{
	char *mac;

	/* grab the macro being defined */
	mac = line+4;
	while (isspace(*mac))
		mac++;
	if (*mac == 0) {
		pe(lineno);
		(void) printf(gettext("illegal define: %s\n"), line);
		return;
	}
	mac[2] = 0;
	if (isspace(mac[1]) || mac[1] == '\\')
		mac[1] = 0;
	if (ncmds >= MAXCMDS) {
		(void) printf(gettext("Only %d known commands allowed\n"),
		    MAXCMDS);
		exit(1);
	}
	addmac(mac);
}

/*
 * Add mac to the list.  We should really have some kind of tree
 * structure here but this is a quick-and-dirty job and I just don't
 * have time to mess with it.  (I wonder if this will come back to haunt
 * me someday?)  Anyway, I claim that .de is fairly rare in user
 * nroff programs, and the loop below is pretty fast.
 */
static void
addmac(char *mac)
{
	char **src, **dest, **loc;

	if (binsrch(mac) >= 0) {	/* it's OK to redefine something */
#ifdef DEBUG
		(void) printf("binsrch(%s) -> already in table\n", mac);
#endif
		return;
	}
	/* binsrch sets slot as a side effect */
#ifdef DEBUG
printf("binsrch(%s) -> %d\n", mac, slot);
#endif
	loc = &knowncmds[slot];
	src = &knowncmds[ncmds-1];
	dest = src+1;
	while (dest > loc)
		*dest-- = *src--;
	*loc = malloc(3);
	(void) strcpy(*loc, mac);
	ncmds++;
#ifdef DEBUG
	(void) printf("after: %s %s %s %s %s, %d cmds\n",
	    knowncmds[slot-2], knowncmds[slot-1], knowncmds[slot],
	    knowncmds[slot+1], knowncmds[slot+2], ncmds);
#endif
}

/*
 * Do a binary search in knowncmds for mac.
 * If found, return the index.  If not, return -1.
 */
static int
binsrch(char *mac)
{
	char *p;	/* pointer to current cmd in list */
	int d;		/* difference if any */
	int mid;	/* mid point in binary search */
	int top, bot;	/* boundaries of bin search, inclusive */

	top = ncmds-1;
	bot = 0;
	while (top >= bot) {
		mid = (top+bot)/2;
		p = knowncmds[mid];
		d = p[0] - mac[0];
		if (d == 0)
			d = p[1] - mac[1];
		if (d == 0)
			return (mid);
		if (d < 0)
			bot = mid + 1;
		else
			top = mid - 1;
	}
	slot = bot;	/* place it would have gone */
	return (-1);
}
