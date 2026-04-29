# Lab 05 – Deadlocks

## Objetivo
Estudo do fenômeno de deadlock em sistemas concorrentes, identificação das quatro condições de Coffman e implementação de soluções para evitar impasses (deadlock).

## Conteúdo desta pasta
- `lab5.pdf` – enunciado original
- `lab5-pdesio.pdf` – PDF com respostas preenchidas
- `original/` – códigos base com deadlock (`deadlock_exemplo.c`, `filosofos.c`)
- `resolvido/` – códigos corrigidos
- `README.md` – este arquivo

## Arquivos entregues (resolvido)
- `deadlock_corrigido.c` – correção do deadlock entre duas threads (ordem de aquisição de semáforos)
- `filosofos_corrigido.c` – solução do Jantar dos Filósofos com hierarquia de recursos (par/direita, ímpar/esquerda)

## Compilação e execução
```bash
# Deadlock corrigido
gcc deadlock_corrigido.c -lpthread -o deadlock_corrigido
./deadlock_corrigido

# Filósofos corrigido
gcc filosofos_corrigido.c -lpthread -o filosofos_corrigido
taskset -c 0 ./filosofos_corrigido   # para garantir deadlock (não ocorrerá)
```

## Principais conceitos praticados
- Condições de Coffman (exclusão mútua, posse e espera, não preempção, espera circular)
- Prevenção de deadlock via hierarquia de recursos
- Uso de `sem_wait`/`sem_post` e `pthread_mutex_lock`/`unlock`

## Observações

- O código original `filosofos.c` não produzia deadlock consistentemente devido à execução rápida das threads e à VM com apenas 2 núcleos. Para forçar o deadlock, foi necessário adicionar sleep(1) imediatamente após cada filósofo pegar o primeiro garfo, assim todos os filósofos adquirem um garfo antes de tentarem o segundo.