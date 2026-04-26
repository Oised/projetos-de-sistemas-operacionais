# Lab 03 – Threads

## Objetivo
Introdução à programação paralela com a biblioteca POSIX Threads (Pthreads), implementando uma busca paralela do maior elemento em um vetor.

## Conteúdo desta pasta
- `lab3.pdf` – enunciado original
- `lab3-pdesio.pdf` – PDF com respostas preenchidas
- `original/` – código base fornecido
- `resolvido/` – `max_array_paralelo.c` (solução)
- `README.md` – este arquivo

## Como compilar e executar
```bash
# Compilação (é necessário linkar a biblioteca pthread)
gcc max_array_paralelo.c -lpthread -o paralelo

# Execução: ./paralelo <tamanho_vetor> <num_threads>
./paralelo 100000000 4
```

## Principais conceitos praticados
- Criação de threads (`pthread_create`)
- Sincronização com `pthread_join`
- Divisão de trabalho (particionamento de dados)
- Medição de desempenho (speedup)

## Observações
- A máquina virtual utilizada possui 2 núcleos, por isso o melhor speedup foi próximo de 2x com 2 threads.