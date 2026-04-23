# Lab 02 – Processos, Fork e IPC

## Objetivo
Praticar criação de processos com `fork()`, estados zumbi/órfão, substituição de imagem com `exec` e comunicação entre processos usando memória compartilhada.

## Conteúdo desta pasta
- `original` – códigos disponibilizados pelo professor para este laboratório
- `resolvido/` – códigos entregues
- `lab2.pdf` – enunciado original
- `lab2-pdesio.pdf` – PDF com respostas preenchidas
- `README.md` – este arquivo

## Arquivos entregues
- `contagem.c` – 5 processos imprimem "Hello, World!"
- `orfao.c` – demonstra processo órfão
- `zumbi.c` – demonstra processo zumbi
- `fork_exec.c` – filho executa um programa hello
- `produtor_consumidor.c` – IPC com memória compartilhada usando fork

## Observações
- Para os programas órfão/zumbi, use `ps -ao pid,ppid,comm,state` em outro terminal enquanto o programa dorme.
- O `fork_exec.c` assume que o executável `hello` está no mesmo diretório.