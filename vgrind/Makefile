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
# Copyright 1990-2002 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# cmd/vgrind/Makefile

#
# These are the objects associated with the overall vgrind command.
#
VFONTEDPR =	vfontedpr
RETEST = 	retest
MACROS =	tmac.vgrind
LANGDEFS =	vgrindefs
KSHPROG =	vgrind

#
# These macros captures objects that ultimately will be installed in
# (respectively) /usr/bin, /usr/lib, and /usr/share/lib.
#
# Note also that retest is used strictly as a test program and is never
# installed.  We omit it here, so that the NSE doesn't spend cycles
# on it when acquiring and reconciling.
#
PROG = 		$(KSHPROG)
LIBPROG = 	$(VFONTEDPR) $(LANGDEFS)
TMACPROG =	$(MACROS)

VFONTEDPROBJS =	vfontedpr.o vgrindefs.o regexp.o
RETESTOBJS =	retest.o regexp.o

RETESTSRC =	$(RETESTOBJS:%.o=%.c)

OBJS =		$(VFONTEDPROBJS) $(RETESTOBJS)
SRCS =		$(OBJS:%.o=%.c)

CPPFLAGS =	-DLIBDIR='"${LIBDIR}"'
#
# retest appears here only in source form; see comment above for PROG.
#
all:		$(PROG) $(LIBPROG) $(TMACPROG) $(RETEST)

#
# We add all as a dependent to make sure that the install pattern
# matching rules see everything they should.  (This is a safety net.)
#
# XXX:	ROOTTMAC shouldn't appear as a dependent; it's here as a
# 	bandaid(TM) until /usr/lib/tmac becomes a symlink to
#	/usr/share/lib/tmac.
#
install:	all
		@[ -d ${LIBDIR} ] || mkdir -p ${LIBDIR}
		install ${VFONTEDPR} ${LIBDIR}/
		install -m 644 ${LANGDEFS} ${LIBDIR}/
		@[ -d ${BINDIR} ] || mkdir -p ${BINDIR}
		install ${PROG} ${BINDIR}/
		@[ -d ${TMACDIR} ] || mkdir -p ${TMACDIR}
		install -m 644 ${MACROS} ${TMACDIR}/

uninstall:
		rm -f ${LIBDIR}/${VFONTEDPR}
		rm -f ${LIBDIR}/${LANGDEFS}
		rm -f ${BINDIR}/${PROG}
		rm -f ${TMACDIR}/${MACROS}
		@rmdir ${BINDIR} 2> /dev/null || true
		@rmdir ${TMACDIR} 2> /dev/null || true
		@rmdir ${LIBDIR} 2> /dev/null || true

clean:
		rm -f $(OBJS) ${PROG} ${VFONTEDPR} ${LANGDEFS} $(RETEST)

vgrind:
		sed 's"/usr/lib/vfontedpr"${LIBDIR}/${VFONTEDPR}"; s"/usr/share/lib/tmac"${TMACDIR}"' < $@.ksh > $@
		chmod a+x $@

${VFONTEDPR}:	${VFONTEDPROBJS}
		${CC} -o $@ ${VFONTEDPROBJS}

${RETEST}:	${RETESTOBJS}
		${CC} -o $@ ${RETESTOBJS}

${LANGDEFS}:
		cp ${LANGDEFS}.src ${LANGDEFS}
