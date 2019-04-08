CC=gcc
CFLAGS =-Wall -Wextra -Wpedantic -std=c99 -g
VFLAGS=--leak-check=full

BINARIES = ruterdrift

all: $(BINARIES)

ruterdrift: drift.h ruterdrift.c
	$(CC) $(CFLAGS) ruterdrift.c -o ruterdrift

clean:
	$(RM) $(BINARIES)
