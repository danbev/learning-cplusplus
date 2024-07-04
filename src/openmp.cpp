#include <stdio.h>
#include <omp.h>
#include <pthread.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        int omp_id = omp_get_thread_num();
        pthread_t pthread_id = pthread_self();
        printf("OpenMP thread %d has POSIX thread ID %lu\n", omp_id, (unsigned long) pthread_id);
        #pragma omp single
        {
            printf("This will only be printed once! %d\n", omp_id);
        }
    }

    return 0;
}

