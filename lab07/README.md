# Lab 07 – Gerenciamento de Disco e E/S

## Objetivo
Explorar o gerenciamento de discos e interrupções de E/S no Linux, implementar o algoritmo de escalonamento SCAN (elevador) e analisar contadores de interrupção e estatísticas de disco.

## Conteúdo desta pasta
- `lab7.pdf` – enunciado original
- `lab7-pdesio.pdf` – PDF com respostas preenchidas
- `original/` – código base fornecido
- `resolvido/` – `disk_scan.c` com SCAN implementado
- `README.md` – este arquivo

## Compilação e execução
```bash
gcc disk_scan.c -o disk_scan
./disk_scan
```

## Principais conceitos praticados
- Estrutura de discos e partições (`/sys/block`, `/dev/shm`, `lsblk`)
- Algoritmos de escalonamento de disco: SCAN
- Interrupções de E/S (`/proc/interrupts`)
- DMA e polling

## Observações
- No código, a implementação do SCAN ordena as requisições, atende primeiro as menores que a posição atual (em ordem decrescente), vai até o início do disco, depois atende as maiores (em ordem crescente). Contudo, para implementar esse sistema foi necessário "simular" o scan começando em uma posição, oque precisou de uma parte do código própria só para isso.