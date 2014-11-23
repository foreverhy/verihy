
LINKFLAGS = -L$(LINK_DIR) -lgraph
CXX = clang++
CXXFLAGS += -g -Wall -Wextra -std=c++0x 

LINK_DIR = ../../lib



test:libdigraph.so test.o
	$(CXX) test.o $(LINKFLAGS) -o test


test.o:test.cpp digraph.h
	$(CXX) $(CXXFLAGS) -c test.cpp

libdigraph.so:digraph.h digraph.cpp 
	$(CXX) $(CXXFLAGS) -fPIC --shared digraph.cpp  -o $(LINK_DIR)/libdigraph.so

.PHONY:clean

clean :
	rm -f test *.o $(LINK_DIR)/libdigraph.so $(LINK_DIR)/libdigraph.a
