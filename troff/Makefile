SUBDIRS = nroff.d troff.d

all install clean:
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
