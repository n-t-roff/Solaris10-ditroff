PROG =		diffmk

all:		$(PROG)

install:	all
		@[ -d ${BINDIR} ] || mkdir -p ${BINDIR}
		install ${PROG} ${BINDIR}/

uninstall:
		rm -f ${BINDIR}/${PROG}
		@rmdir ${BINDIR} 2> /dev/null || true

clean:
		rm -f ${PROG}
