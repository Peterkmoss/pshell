CC = gcc
CFLAGS = -Wall

SHELLNAME = pshell

all: options ${SHELLNAME}
	${CC} ${CFLAGS} *.o -o ${SHELLNAME}

$(SHELLNAME): ${SHELLNAME}.c builtins
	${CC} ${CFLAGS} -c ${SHELLNAME}.c

builtins: builtins.h builtins.c
	${CC} ${CFLAGS} -c builtins.c

options:
	@echo "Compiling ${SHELLNAME}"
	@echo ""
	@echo "Build options:"
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CC       = ${CC}"
	@echo ""

clean:
	rm -f *.o ${SHELLNAME}
