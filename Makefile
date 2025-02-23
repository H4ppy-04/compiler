# See LICENSE file for copyright and license details

include config.mk

SRC = main.c compiler.c parser.c
INC = compiler.h cutest.h parser.h

all: build

build:
	${CC} ${CFLAGS} ${SRC} -o compiler.out

clean:
	rm -f compiler compiler-${VERSION}.tar.gz *.out

dist: clean
	mkdir -p compiler-${VERSION}
	cp -R LICENSE Makefile README ${SRC} compiler-${VERSION}
	tar -cf compiler-${VERSION}.tar
	rm -rf compiler-${VERSION}

check:
	splint ${CHKFLAGS} ${SRC}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f compiler ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/compiler

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/compiler

fmt:
	clang-format --fail-on-incomplete-format --verbose -i ${SRC} ${TEST} ${INC}

test:
	${CC} ${TEST} -o runner.out
	./runner.out


.PHONY: all clean dist install uninstall fmt check
