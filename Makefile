# Description: Makefile for RedBlackTree
CXX = g++
CXXFLAGS = -W -Wall -Wextra -std=c++14

EXE = RBTree.x

all: $(EXE)

.PHONY: all

RBTree.x: 
	$(CXX) RBTree.cpp -o main.x $(CXXFLAGS)

clean:
	rm -f $(EXE) *~

.PHONY: clean