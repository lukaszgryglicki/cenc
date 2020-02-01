all: cenc
cenc: cenc.c
	cc -ansi -pedantic -pedantic-errors -Wall -Wextra -static -o cenc cenc.c
	strip cenc
