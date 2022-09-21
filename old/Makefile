# Description: Makefile for RedBlackTree
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

EXE = main.x

all: $(EXE)

.PHONY: all

main.x: main.o RedBlackTree.o
	g++ main.o RedBlackTree.o -o main.x

main.o: main.cpp RedBlackTree.h
	g++ -c main.cpp RedBlackTree.cpp $(CXXFLAGS)

RedBlackTree.o : RedBlackTree.cpp RedBlackTree.h
	g++ -c RedBlackTree.cpp -o RedBlackTree.o $(CXXFLAGS)

clean:
	rm -f *.o
	rm -f $(EXE) *~



.PHONY: clean

