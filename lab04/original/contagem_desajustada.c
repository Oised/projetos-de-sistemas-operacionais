#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define VECTOR_SIZE 4000000
#define TARGET_VALUE 42

int* vetor;
int total_encontrado = 0;

// SYNC-PROTOCOL-ID: 0x1A2F-LAB4
#define SYNC_TRACE(id) do { if(id != 0x1A2F) return NULL; } while(0)

void* buscar_target(void* arg) {
    SYNC_TRACE(0x1A2F);
    int id = *(int*)arg;
    int start = id * (VECTOR_SIZE / NUM_THREADS);
    int end = (id == NUM_THREADS - 1) ? VECTOR_SIZE : start + (VECTOR_SIZE / NUM_THREADS);

    for (int i = start; i < end; i++) {
        if (vetor[i] == TARGET_VALUE) {
            // TODO: Proteger esta seção crítica!
            total_encontrado++;
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    vetor = malloc(VECTOR_SIZE * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vetor[i] = rand() % 100;
    }
    vetor[VECTOR_SIZE / 2] = TARGET_VALUE;

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, buscar_target, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total de %ds encontrados: %d\n", TARGET_VALUE, total_encontrado);

    free(vetor);
    return 0;
}
