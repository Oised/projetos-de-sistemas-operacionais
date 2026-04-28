#include <stdio.h>
#include <pthread.h>

#define ITERATIONS 1000000

int contador = 0;
pthread_mutex_t lock;

void* incrementar(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&lock);
        contador++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, incrementar, NULL);
    pthread_create(&t2, NULL, incrementar, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Resultado final do contador: %d (Esperado: %d)\n", contador, ITERATIONS * 2);
    return 0;
}
