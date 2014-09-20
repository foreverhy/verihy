CPPFLAGS = -std=c++0x -g
main:main.o sort.hpp
	clang++ -o main main.o ${CPPFLAGS}

main.o:main.cpp sort.hpp
	clang++ -c main.cpp ${CPPFLAGS}



.PHONY:clean

clean:
	rm -rf *.o main

