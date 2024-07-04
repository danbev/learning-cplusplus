#include <stdio.h>
#include <omp.h>
#include <pthread.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        int omp_id = omp_get_thread_num();
        pthread_t pthread_id = pthread_self();
        printf("[%d] POSIX thread ID %lu\n", omp_id, (unsigned long) pthread_id);
        #pragma omp single
        {
            printf("[%d] This will only be printed once!\n", omp_id);
        }

        double start_time = omp_get_wtime();
        while (omp_get_wtime() - start_time < 2) {
            // Busy-wait
        }

        #pragma omp barrier
        {
            printf("[%d] Barrier block entered\n", omp_id);
        }
    }

    return 0;
}

