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

all install clean uninstall:
		@TEMPDIR='$(TEMPDIR)'; export TEMPDIR; \
		BINDIR='$(BINDIR)'; export BINDIR; \
		LIBDIR='$(LIBDIR)'; export LIBDIR; \
		PUBDIR='$(PUBDIR)'; export PUBDIR; \
		TMACDIR='$(TMACDIR)'; export TMACDIR; \
		NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
		FONTDIR='$(FONTDIR)'; export FONTDIR; \
		PSDIR='$(PSDIR)'; export PSDIR; \
		OPENSOLARIS='$(OPENSOLARIS)'; export OPENSOLARIS; \
		for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done
