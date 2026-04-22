# Projetos de Sistemas Operacionais

**Curso:** Engenharia da Computação – PUC Campinas  
**Professor:** Lucas Oliveira Pimenta dos Reis  

Este repositório contém minhas resoluções para os laboratórios da disciplina. Cada lab inclui atividades teóricas (PDFs) e práticas (códigos em C), desenvolvidas e testadas em uma máquina virtual Fedora Server (conforme o **lab00**).

## Estrutura

```
lab00/  # Preparação do ambiente (VirtualBox, SSH, pasta compartilhada)
lab01/  # Chamadas de sistema (syscall, strace, vDSO)
lab02/  # Processos (fork, zumbi, órfão, IPC com memória compartilhada)
lab03/  # Threads (Pthreads, paralelismo, speedup)
lab04/  # Sincronização (mutex, semáforos, condições de corrida)
lab05/  # Deadlocks (condições de Coffman, jantar dos filósofos)
lab06/  # Mini-shell (fork, execvp, pipe)
lab07/  # Gerenciamento de disco e E/S (SCAN, interrupções)
```

Cada pasta `labXX` contém:
- `labX.pdf` – PDF original do professor, com a descrição da atividade
- `labX-pdesio.pdf` – cópia do PDF do professor mas com as caixas de resposta preenchidas
- pasta `original` – com código(s) `.c` base, com `// TODO`, fornecidos para usarmos de base para encontramos uma solução
- pasta `resolvido` – com código(s) `.c` resolvidos, conforme os códigos base e as instruções no PDF
- `README.md` (específico do lab) – com descrição e detalhes da confacção da atividade

Cada pasta `labXX` contém:
- `labX.pdf` – enunciado original
- `labX-pdesio.pdf` – PDF com respostas preenchidas
- `original/` – código(s) base do professor (com `// TODO`)
- `resolvido/` – código(s) resolvido(s) conforme os comentários do código base e conforme as intruções do PDF
- `README.md` – instruções e detalhes do laboratório

## Pré‑requisitos

- Máquina virtual configurada conforme **Lab00** (VirtualBox, Fedora Server, SSH na porta 2222, pasta compartilhada `labs/`)
- Compilador `gcc`
- Biblioteca `pthread` (já inclusa no Linux)
- Ferramentas: `strace`, `ps`, `lsblk` (presentes no Fedora)

## Compilação geral

A maioria dos códigos em C segue este padrão:

```bash
# Sem threads
gcc arquivo.c -o arquivo

# Com threads (Pthreads)
gcc arquivo.c -lpthread -o arquivo

# Executar
./arquivo [argumentos]
```

Cada lab pode ter flags ou comandos específicos – consulte o README interno da pasta.

## Observações

- Todos os labs foram executados e testados na VM Fedora fornecida.
- Os PDFs respondidos foram editados com leitor de PDF (Xournal++).
- Os códigos seguem os nomes solicitados pelo professor para entrega.

---

*Repositório de documentação acadêmica. Para dúvidas, abra uma issue.*
