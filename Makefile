CC=clang
CFLAGS=
all: parse

parse: parse.c parse.h
	$(CC) $(CFLAGS) parse.c -o parse
