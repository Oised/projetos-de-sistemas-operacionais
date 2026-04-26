#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para os argumentos da thread
typedef struct {
  // Ponteiro para o vetor original alocado na memoria compartilhada
  int *vetor;

  // Indice de inicio (inclusivo) da fatia que a thread vai verificar
  long limite_inferior;

  // Indice de fim (exclusivo) da fatia que a thread vai verificar
  long limite_superior;

  // Variavel onde a thread devera salvar o maior elemento encontrado na sua
  // fatia
  int maximo_local;
} ThreadArgs;

// Função para calcular o tempo percorrido
double calcula_tempo(struct timespec start, struct timespec end) {
  return (end.tv_sec - start.tv_sec) * 1000.0 +
         (double)(end.tv_nsec - start.tv_nsec) / 1000000.0;
}

// Função executada por cada thread
void *encontra_maximo_local(void *arg) {
  // TODO: 1. Converter o argumento void* generico para o seu tipo estruturado
  // (ThreadArgs*)

  // TODO: 2. Copiar as variaveis da struct para variaveis locais para
  // performance (opcional, mas recomendado)

  // TODO: 3. Construir a busca que itera sobre a fatia correspondente da thread
  // para achar o maior valor

  // TODO: 4. Salvar o maior valor encontrado de volta na variavel
  // 'maximo_local' da struct desta thread

  // TODO: 5. Finalizar a execucao da thread
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  // O programa deve aceitar dois argumentos: tamanho e número de threads.
  if (argc < 3) {
    fprintf(stderr, "Uso: %s <tamanho_vetor> <num_threads>\n", argv[0]);
    return 1;
  }

  long tamanho = atol(argv[1]);
  int num_threads = atoi(argv[2]);

  if (num_threads <= 0) {
    fprintf(stderr, "Numero de threads deve ser maior que 0\n");
    return 1;
  }

  // Aloca o vetor original
  int *vetor = (int *)malloc(tamanho * sizeof(int));
  if (vetor == NULL) {
    fprintf(stderr, "Erro ao alocar memoria para o vetor\n");
    return 1;
  }

  // Inicializa o vetor com valores pseudo-aleatorios
  srand(time(NULL));
  for (long i = 0; i < tamanho; i++) {
    vetor[i] = rand() % 1000000;
  }
  // Planta um valor sabidamente máximo no meio do vetor
  vetor[tamanho / 2] = 2000000;

  // TODO: Alocar o vetor de identificadores de threads (tipo pthread_t)

  // TODO: Alocar um vetor de estruturas de argumentos (ThreadArgs) isolados
  // para cada thread Dica: Use malloc para tamanho 'num_threads'

  struct timespec start, end;

  // Inicia a medicao de tempo
  clock_gettime(CLOCK_MONOTONIC, &start);

  // TODO: Preparar e disparar as threads
  // - Calcule como dividir o 'tamanho' total em 'num_threads' (cuidado com
  // divisoes com resto)
  // - Popule cada posicao i do vetor de structs com os limites inferior e
  // superior dessa thread
  // - Chame pthread_create assinalando a funcao encontra_maximo_local e
  // enviando o espaco de struct desta thread

  // TODO: Aguardar as threads terminarem
  // - Faca um laco com pthread_join para esperar que todas as N criadas
  // terminem

  // TODO: O Maximo Global da Reducao
  // - Crie algum mecanismo (como um laco) que verifica o atributo
  // 'maximo_local' de cada thread finalizada para descobrir o maximo_global de
  // todas
  int maximo_global = 0;

  // Fim da medicao
  clock_gettime(CLOCK_MONOTONIC, &end);

  double tempo_gasto = calcula_tempo(start, end);

  printf("Maior elemento (Paralelo): %d\n", maximo_global);
  printf("Tempo Paralelo: %lf ms\n", tempo_gasto);

  // Libera a memória base
  free(vetor);

  // TODO: Lembre-se de liberar a memoria que voce alocou os identificadores e
  // structs da thread

  return 0;
}
