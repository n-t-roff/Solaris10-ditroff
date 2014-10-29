MKOUT =	col.mk

all: $(MKOUT)
	$(MAKE) -f $(MKOUT) $@

.DEFAULT: $(MKOUT)
	$(MAKE) -f $(MKOUT) $@

clean:
	@if [ -e $(MKOUT) ]; then \
		$(MAKE) -f $(MKOUT) $@; \
	else \
		true; \
	fi
	rm -f $(MKOUT)

$(MKOUT): bsd.mk gnu.mk common.mk
	@if [ "`uname`" = "Linux" ]; then \
		cat gnu.mk common.mk >$@; \
	else \
		cat bsd.mk common.mk >$@; \
	fi
