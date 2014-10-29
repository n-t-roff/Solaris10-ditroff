PROG =		col

all:		$(PROG)

install:	all
		@[ -d ${BINDIR} ] || mkdir -p ${BINDIR}
		install ${PROG} ${BINDIR}/

clean:
		rm -f ${PROG}

uninstall:
		rm -f ${BINDIR}/${PROG}
		@rmdir ${BINDIR} 2> /dev/null || true

${PROG}:	${SRC}
		${CC} -o $@ ${SRC}
