# Name: Sally Chung
# Project: Lab 4: Rice, rice, and rice.

EXECUTABLES=dining-p
SRC=dining-p.c
OBJ=dining-p.o

CC=gcc
CFLAGS=-g

all: $(EXECUTABLES)

	$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

catcher: catcher.c
	gcc -g -c dining-p.c
	gcc -g -o $@ dining-p.o

clean:
	rm -f $(EXECUTABLES) $(OBJ) 