PROG = steganography.app
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11 -g
OBJS = main.o ppm.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm

ppm.o: ppm.c
	$(CC) $(CFLAGS) -c ppm.c
main.o: main.c ppm.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f core $(PROG) $(OBJS)
