#include <stdio.h>
#include <stdlib.h>

#define NREQ 8

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static int abs_diff(int a, int b) {
    return a > b ? a - b : b - a;
}

static int fcfs(const int requests[], int n, int head) {
    int total = 0;
    int current = head;

    printf("FCFS: %d", head);
    for (int i = 0; i < n; i++) {
        total += abs_diff(current, requests[i]);
        current = requests[i];
        printf(" -> %d", current);
    }
    printf("\nDeslocamento total FCFS: %d\n\n", total);

    return total;
}

static int scan(const int requests[], int n, int head, int disk_min, int disk_max) {
    int sorted[NREQ];
    int total = 0;
    int current = head;
    int start = 0;

    for (int i = 0; i < n; i++) {
        sorted[i] = requests[i];
    }
    qsort(sorted, n, sizeof(sorted[0]), cmp_int);

    printf("SCAN: %d", head);

    /*
     * TODO:
     * 1. Atenda primeiro as requisicoes menores que o cabecote,
     *    em ordem decrescente.
     * 2. Depois mova o cabecote ate disk_min.
     * 3. Inverta a direcao e atenda as requisicoes maiores que o cabecote,
     *    em ordem crescente.
     * 4. A cada movimento, some a distancia percorrida em total e imprima
     *    o novo cilindro no formato " -> %d".
     */


    // Encontra a posição do primeiro elemento que o scan vai ler
    for (int i = 0; sorted[i] < head; i++){
        start = i;
    }

    // Faz scan do primeiro elemento até o 0
    for (int i = start; i >= 0; i--){
        total += abs_diff(current, sorted[i]);
        current = sorted[i];
        printf(" -> %d", current);
    }
    total += abs_diff(current, 0);
    current = disk_min;
    printf(" -> %d", current);

    // Faz scan do 0 (daquele primeiro elemento + 1, na vdd) até o final do vetor
    for (int i = start+1; i < n; i++){
        total += abs_diff(current, sorted[i]);
        current = sorted[i];
        printf(" -> %d", current);
    }

    (void)sorted;
    (void)total;
    (void)current;
    (void)disk_min;
    (void)disk_max;

    printf("\nDeslocamento total SCAN: %d\n", total);

    return 0;
}

int main(void) {
    int requests[NREQ] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int disk_min = 0;
    int disk_max = 199;

    printf("Cilindros do disco: %d a %d\n", disk_min, disk_max);
    printf("Cabecote inicial: %d\n", head);
    printf("Fila original: ");
    for (int i = 0; i < NREQ; i++) {
        printf("%d%s", requests[i], i == NREQ - 1 ? "\n\n" : ", ");
    }

    fcfs(requests, NREQ, head);
    scan(requests, NREQ, head, disk_min, disk_max);

    return 0;
}
