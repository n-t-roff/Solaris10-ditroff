#
# ident	"%Z%%M%	%I%	%E% SMI"
#
# Copyright (c) 1994 by Sun Microsystems, Inc.
# All rights reserved.
#
# cmd/eqn/eqn.d/Makefile
#

PROG =		eqn

CSRCS =		diacrit.c eqnbox.c font.c fromto.c funny.c	\
		glob.c integral.c io.c lex.c lookup.c		\
		mark.c matrix.c move.c over.c paren.c		\
		pile.c shift.c size.c sqrt.c text.c

SRCS =		$(CSRCS:%=../%)

YACCSRC =	e.y

COBJS =		$(CSRCS:%.c=%.o)
OBJS =		y.tab.o $(COBJS)

YFLAGS =	-d
#CFLAGS =	-g
CPPFLAGS =	${OPENSOLARIS} -I. -I..

all:		$(PROG) 

$(PROG):	$(OBJS)
		$(LINK.c) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

y.tab.c: ../$(YACCSRC)
		$(YACC.y) ../$(YACCSRC)
		sed -f ../yyval.sed < y.tab.c > sed.y.tab.c
		mv y.tab.c orig.y.tab.c
		mv sed.y.tab.c y.tab.c

$(COBJS):	$(SRCS)
		$(COMPILE.c) ../$(@:%.o=%.c)

install:	all
		[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
		install $(PROG) $(BINDIR)/

clean:
		rm -f $(OBJS) *y.tab.* $(PROG)

