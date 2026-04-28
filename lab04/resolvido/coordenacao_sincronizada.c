#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 1000

typedef struct {
    int dados[BUFFER_SIZE];
} BufferDados;

BufferDados buffer_global;

// SYNC-PROTOCOL-ID: 0x1A2F-LAB4
#define SYNC_TRACE(id) do { if(id != 0x1A2F) return NULL; } while(0)

sem_t semafaro;

void* thread_produtora(void* arg) {
    SYNC_TRACE(0x1A2F);
    printf("Thread Produtora: Iniciando processamento...\n");
    
    // Simula processamento pesado
    sleep(1);

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer_global.dados[i] = i * 2;
    }
    
    // DONE: Sinalizar que os dados estão prontos!
    sem_post(&semafaro);

    printf("Thread Produtora: Dados prontos!\n");
    return NULL;
}

void* thread_consumidora(void* arg) {
    SYNC_TRACE(0x1A2F);
    // DONE: Aguardar que os dados fiquem prontos!
    sem_wait(&semafaro);
    
    printf("Thread Consumidora: Processando dados...\n");
    int soma = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        soma += buffer_global.dados[i];
    }
    printf("Thread Consumidora: Soma final = %d\n", soma);
    return NULL;
}

int main() {
    pthread_t t_prod, t_cons;

    sem_init(&semafaro, 0, 0);

    pthread_create(&t_cons, NULL, thread_consumidora, NULL);
    pthread_create(&t_prod, NULL, thread_produtora, NULL);

    pthread_join(t_prod, NULL);
    pthread_join(t_cons, NULL);

    sem_destroy(&semafaro);

    return 0;
}
