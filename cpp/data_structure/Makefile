CPPFLAGS = -std=c++0x -g
CXX = clang++
main:main.o data_structure.o
	$(CXX) -o main main.o ${CPPFLAGS}

main.o:main.cpp data_structure.cpp
	$(CXX) -c main.cpp ${CPPFLAGS}

data_structure.o: data_structure.cpp
	$(CXX) -c data_structure.cpp $(CPPFLAGS)



.PHONY:clean

clean:
	rm -rf *.o main

