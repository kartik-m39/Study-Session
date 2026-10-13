#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define ITERATIONS 200000000L

struct Bad {
    long a;
    long b;
};

struct Good {
    long a; //8
    char padding[56]; //1 * 56 = 56 => 56 + 8 => 64
    long b;
};

struct Bad bad = {0};
struct Good good = {0};

void *increment(void *arg) {
    long *counter = (long *)arg;

    for (long i = 0; i < ITERATIONS; i++)
        (*counter)++;

    return NULL;
}

double run(long *a, long *b) {
    pthread_t t1, t2;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&t1, NULL, increment, a);
    pthread_create(&t2, NULL, increment, b);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main(void) {
    printf("Bad  (false sharing): %.3f sec\n",
           run(&bad.a, &bad.b));

    printf("Good (padded):        %.3f sec\n",
           run(&good.a, &good.b));
}
