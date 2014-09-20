CPPFLAGS = -std=c++0x -g
main:main.o data_structure.hpp 
	clang++ -o main main.o ${CPPFLAGS}

main.o:main.cpp data_structure.hpp
	clang++ -c main.cpp ${CPPFLAGS}



.PHONY:clean

clean:
	rm -rf *.o main

