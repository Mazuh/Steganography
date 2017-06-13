PROG = steganography.app
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11 -g
OBJS = main.o pixel.o ppm.o bmp.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm

pixel.o: pixel.c
	$(CC) $(CFLAGS) -c pixel.c
ppm.o: ppm.c
	$(CC) $(CFLAGS) -c ppm.c
bmp.o: bmp.c
	$(CC) $(CFLAGS) -c bmp.c
main.o: main.c pixel.h ppm.h bmp.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f core $(PROG) $(OBJS)
