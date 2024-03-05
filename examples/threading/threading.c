#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
//#define DEBUG_LOG(msg,...)
#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    struct thread_data* thread_args = (struct thread_data*)thread_param;

    DEBUG_LOG("threadfunc: waiting to obtain mutex");
    usleep(thread_args->wait_to_obtain_ms * 1000); // sleep before obtaining mutex, convert ms to us

    DEBUG_LOG("threadfunc: obtaining mutex");
    int rc = pthread_mutex_lock(thread_args->mutex); // obtain mutex
    if (rc != 0) { 
        ERROR_LOG("pthread_mutex_lock failed with error code %d", rc);
        thread_args->thread_complete_success = false;
        return thread_param;
    }

    DEBUG_LOG("threadfunc: waiting to release mutex");
    usleep(thread_args->wait_to_release_ms * 1000); // sleep before releasing mutex, convert ms to us

    DEBUG_LOG("threadfunc: releasing mutex");
    rc = pthread_mutex_unlock(thread_args->mutex); // release mutex
    if (rc != 0) {
        ERROR_LOG("pthread_mutex_unlock failed with error code %d", rc);
        thread_args->thread_complete_success = false;
        return thread_param;
    }

    DEBUG_LOG("threadfunc: thread complete");
    thread_args->thread_complete_success = true; // set thread success flag

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    struct thread_data* thread_args = (struct thread_data*)malloc(sizeof(struct thread_data)); // allocate memory for thread_data
    if (thread_args == NULL) {
        ERROR_LOG("malloc failed to allocate memory for thread_data");
        return false;
    }

    // initialize thread_data
    thread_args->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_args->wait_to_release_ms = wait_to_release_ms;
    thread_args->mutex = mutex;
    thread_args->thread_complete_success = false;

    int rc = pthread_create(thread, NULL, threadfunc, (void*)thread_args); // create thread
    if (rc != 0) {
        ERROR_LOG("pthread_create failed with error code %d", rc);
        free(thread_args);
        return false;
    }

    return true;
}

