FILES =		eqnchar iso ascii greek

all:		$(FILES) 

install:	all
		@[ -d $(PUBDIR) ] || mkdir -p $(PUBDIR)
		for i in $(FILES); do \
			install -m 644 $$i $(PUBDIR)/; \
		done

uninstall:
		for i in $(FILES); do \
			rm -f $(PUBDIR)/$$i; \
		done
		@rmdir $(PUBDIR) 2> /dev/null || true

clean:
