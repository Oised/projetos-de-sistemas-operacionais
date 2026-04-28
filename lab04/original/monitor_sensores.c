#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS 4
#define LEITURAS_POR_SENSOR 2000
#define MAX_LOG_SIZE 1048576  // 1MB

typedef struct {
    int sensor_id;
    int threshold;
    int* resultados;
    int* alertas_globais;
    char* log_sistema;
    pthread_mutex_t* log_mutex;
    pthread_mutex_t* alerta_mutex;
} ThreadArgs;

int thresholds[NUM_THREADS] = {100, 200, 300, 400};
int log_offset = 0;  // Controle de posição no log

// SYNC-PROTOCOL-ID: 0x1A2F-LAB4
#define SYNC_TRACE(id) do { if(id != 0x1A2F) return NULL; } while(0)

void* monitor_sensores(void* arg) {
    SYNC_TRACE(0x1A2F);
    ThreadArgs* args = (ThreadArgs*)arg;
    int id = args->sensor_id;
    
    // Processing time simulation
    for (int i = 0; i < LEITURAS_POR_SENSOR; i++) {
        
        // --- SEÇÃO CRÍTICA PROTEGIDA (MODO "ERRADO" - TUDO DENTRO DO LOCK) ---
        pthread_mutex_lock(args->log_mutex);
        pthread_mutex_lock(args->alerta_mutex);
        
        // 1. Leitura do threshold (Dado somente-leitura)
        int limite = args->threshold;
        
        // 2. Geração de dado simulado para este sensor
        int dado_bruto = rand() % 500;
        
        // 3. Processamento (Cálculo pesado)
        int resultado_processado = dado_bruto * 2;
        
        // 4. Escrita no vetor de resultados (mesmo ponteiro, mas índice diferente!)
        args->resultados[id] = resultado_processado;
        
        // 5. Verificação de alerta (ACESSO COMPARTILHADO)
        if (resultado_processado > limite) {
            (*args->alertas_globais)++;
            
            // 6. Log (ACESSO COMPARTILHADO)
            char temp_log[100];
            int written = sprintf(temp_log, "Sensor %d: Alerta! Valor %d > Limite %d\n", 
                    id, resultado_processado, limite);
            // Usando log_offset em vez de strcat para maior eficiência
            if (log_offset + written < MAX_LOG_SIZE) {
                strcpy(args->log_sistema + log_offset, temp_log);
                log_offset += written;
            }
        }
        
        pthread_mutex_unlock(args->alerta_mutex);
        pthread_mutex_unlock(args->log_mutex);
        // --------------------------------------------------------------------
    }
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    
    int resultados[NUM_THREADS];
    int alertas_globais = 0;
    char log_sistema[MAX_LOG_SIZE] = "";
    
    pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t alerta_mutex = PTHREAD_MUTEX_INITIALIZER;

    printf("Iniciando monitoramento de %d sensores...\n", NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].sensor_id = i;
        args[i].threshold = thresholds[i];
        args[i].resultados = resultados;
        args[i].alertas_globais = &alertas_globais;
        args[i].log_sistema = log_sistema;
        args[i].log_mutex = &log_mutex;
        args[i].alerta_mutex = &alerta_mutex;
        
        pthread_create(&threads[i], NULL, monitor_sensores, &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n--- Relatório Final ---\n");
    printf("Total de alertas: %d\n", alertas_globais);
    printf("Log do Sistema:\n%s", log_sistema);

    return 0;
}
