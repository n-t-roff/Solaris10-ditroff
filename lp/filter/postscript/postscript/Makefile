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
# Copyright 1989-2002 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# cmd/lp/filter/postscript/postscript/Makefile
#

TXTFILES =	README

FILES =				\
		aps.ps		\
		banner.ps	\
		baseline.ps	\
		color.ps	\
		dpost.ps	\
		draw.ps		\
		fatcourier.ps	\
		forms.ps	\
		postdaisy.ps	\
		postdmd.ps	\
		postmd.ps	\
		postplot.ps	\
		postprint.ps	\
		posttek.ps	\
		ps.requests

all:		$(TXTFILES) $(FILES)

install:	all
		@[ -d ${PSDIR} ] || mkdir -p ${PSDIR}
		for i in ${FILES}; do \
			install -m 644 $$i ${PSDIR}/; \
		done

uninstall:
		for i in ${FILES}; do \
			rm -f ${PSDIR}/$$i; \
		done
		@rmdir ${PSDIR} 2> /dev/null || true

clean:
