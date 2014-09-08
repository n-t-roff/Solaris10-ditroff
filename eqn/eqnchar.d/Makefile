FILES =		eqnchar iso ascii greek

all:		$(FILES) 

install:	all
		[ -d $(PUBDIR) ] || mkdir -p $(PUBDIR)
		for i in $(FILES); do \
			install -m 644 $$i $(PUBDIR)/; \
		done

clean:
