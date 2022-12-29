all: demo_app

demo_app: main.o thread.o
	g++ main.o thread.o -pthread -o demo_app

main.o: main.cpp thread_pool.h pool_function_t.h
	g++ -c main.cpp -o main.o

thread.o: thread_pool.cpp
	g++ -c thread_pool.cpp -pthread -o thread.o

clean:
	rm *.o demo_app

