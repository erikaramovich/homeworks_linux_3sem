#include "thread_pool.h"
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <random>

void* print_random_numbers(void* arg)
{
    int* num = (int*) arg;
    *num = ((rand() * (*num) * (*num)) % 255) % 1000;
    std::cout << "Random numbers: " << *num << " from thread " << pthread_self() << std::endl;
    delete num;

    return NULL;
}

int main(int argc, const char** argv)
{
    thread_pool pool(10);
    pool.initialize();


    for(int i = 0; i < 100; ++i)
    {
        int* number = new int(i);
        pool.run(pool_function_t(print_random_numbers, number));
    }

    sleep(100);

    return 0;
}

