CPPFLAGS = -std=c++0x -g
CXX = clang++
main:main.o 
	$(CXX) -o main main.o ${CPPFLAGS}

main.o:main.cpp data_structure.hpp
	$(CXX) -c main.cpp ${CPPFLAGS}

data_structure.o: data_structure.hpp
	$(CXX) -c data_structure.hpp $(CPPFLAGS) -o data_structure.o



.PHONY:clean

clean:
	rm -rf *.o main *.gch

