CC = gcc
CFLAGS = -Wall

SH = pshell
SIG=sighandlers
BI=builtins

all: options ${SH}
	${CC} ${CFLAGS} *.o -o ${SH}

$(SH): ${SH}.c ${BI} ${SIG}
	${CC} ${CFLAGS} -c ${SH}.c

$(BI): ${BI}.h ${BI}.c
	${CC} ${CFLAGS} -c ${BI}.c

$(SIG): ${SIG}.h ${SIG}.c
	${CC} ${CFLAGS} -c ${SIG}.c

options:
	@echo "Compiling ${SH}"
	@echo ""
	@echo "Build options:"
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CC       = ${CC}"
	@echo ""

clean:
	rm -f *.o ${SH}
