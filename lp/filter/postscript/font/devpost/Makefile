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
# cmd/lp/filter/postscript/font/devpost/Makefile
#

FONTFILES =		AB AI AR AX BI CB CI CO	\
			CW CX GR HB HI HX Hb Hi	\
			Hr Hx KB KI KR KX NB NI	\
			NR NX PA PB PI PX S1 VB	\
			VI VR VX ZD ZI B  H  I	\
			R  S	
FONTLNK1 =		G HM HK HL
FONTLNK2 =		GI
DESCFILE =		DESC
TXTS =			DESC.big DESC.small S.big S.small LINKFILE

FONTNAMES =		$(FONTFILES:%=%.name)
FONTLNK1OUTS =		$(FONTLNK1:%=%.out)
FONTLNK2OUTS =		$(FONTLNK2:%=%.out)
FONTOUTS =		$(FONTFILES:%=%.out)
FONTS =			$(FONTOUTS:%.out=%)

SUBDIRS =		charlib

NATIVEMAKEDEV =		../makedev

ROOTDEVPOST =		$(FONTDIR)/devpost

all :			$(TXTS) $(FONTOUTS) $(FONTNAMES) ${FONTLNK1OUTS} \
			${FONTLNK2OUTS}
			@NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
			TMACDIR='$(TMACDIR)'; export TMACDIR; \
			FONTDIR='$(FONTDIR)'; export FONTDIR; \
			TEMPDIR='$(TEMPDIR)'; export TEMPDIR; \
			for dir in $(SUBDIRS); do \
				echo "Entering \"$$PWD/$$dir/\""; \
				(cd "$$dir" && make $@) || exit; \
				echo "Leaveing \"$$PWD/$$dir/\""; \
			done

install:		$(TXTS) $(FONTOUTS) $(FONTNAMES)
			@[ -d $(ROOTDEVPOST) ] || mkdir -p $(ROOTDEVPOST)
			for i in $(FONTFILES) $(FONTNAMES) ${FONTOUTS}; do \
				install -m 644 $$i $(ROOTDEVPOST)/; \
			done
			install -m 644 ${DESCFILE}.out $(ROOTDEVPOST)/
			install -m 644 ${DESCFILE} $(ROOTDEVPOST)/;
			@LIBDIR='$(LIBDIR)'; export LIBDIR; \
			NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
			TMACDIR='$(TMACDIR)'; export TMACDIR; \
			FONTDIR='$(FONTDIR)'; export FONTDIR; \
			for dir in $(SUBDIRS); do \
				echo "Entering \"$$PWD/$$dir/\""; \
				(cd "$$dir" && make $@) || exit; \
				echo "Leaveing \"$$PWD/$$dir/\""; \
			done

uninstall:
			@LIBDIR='$(LIBDIR)'; export LIBDIR; \
			NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
			TMACDIR='$(TMACDIR)'; export TMACDIR; \
			FONTDIR='$(FONTDIR)'; export FONTDIR; \
			for dir in $(SUBDIRS); do \
				echo "Entering \"$$PWD/$$dir/\""; \
				(cd "$$dir" && make $@) || exit; \
				echo "Leaveing \"$$PWD/$$dir/\""; \
			done
			for i in $(FONTFILES) $(FONTNAMES) ${FONTOUTS}; do \
				rm -f $(ROOTDEVPOST)/$$i; \
			done
			rm -f $(ROOTDEVPOST)/${DESCFILE}.out
			rm -f $(ROOTDEVPOST)/${DESCFILE};
			@rmdir $(ROOTDEVPOST) 2> /dev/bull || true
			@rmdir $(FONTDIR) 2> /dev/bull || true

clean:
			rm -f $(FONTOUTS) $(FONTLNK1OUTS) $(FONTLNK2OUTS) \
			    ${DESCFILE}.out
			@for dir in $(SUBDIRS); do \
				echo "Entering \"$$PWD/$$dir/\""; \
				(cd "$$dir" && make $@) || exit; \
				echo "Leaveing \"$$PWD/$$dir/\""; \
			done

$(FONTOUTS):		${FONTS} $(NATIVEMAKEDEV)
			rm -f $@ ${DESCFILE}.out
			$(NATIVEMAKEDEV) ${FONTS}
			$(NATIVEMAKEDEV) ${DESCFILE}

$(FONTLNK1OUTS):	H.out
			rm -f $@; ln -s H.out $@

$(FONTLNK2OUTS):	HI.out
			rm -f $@; ln -s HI.out $@
