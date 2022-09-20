# Description: Makefile for RedBlackTree
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

EXE = main.x

all: $(EXE)

.PHONY: all

main.x: main.o RedBlackTree.o RedBlackTree_iterator.o
	g++ main.o RedBlackTree.o -o main.x

main.o: main.cpp RedBlackTree.h
	g++ -c main.cpp -o main.o $(CXXFLAGS)

RedBlackTree.o : RedBlackTree.cpp RedBlackTree.h
	g++ -c RedBlackTree.cpp -o RedBlackTree.o $(CXXFLAGS)

RedBlackTree_iterator.o: RedBlackTree.cpp RedBlackTree.h
	g++ -c RedBlackTree_iterator.cpp -o RedBlackTree_iterator.o $(CXXFLAGS)

clean:
	rm -f $(EXE) *~

.PHONY: clean

