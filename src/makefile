PROG = steganography.app
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11 -g
OBJS = main.o ppm.o bmp.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm

ppm.o: ppm.c
	$(CC) $(CFLAGS) -c ppm.c
ppm.o: bmp.c
	$(CC) $(CFLAGS) -c bmp.c
main.o: main.c ppm.h bmp.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f core $(PROG) $(OBJS)
