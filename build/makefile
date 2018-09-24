#Compiler
CC = g++

#Compiler flags
CFLAGS = -Wall -g -std=c++11

# Include directory
IDIR = -I../include/

TEST = main

MAIN = main 
AVL = avl_tree
UNIT = unittest

MAINDIR = ../src/

TESTDIR = ../test/

	
all: $(AVL) $(MAIN)
	$(CC) $(CFLAGS) $(IDIR) -o run.out $(AVL).o $(MAIN).o

$(AVL): 
	$(CC) $(CFLAGS) $(IDIR) -c $(MAINDIR)$cpp

$(MAIN):
	$(CC) $(CFLAGS) $(IDIR) -c $(MAINDIR)$cpp

unittest: $(AVL) $(UNIT)
	$(CC) $(CFLAGS) $(IDIR) -o run_unittes.out $(AVL).o $(UNIT).o

$(UNIT):
	$(CC) $(CFLAGS) $(IDIR) -c $(TESTDIR)$cpp
clean:
	rm $(MAIN).o $(TEST).o $(UNIT).o run.out run_unittes