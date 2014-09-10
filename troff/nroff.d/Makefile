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
# cmd/troff/nroff.d/Makefile
#

SUBDIRS =	terms.d

PROG =		nroff

OBJS =		n10.o n6.o

COMMONOBJS =	hytab.o n1.o n2.o n3.o n4.o n5.o \
		n7.o n8.o n9.o ni.o nii.o suftab.o

SRCS =		$(OBJS:%.o=%.c) $(COMMONOBJS:%.o=../%.c)

CPPFLAGS =	${OPENSOLARIS} \
		-DTMACDIR="\"${TMACDIR}\"" \
		-DNTERMDIR="\"${NTERMDIR}\"" \
		-DTEMPDIR="\"${TEMPDIR}\"" \
		-DNROFF -DUSG -DINCORE -DEUC -I. -I..

all:		$(PROG)
		@for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done

install:	$(PROG)
		@LIBDIR='$(LIBDIR)'; export LIBDIR; \
		NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
		for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done
		[ -d $(BINDIR) ] || mkdir -p $(BINDIR) || exit
		install $(PROG) $(BINDIR)/ || exit

clean:
		@for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done
		rm -f $(OBJS) $(COMMONOBJS) $(PROG)

$(PROG):	$(OBJS) $(COMMONOBJS)
		$(LINK.c) -o $@ $(OBJS) $(COMMONOBJS) $(LDLIBS)

%.o: ../%.c
		$(COMPILE.c) $<

hytab.o: ../hytab.c
n1.o: ../n1.c ../tdef.h ../ext.h tw.h
n2.o: ../n2.c ../tdef.h ../ext.h tw.h
n3.o: ../n3.c ../tdef.h ../ext.h tw.h
n4.o: ../n4.c ../tdef.h ../ext.h tw.h
n5.o: ../n5.c ../tdef.h ../ext.h
n7.o: ../n7.c ../tdef.h ../ext.h tw.h
n8.o: ../n8.c ../tdef.h ../ext.h
n9.o: ../n9.c ../tdef.h ../ext.h tw.h
ni.o: ../ni.c ../tdef.h
nii.o: ../nii.c ../tdef.h ../ext.h tw.h
suftab.o: ../suftab.c
