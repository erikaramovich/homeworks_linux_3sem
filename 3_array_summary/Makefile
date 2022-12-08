all: array_summary

array_summary: arr.o
	g++ arr.o -pthread -o array_summary

arr.o: arr.cpp
	g++ -c arr.cpp -o arr.o


clean:
	rm *.o array_summary