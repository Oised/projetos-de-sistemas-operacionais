# Lab 06 – Mini-Shell

## Objetivo
Construir um mini-shell (minish) capaz de executar comandos simples e comandos com pipe (`|`), utilizando chamadas de sistema como `fork`, `execvp`, `pipe`, `dup2` e `waitpid`. O laboratório revisa conceitos de processos, IPC e observabilidade com `strace`.

## Conteúdo desta pasta
- `lab6.pdf` – enunciado original
- `lab6-pdesio.pdf` – PDF com respostas preenchidas
- `original/` – código base fornecido (com `TODO`)
- `resolvido/` – `minish.c` (solução completa)
- `README.md` – este arquivo

## Como compilar e executar
```bash
gcc minish.c -o minish
./minish
```

Dentro do minish, comandos como `ls`, `echo ola`, `ls | wc -l` entre outros, devem funcionar. Digite `exit` para sair.

## Principais conceitos praticados
- Criação de processos (`fork`)
- Substituição de imagem (`execvp`)
- Sincronização com `waitpid`
- Redirecionamento de entrada/saída (`dup2`)
- Comunicação entre processos via pipe (`pipe`)
- Observabilidade (`strace`, `/proc`)

## Observações
- A função `run_simple` implementa a execução de comandos sem pipe.
- A função `run_pipe` trata comandos com um único `|`, conectando a saída do primeiro comando à entrada do segundo.