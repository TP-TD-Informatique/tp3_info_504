CC=gcc
CFLAGS=-g -Wall -pedantic -std=c99

all: tetris.o

tetris.o: tetris.h tetris.c
	$(CC) -c $(CFLAGS) tetris.c