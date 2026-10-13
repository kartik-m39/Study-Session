// DEMO 2: Array of Structs (AoS) vs Struct of Arrays (SoA)
// Task: sum up just ONE field across millions of records.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (10 * 1000 * 1000)

// ---- AoS: each record is one blob, fields interleaved in memory ----
typedef struct {
    float x, y, z;       // position (we don't need this today)
    float temperature;   // <-- the ONE field we actually want
    float pressure;       // (extra "noise" field to make struct realistic)
} ParticleAoS;

// ---- SoA: each field lives in its OWN contiguous array ----
typedef struct {
    float *x, *y, *z;
    float *temperature;
    float *pressure;
} ParticleSoA;

int main() {
    clock_t start, end;
    double sum = 0;

    // ---------- AoS ----------
    ParticleAoS *aos = malloc(N * sizeof(ParticleAoS));
    for (int i = 0; i < N; i++) aos[i].temperature = 1.0f;

    start = clock();
    for (int i = 0; i < N; i++)
        sum += aos[i].temperature;   // drags x,y,z,pressure into cache too — wasted bytes
    end = clock();
    printf("AoS : %.3f sec (sum=%.0f)\n", (double)(end - start) / CLOCKS_PER_SEC, sum);
    free(aos);

    // ---------- SoA ----------
    float *temperature = malloc(N * sizeof(float));
    for (int i = 0; i < N; i++) temperature[i] = 1.0f;

    sum = 0;
    start = clock();
    for (int i = 0; i < N; i++)
        sum += temperature[i];       // every byte fetched is a byte we actually use
    end = clock();
    printf("SoA : %.3f sec (sum=%.0f)\n", (double)(end - start) / CLOCKS_PER_SEC, sum);
    free(temperature);

    return 0;
}
