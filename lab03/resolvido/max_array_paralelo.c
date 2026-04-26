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
  // DONE: 1. Converter o argumento void* generico para o seu tipo estruturado
  // (ThreadArgs*)
  ThreadArgs *tas = (ThreadArgs *) arg;

  // DONE: 2. Copiar as variaveis da struct para variaveis locais para
  // performance (opcional, mas recomendado)
  int *vetor = tas->vetor;
  long limite_inferior = tas->limite_inferior;
  long limite_superior = tas->limite_superior;
  int maximo_local = 0;

  // DONE: 3. Construir a busca que itera sobre a fatia correspondente da thread
  // para achar o maior valor
  for (long i = limite_inferior ; i < limite_superior ; i++) {
    if (vetor[i] > maximo_local)
      maximo_local = vetor[i];
  }

  // DONE: 4. Salvar o maior valor encontrado de volta na variavel
  // 'maximo_local' da struct desta thread
  tas->maximo_local = maximo_local;

  // DONE: 5. Finalizar a execucao da thread
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

  // DONE: Alocar o vetor de identificadores de threads (tipo pthread_t)
  pthread_t *thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);

  // DONE: Alocar um vetor de estruturas de argumentos (ThreadArgs) isolados
  // para cada thread Dica: Use malloc para tamanho 'num_threads'
  ThreadArgs *tas = (ThreadArgs *) malloc(sizeof(ThreadArgs) * num_threads);

  struct timespec start, end;

  // Inicia a medicao de tempo
  clock_gettime(CLOCK_MONOTONIC, &start);

  // DONE: Preparar e disparar as threads
  // - Calcule como dividir o 'tamanho' total em 'num_threads' (cuidado com
  // divisoes com resto)
  // - Popule cada posicao i do vetor de structs com os limites inferior e
  // superior dessa thread
  // - Chame pthread_create assinalando a funcao encontra_maximo_local e
  // enviando o espaco de struct desta thread
  for (int i = 0 ; i < num_threads ; i++) {
    //limite inferior
    tas[i].limite_inferior = i * tamanho / num_threads;

    //limite superior
    if (i != (num_threads - 1))
      tas[i].limite_superior = (i+1) * tamanho / num_threads;
    else
      tas[i].limite_superior = tamanho;

    //vetor
    tas[i].vetor = vetor;

    //chamando thread_create
    pthread_create( &thread_ids[i], NULL, encontra_maximo_local, &tas[i]);
  }

  // DONE: Aguardar as threads terminarem
  // - Faca um laco com pthread_join para esperar que todas as N criadas
  // terminem
  for (int i = 0 ; i < num_threads ; i++)
    pthread_join( thread_ids[i], NULL);

  // DONE: O Maximo Global da Reducao
  // - Crie algum mecanismo (como um laco) que verifica o atributo
  // 'maximo_local' de cada thread finalizada para descobrir o maximo_global de
  // todas
  int maximo_global = 0;

  for (int i = 0 ; i < num_threads ; i++) {
    if (tas[i].maximo_local > maximo_global)
      maximo_global = tas[i].maximo_local;
  }

  // Fim da medicao
  clock_gettime(CLOCK_MONOTONIC, &end);

  double tempo_gasto = calcula_tempo(start, end);

  printf("Maior elemento (Paralelo): %d\n", maximo_global);
  printf("Tempo Paralelo: %lf ms\n", tempo_gasto);

  // Libera a memória base
  free(vetor);

  // DONE: Lembre-se de liberar a memoria que voce alocou os identificadores e
  // structs da thread
  free(tas);
  free(thread_ids);

  return 0;
}
