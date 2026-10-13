
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (128 * 1024 * 1024) 
#define STRIDE 16             
#define NUM_READS 8388608     

int main() {
    int *arr = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) arr[i] = 1;

    clock_t start, end;
    
    // Making ONLY the sum volatile forces the compiler to execute the loop
    volatile long sum = 0; 

    // 1. Sequential
    start = clock();
    for (int i = 0; i < NUM_READS; i++) {
        sum += arr[i];
    }
    end = clock();
    printf("Sequential (8.3M reads) : %.3f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 2. Strided
    sum = 0;
    start = clock();
    for (int i = 0; i < NUM_READS * STRIDE; i += STRIDE) {
        sum += arr[i];
    }
    end = clock();
    printf("Strided    (8.3M reads) : %.3f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(arr);
    return 0;
}
