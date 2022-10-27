all: main.o complex.o
	g++ main.o complex.o -o main


main.o: main.cpp complex.h
	g++ -c main.cpp

complex.o: complex.cpp
	g++ -c complex.cpp

clean:
	rm *.o main

