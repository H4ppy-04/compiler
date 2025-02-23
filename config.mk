# compiler version
VERSION = 1.0

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wno-deprecated-declarations -Os -g

CC = cc

CHKFLAGS = -checks -limit 1

TEST=test.c cutest.c compiler.c parser.c
