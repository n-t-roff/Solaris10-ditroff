TEMPDIR =	/var/tmp
ROOTDIR =	/usr/local/sunroff
BINDIR =	$(ROOTDIR)/bin
LIBDIR =	$(ROOTDIR)/lib
PUBDIR =	$(ROOTDIR)/pub
TMACDIR =	$(LIBDIR)/tmac
NTERMDIR =	$(LIBDIR)/nterm
FONTDIR =	$(LIBDIR)/font
PSDIR =		$(LIBDIR)/postscript

SUBDIRS =	troff lp/filter/postscript eqn tbl col soelim refer diffmk \
		deroff vgrind

all install clean:
		@TEMPDIR='$(TEMPDIR)'; export TEMPDIR; \
		BINDIR='$(BINDIR)'; export BINDIR; \
		LIBDIR='$(LIBDIR)'; export LIBDIR; \
		PUBDIR='$(PUBDIR)'; export PUBDIR; \
		TMACDIR='$(TMACDIR)'; export TMACDIR; \
		NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
		FONTDIR='$(FONTDIR)'; export FONTDIR; \
		PSDIR='$(PSDIR)'; export PSDIR; \
		for dir in $(SUBDIRS); do \
			echo "Entering \"$$PWD/$$dir/\""; \
			(cd "$$dir" && make $@) || exit; \
			echo "Leaveing \"$$PWD/$$dir/\""; \
		done
