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
# Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# ident	"%Z%%M%	%I%	%E% SMI"
#
# Makefile for cmd/refer
#

PROG =		refer addbib lookbib sortbib \
		roffbib indxbib \
		mkey inv hunt

MKEY_OBJS =	mkey1.o mkey2.o mkey3.o deliv2.o
INV_OBJS =	inv1.o inv2.o inv3.o inv5.o inv6.o deliv2.o
HUNT_OBJS =	hunt1.o hunt2.o hunt3.o hunt5.o hunt6.o		\
		hunt7.o glue5.o refer3.o hunt9.o shell.o	\
		deliv2.o hunt8.o glue4.o tick.o
REFER_OBJS =	glue1.o refer1.o refer2.o refer4.o refer5.o	\
		refer6.o mkey3.o refer7.o refer8.o hunt2.o	\
		hunt3.o deliv2.o hunt5.o hunt6.o hunt8.o	\
		glue3.o hunt7.o hunt9.o glue2.o glue4.o		\
		glue5.o refer0.o shell.o
ADDBIB_OBJS =	addbib.o
LOOKBIB_OBJS =	lookbib.o
SORTBIB_OBJS =	sortbib.o

OTXTS =		tmac.bib

REFDIR =	$(ROOTLIB)/refer

SUBDIRS =	papers

CPPFLAGS =	-DTEMPDIR='"${TEMPDIR}"'

all:		${PROG}

install:	all
		@[ -d ${BINDIR} ] || mkdir -p ${BINDIR}
		for i in ${PROG}; do \
			install $$i ${BINDIR}/; \
		done

clean:
		rm -f ${MKEY_OBJS} ${INV_OBJS} ${HUNT_OBJS} ${REFER_OBJS} \
		    ${ADDBIB_OBJS} ${LOOKBIB_OBJS} ${SORTBIB_OBJS} ${PROG}

uninstall:
		for i in ${PROG}; do \
			rm -f ${BINDIR}/$$i; \
		done
		@rmdir ${BINDIR} 2> /dev/null || true

refer:		${REFER_OBJS}
		${CC} -o $@ ${REFER_OBJS}

addbib:		${ADDBIB_OBJS}
		${CC} -o $@ ${ADDBIB_OBJS}

lookbib:	${LOOKBIB_OBJS}
		${CC} -o $@ ${LOOKBIB_OBJS}

sortbib:	${SORTBIB_OBJS}
		${CC} -o $@ ${SORTBIB_OBJS}

mkey:		${MKEY_OBJS}
		${CC} -o $@ ${MKEY_OBJS}

inv:		${INV_OBJS}
		${CC} -o $@ ${INV_OBJS}

hunt:		${HUNT_OBJS}
		${CC} -o $@ ${HUNT_OBJS}

