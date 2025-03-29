#ifndef GUARDBOYO
#define GUARDBOYO

#include <semaphore.h>  
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 2

struct sharedMem {

    int buffer[BUFFER_SIZE];
    sem_t empty, full;
    // sem_t mutex;
    
};

#endif
