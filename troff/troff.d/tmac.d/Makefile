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
# cmd/troff/troff.d/tmac.d/Makefile
#

FILES =		acm.me ansun.tbl \
		chars.me deltext.me eqn.me  \
		float.me footnote.me index.me local.me \
		mmn mmt ms.acc ms.cov ms.eqn ms.ref ms.tbl \
		ms.ths ms.toc null.me refer.me sh.me \
		tbl.me thesis.me tz.map v vgrind

SEDFILES =	an ansun bib e m s

all:

install:	$(FILES) ${SEDFILES}
		@[ -d ${TMACDIR} ] || mkdir -p ${TMACDIR}
		for f in ${FILES}; do \
			install -m 644 $$f ${TMACDIR}/; \
		done
		for file in ${SEDFILES}; do \
			sed "s'/usr/share/lib/tmac'${TMACDIR}'" $$file > \
			    ${TMACDIR}/$$file; \
		done

uninstall:
		for f in ${FILES}; do \
			rm -f ${TMACDIR}/$$f; \
		done
		for file in ${SEDFILES}; do \
			rm -f ${TMACDIR}/$$file; \
		done
		@rmdir ${TMACDIR} 2>/dev/null || true

clean:
