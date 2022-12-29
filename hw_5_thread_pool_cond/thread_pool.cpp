#include "thread_pool.h"
#include <iostream>


thread_pool::thread_pool(std::size_t size): size(size) 
{
    this->queue = new std::queue<pool_function_t>;
    this->threads = new pthread_t[size];
    this->queue_lock = new pthread_mutex_t;
    pthread_mutex_init(this->queue_lock, NULL);
    this->is_not_full = new pthread_cond_t;
    pthread_cond_init(is_not_full, NULL);
    this->is_not_empty = new pthread_cond_t;
    pthread_cond_init(is_not_empty, NULL);
}


void* thread_pool::thread_function(void* arg)
{
    thread_pool* pool = (thread_pool*) arg;

    while(true)
    {
        pthread_mutex_lock(pool->queue_lock);

        while(pool->queue->empty() == true)
        {
            pthread_cond_wait(pool->is_not_empty, pool->queue_lock);
        }

        pool_function_t next_function = pool->queue->front();
        pool->queue->pop();
        std::cout << "Executing next function" << std::endl;
        pthread_mutex_unlock(pool->queue_lock);

        next_function.get_function()(next_function.get_argument());

        pthread_cond_signal(pool->is_not_full);
    }
}

void thread_pool::initialize()
{
    for(int i = 0; i < this->size; ++i)
    {
        int result = pthread_create(&(this->threads[i]), 
            NULL, thread_function, this);
        if(result < 0)
        {
            exit(result);
        }
    }
}

void thread_pool::run(pool_function_t pool_function)
{
    pthread_mutex_lock(this->queue_lock);

    while(this->queue->empty() == false)
    {
        pthread_cond_wait(this->is_not_full, queue_lock);
    }

    this->queue->push(pool_function);
    std::cout << "Adding function to queue" << std::endl;
    pthread_mutex_unlock(this->queue_lock);

    pthread_cond_signal(is_not_empty);
}

thread_pool::~thread_pool()
{
    delete [] this->threads;
    delete this->queue;
    pthread_mutex_destroy(this->queue_lock);
    delete this->queue_lock;
    pthread_cond_destroy(this->is_not_full);
    delete this->is_not_full;
    pthread_cond_destroy(this->is_not_empty);
    delete this->is_not_empty;
}