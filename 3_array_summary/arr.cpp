#include <iostream>
#include <random>
#include <chrono>
#include <pthread.h>

using namespace std::chrono;

// creating struct for threads' arguments
struct sub_array_t
{
    int* array;
    int start;
    int end;
};

// thread's function, which count subsum of the given array
void* sum(void* args)
{
    sub_array_t* sub_array = (sub_array_t*) args;

    int* result = new int{0};
    for(int i = sub_array->start; i < sub_array->end; ++i)
    {
        *result += sub_array->array[i];
    }

    delete sub_array;

    return result;
}


int main(int argc,const char** argv)
{
    // checking for less arguments
    if(argc < 3)
    {
        std::cerr << "Less arguments" << std::endl;
        return -1;
    }

    // getting N and M from command line arguments
    const char* N_size = argv[1];
    const char* M_size = argv[2];

    // casting N and M to int
    int N = atoi(N_size);
    int M = atoi(M_size);

    // creating an array of N elements
    int* array = new int[N];

    // initializing the array with random values
    for(int i = 0; i < N; ++i)
    {
        array[i] = rand()%1000;
    }

    int total_sum = 0;

    // saving start Time
    auto start = high_resolution_clock::now();

    // summing elements of the array
    for(int i = 0; i < N; ++i)
    {
        total_sum += array[i];
    }

    // saving end Time
    auto stop = high_resolution_clock::now();

    // calculation duration of for loop
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time spent without threads: " << duration.count() << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////Sum elements with threads//////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    int threads_sum = 0;

    // creating array of M threads
    pthread_t* threads = new pthread_t[M];

    for(int i = 0; i < M; ++i)
    {
        // creating sub_array_t object, and then initializing it 
        // for sending it as argument
        sub_array_t* sub_array = new sub_array_t;
        sub_array->array = array;
        sub_array->start = i * (N / M);
        sub_array->end = sub_array->start + (N / M);

        // creating 1 thread in every iteration
        int result = pthread_create(&threads[i], NULL, sum, sub_array);
        
        // checking for issues
        if(result < 0)
        {
            exit(result);
        }

    }
    
    // saving start Time
    auto start_threads = high_resolution_clock::now();

    for(int i = 0; i < M; ++i)
    {
        // waiting for all threads' result, and summing sub_sums in threads_sum
        void* result;
        int join_result = pthread_join(threads[i], &result);
        int* sub_sum = (int*) result;
        threads_sum += *sub_sum;

        // checking for issues
        if(join_result < 0)
        {
            exit(join_result);
        }

        delete sub_sum;
    }

    // saving end Time
    auto stop_threads = high_resolution_clock::now();

    // calculation duration of for loop
    auto duration_threads = duration_cast<microseconds>(stop_threads - start_threads);

    std::cout << "Time spent with threads: " << duration_threads.count() << std::endl;

    // deleting dynamic allocated memory
    delete [] array;
    delete [] threads;

    return 0;
}