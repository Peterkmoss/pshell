CC = gcc
CFLAGS = -Wall

all: options mysh
	${CC} ${CFLAGS} *.o -o mysh

mysh: mysh.c builtins
	${CC} ${CFLAGS} -c mysh.c

builtins: builtins.h builtins.c
	${CC} ${CFLAGS} -c builtins.c

options:
	@echo "Compiling mysh"
	@echo ""
	@echo "Build options:"
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CC       = ${CC}"
	@echo ""

clean:
	rm -f *.o
