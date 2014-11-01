
LINKFLAGS = -L$(LINK_DIR) -ltrie_tree
CXX = clang++
CXXFLAGS += -g -Wall -Wextra -std=c++0x 
GRAPHS = test

LINK_DIR = ../../lib

all : $(GRAPHS)

clean :
	rm -f $(GRAPHs) *.o $(LINK_DIR)/libgraph.so $(LINK_DIR)/libgraph.a

test:libgraph.so test.o
	$(CXX) test.o -L$(LINK_DIR) -lgraph -o test


test.o:test.cpp base_graph.h
	$(CXX) $(CXXFLAGS) -c test.cpp

libgraph.so:*.h *.cpp
	$(CXX) $(CXXFLAGS) -fPIC --shared *.cpp -o $(LINK_DIR)/libgraph.so
