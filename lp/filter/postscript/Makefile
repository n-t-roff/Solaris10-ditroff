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
# cmd/lp/filter/postscript/Makefile
#

SUBDIRS =	common		\
		dpost		\
		font		\
		postscript
#		postreverse	\
#		postio		\
#		postprint	\
#		posttek		\
#		postdmd		\
#		postdaisy	\
#		postmd		\
#		postplot	\
#		postcomm	\
#		picpack		\
#		download	\
#		filtdesc

TXTS =		README

all:		$(TXTS)
		@NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
		TMACDIR='$(TMACDIR)'; export TMACDIR; \
		FONTDIR='$(FONTDIR)'; export FONTDIR; \
		TEMPDIR='$(TEMPDIR)'; export TEMPDIR; \
		PSDIR='$(PSDIR)'; export PSDIR; \
		for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done

install:
		@BINDIR='$(BINDIR)'; export BINDIR; \
		LIBDIR='$(LIBDIR)'; export LIBDIR; \
		NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
		TMACDIR='$(TMACDIR)'; export TMACDIR; \
		FONTDIR='$(FONTDIR)'; export FONTDIR; \
		PSDIR='$(PSDIR)'; export PSDIR; \
		for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done

clean:
		@for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done
