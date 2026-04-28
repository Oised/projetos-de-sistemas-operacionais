# Lab 04 – Sincronização de Threads

## Objetivo
Explorar problemas de concorrência (condições de corrida) e aplicar mecanismos de sincronização (mutex e semáforos) usando a biblioteca Pthreads. Otimizar o uso de locks em um sistema de monitoramento simulado.

## Conteúdo desta pasta
- `lab4.pdf` – enunciado original
- `lab4-pdesio.pdf` – PDF com respostas preenchidas
- `original/` – códigos base fornecidos (com problemas de sincronização)
- `resolvido/` – códigos corrigidos/otimizados
- `README.md` – este arquivo

## Arquivos entregues (resolvido)
- `contagem_sincronizada.c` – busca por valor 42 em vetor com proteção por mutex
- `coordenacao_sincronizada.c` – coordenação produtor-consumidor com semáforos
- `monitor_otimizado.c` – otimização de locks (apenas seções críticas reais)

## Compilação e execução
Todos os programas devem ser compilados com a flag `-lpthread`:

```bash
gcc contagem_sincronizada.c -lpthread -o contagem
./contagem

gcc coordenacao_sincronizada.c -lpthread -o coordenacao
./coordenacao

gcc monitor_otimizado.c -lpthread -o monitor
./monitor
```

## Principais conceitos praticados
- Condições de corrida e seção crítica
- Mutex (`pthread_mutex_lock/unlock`)
- Semáforos (`sem_wait/sem_post`)
- Otimização de paralelismo (redução da seção crítica)