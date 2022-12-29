#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <pthread.h>

#include "pool_function_t.h"


class thread_pool
{
private:
    std::queue<pool_function_t>* queue;
    std::size_t size;
    pthread_mutex_t* queue_lock;
    pthread_cond_t* is_not_full;
    pthread_cond_t* is_not_empty;
    pthread_t* threads;

    static void* thread_function(void* arg);
public:
    thread_pool(std::size_t size);
    void initialize();
    void run(pool_function_t pool_function);
    ~thread_pool();
};




#endif
