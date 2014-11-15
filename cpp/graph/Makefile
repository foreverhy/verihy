
LINKFLAGS = -L$(LINK_DIR) -lgraph
CXX = clang++
CXXFLAGS += -g -Wall -Wextra -std=c++0x 

LINK_DIR = ../../lib



test:libgraph.so test.o
	$(CXX) test.o $(LINKFLAGS) -o test


test.o:test.cpp graph.h
	$(CXX) $(CXXFLAGS) -c test.cpp

libgraph.so:graph.h graph.cpp graph_search.h graph_search.cpp
	$(CXX) $(CXXFLAGS) -fPIC --shared graph.cpp graph_search.cpp -o $(LINK_DIR)/libgraph.so

.PHONY:clean

clean :
	rm -f test *.o $(LINK_DIR)/libgraph.so $(LINK_DIR)/libgraph.a
