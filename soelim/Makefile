PROG =		soelim

all:		$(PROG)

install:	all
		[ -d ${BINDIR} ] || mkdir -p ${BINDIR}
		install ${PROG} ${BINDIR}/

clean:
		rm -f ${PROG}
