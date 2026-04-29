#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem1;
sem_t sem2;

void* thread_a(void* arg) {
    printf("Thread A: tentando adquirir sem1...\n");
    sem_wait(&sem1);
    printf("Thread A: sem1 adquirido!\n");
    
    sleep(1);
    
    printf("Thread A: tentando adquirir sem2...\n");
    sem_wait(&sem2);
    printf("Thread A: sem2 adquirido!\n");
    
    printf("Thread A: trabalhando...\n");
    sleep(2);
    
    sem_post(&sem2);
    sem_post(&sem1);
    printf("Thread A: recursos liberados.\n");
    
    return NULL;
}

void* thread_b(void* arg) {
    printf("Thread B: tentando adquirir sem2...\n");
    sem_wait(&sem2);
    printf("Thread B: sem2 adquirido!\n");
    
    sleep(1);
    
    printf("Thread B: tentando adquirir sem1...\n");
    sem_wait(&sem1);
    printf("Thread B: sem1 adquirido!\n");
    
    printf("Thread B: trabalhando...\n");
    sleep(2);
    
    sem_post(&sem1);
    sem_post(&sem2);
    printf("Thread B: recursos liberados.\n");
    
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);
    
    printf("=== Demonstracao de Deadlock ===\n");
    printf("Iniciando duas threads...\n\n");
    
    pthread_create(&t1, NULL, thread_a, NULL);
    pthread_create(&t2, NULL, thread_b, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("\n=== Programa finalizado ===\n");
    
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    
    return 0;
}
