cc = gcc
CCFLAGS = -Wall

all: malloc
	gcc -o mymalloc malloc.o memgrind.c
malloc: mymalloc.c mymalloc.h
	gcc -c -o malloc.o mymalloc.c
clean:
	rm -f mymalloc malloc.o memgrind.o

