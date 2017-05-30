CC=clang
CFLAGS=
all: parse.o main

main: parse.o
	$(CC) $(CFLAGS) -o main main.c parse.o
parse.o: parse.c 
	$(CC) $(CFLAGS) -c parse.c 

clean:
	rm parse.o
	rm main
