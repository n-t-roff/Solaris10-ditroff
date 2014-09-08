#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License, Version 1.0 only
# (the "License").  You may not use this file except in compliance
# with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#
# ident	"%Z%%M%	%I%	%E% SMI"
#
# Copyright (c) 1989 by Sun Microsystems, Inc.
#
# cmd/troff/troff.d/devaps/Makefile
#

LN =		ln -s
PROG =		daps

MAKEDEV =	./makedev

DAPSSRCS =	daps.c build.c
SRCS=		$(DAPSSRCS)

OBJS =		$(SRCS:%.c=%.o)

COMMONOBJS =	../draw.o
COMMONSRCS =	$(COMMONOBJS:%.o=%.c)

F1 =		B I R S CT CW CX GB GI GR GS	\
		HI HK HX PO PX S1 SC SM TX
F2 =		DESC C G H BI CE CI HB HL MB MI MR MX PA PB PI TB
F3 =		HM
OTHERFILES =	version
TXTS =		README LINKFILE

OUTF1 =		$(F1:%=%.out)
OUTF2 =		$(F2:%=%.out)
OUTF3 =		$(F3:%=%.out)
OUTFILES =	$(OUTF1) $(OUTF2) $(OUTF3)
OUTF12 =	$(OUTF1) $(OUTF2)
OUTSRC12 =	$(OUTF12:%.out=%)

ADDFILES =	$(F1:%=%.add)

ROOTDEVAPS =	$(FONTDIR)/devaps

# Don"t re-install /usr/lib/font, Targetdirs installs it
#ROOTDIRS =	$(FONTDIR) $(ROOTDEVAPS)
ROOTDIRS =	$(ROOTDEVAPS)

ROOTFILES =	$(OUTFILES:%=$(ROOTDEVAPS)/%) 	\
		$(ADDFILES:%=$(ROOTDEVAPS)/%)	\
		$(OTHERFILES:%=$(ROOTDEVAPS)/%)

FILEMODE =	644

CPPFLAGS =	-I. -I..

POBJS =		$(COMMONOBJS) $(DAPSSRCS:%.c=%.o)

all :		$(TXTS) $(OTHERFILES) $(PROG) $(MAKEDEV) $(OUTFILES) $(ADDFILES)

$(PROG) :	$(POBJS)
		$(LINK.c) -o $@ $(POBJS) $(LDLIBS) -lm

$(MAKEDEV):	$(MAKEDEV).c
		$(CC) -O $(CPPFLAGS) -o $@ $@.c

$(COMMONOBJS) :	$(COMMONSRCS)
		cd $(@D); $(MAKE) $(@F)

$(OUTF1) \
$(OUTF2) :	$(OUTSRC12) $(MAKEDEV)
		$(MAKEDEV) $(OUTSRC12)

# ADDFILES are built indirectly from building OUTF1, but they must
# appear as a target to the NSE
#
$(ADDFILES) :	$(OUTF1)
		@:

$(OUTF3) :	HB.out
		rm -f $@; $(LN) HB.out $@

#install:	all $(ROOTDIRS) $(ROOTPROG) $(ROOTFILES)
install:

$(ROOTDIRS):
		$(INS.dir)

$(ROOTDEVAPS)/%:	% $(ROOTDIRS)
		$(INS.file)

clean:
		rm -f $(OBJS) $(ADDFILES) $(OUTFILES) $(PROG) $(MAKEDEV)
