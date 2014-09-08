SUBDIRS = nroff.d troff.d

all:
	@NTERMDIR='$(NTERMDIR)'; export NTERMDIR; \
	TMACDIR='$(TMACDIR)'; export TMACDIR; \
	FONTDIR='$(FONTDIR)'; export FONTDIR; \
	TEMPDIR='$(TEMPDIR)'; export TEMPDIR; \
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
