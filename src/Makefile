SRC = RedBlackTree.cpp            \
      RedBlackTree_iterator.cpp  

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

OBJ = $(SRC:.cpp=.o)

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(OBJ)

.PHONY: all

%.o: %.cpp 
	$(CXX) $< -c $(CXXFLAGS)

clean:
	rm -f $(OBJ) *~

.PHONY: clean

01_auto.x : CXXFLAGS+=-Wno-unused-variable
