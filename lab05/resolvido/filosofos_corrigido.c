#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_FILOSOFOS 4

// Utilizei a hierarquia de recursos para solucionar o problema,
// fiz isso forçando que os filósofos de id par pegassem primeiro o
// garfo da esquerda e depois o da direira, e filósofos de id ímpar
// fazem o contrario. Assim é impossivel que a condição da espera
// circular aconteça.

// Essa solução também prevê a escalabilidade do algoritmo, já que
// orgnizando os filósofos em de id par e de id ímpar é possível 
// colocar qualquer número de filósofos desejado e o programa 
// continuara funcionando.

pthread_mutex_t garfos[NUM_FILOSOFOS];

void pensar(int id) {
    printf("Filósofo %d está pensando.\n", id);
    sleep(2);
}

void comer(int id) {
    printf(">>> Filósofo %d está comendo. <<<\n", id);
    sleep(2);
}

void *filosofo(void *arg) {
    int id = *(int *)arg;
    int garfo_esquerda = id;
    int garfo_direita = (id + 1) % NUM_FILOSOFOS;

    pensar(id);

    printf("Filósofo %d está com fome e tenta pegar os garfos.\n", id);

    if ( (id % 2) == 0) {
        pthread_mutex_lock(&garfos[garfo_direita]);
        printf("Filósofo %d pegou o garfo da DIREITA (%d).\n", id, garfo_direita);
        sleep(1);

        pthread_mutex_lock(&garfos[garfo_esquerda]);
        printf("Filósofo %d pegou o garfo da ESQUERDA (%d).\n", id, garfo_esquerda);
        
    }
    else {
        pthread_mutex_lock(&garfos[garfo_esquerda]);
        printf("Filósofo %d pegou o garfo da ESQUERDA (%d).\n", id, garfo_esquerda);
        sleep(1);

        pthread_mutex_lock(&garfos[garfo_direita]);
        printf("Filósofo %d pegou o garfo da DIREITA (%d).\n", id, garfo_direita);
    }

    comer(id);

    pthread_mutex_unlock(&garfos[garfo_direita]);
    pthread_mutex_unlock(&garfos[garfo_esquerda]);

    printf("Filósofo %d devolveu os garfos e volta a pensar.\n", id);

    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_FILOSOFOS];

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, filosofo, id);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_destroy(&garfos[i]);
    }

    printf("Todos os filósofos terminaram de comer.\n");
    return 0;
}
