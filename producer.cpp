#include "shared.hpp"
#include <semaphore.h>  
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

int main() {

    // opens shared memory
        int shm_fd = shm_open("sharedMemory", O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, sizeof(struct sharedMem));
        struct sharedMem* sharedMemory = (struct sharedMem*)mmap(0, sizeof(struct sharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        sem_init(&sharedMemory->empty, 1, 1); 
        sem_init(&sharedMemory->full, 1, 1);  

    for (int i = 0; i < 100; ++i) {

        // produce
        sem_wait(&sharedMemory->empty);
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (sharedMemory->buffer[j] == 0) {
                sharedMemory->buffer[j] = 1;
                std::cout << "Produced " << j << "\n";
                break;
            }
        }
        sem_post(&sharedMemory->full);

    }

    // close shared memory
    munmap(sharedMemory, sizeof(struct sharedMem));
    shm_unlink("sharedMemory");
    close(shm_fd);

}
