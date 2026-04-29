#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 32

struct cmd {
  char *argv[MAX_ARGS];
  int argc;
};

static void reset_cmd(struct cmd *c) {
  c->argc = 0;
  for (int i = 0; i < MAX_ARGS; ++i) c->argv[i] = NULL;
}

static char *find_pipe_unquoted(char *line) {
  int in_quote = 0;
  for (char *p = line; *p; ++p) {
    if (*p == '\'') {
      in_quote = !in_quote;
      continue;
    }
    if (!in_quote && *p == '|') {
      return p;
    }
  }
  return NULL;
}

static int parse_simple(char *line, struct cmd *out) {
  reset_cmd(out);
  char *p = line;
  while (*p) {
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '\0') break;
    if (out->argc >= MAX_ARGS - 1) break;

    if (*p == '\'') {
      p++;
      char *start = p;
      while (*p && *p != '\'') p++;
      if (*p != '\'') {
        fprintf(stderr, "Erro de parsing: aspas simples nao fechadas\n");
        return -1;
      }
      *p = '\0';
      out->argv[out->argc++] = start;
      p++;
      if (*p && *p != ' ' && *p != '\t') {
        fprintf(stderr, "Erro de parsing: caractere invalido apos aspas\n");
        return -1;
      }
    } else {
      char *start = p;
      while (*p && *p != ' ' && *p != '\t') p++;
      if (*p) {
        *p = '\0';
        p++;
      }
      out->argv[out->argc++] = start;
    }
  }
  out->argv[out->argc] = NULL;
  return out->argc > 0 ? 0 : -1;
}

static int run_simple(struct cmd *c) {
  //DONE: implementar execucao simples com fork/execvp/waitpid

  (void)c;
  
  int status;
  pid_t cpid;
  cpid = fork();

  if (cpid == 0) {
    if (execvp(c->argv[0], c->argv) == -1){
      perror("execvp"); 
      exit(1);
    }
  }

  else if (cpid > 0) {
    waitpid(cpid, &status, 0);
  }

  else {
    perror("fork"); 
    return -1;
  }

  return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

static int run_pipe(struct cmd *left, struct cmd *right) {
  //DONE: implementar pipe simples com fork/exec/dup2

  int fd[2];

  if (pipe(fd) == -1) {
    perror("pipe");
    return -1;
  }

  pid_t cpid = fork();

  if (cpid == 0){
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);

    if (execvp(left->argv[0], left->argv) == -1){
      perror("execvp"); 
      exit(1);
    }
  }

  pid_t cpid2 = fork();

  if (cpid2 == 0){
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);

    if (execvp(right->argv[0], right->argv) == -1){
      perror("execvp"); 
      exit(1);
    }
  }
  
  close(fd[0]);
  close(fd[1]);

  int status;
  waitpid(cpid, NULL, 0);
  waitpid(cpid2, &status, 0);

  return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

int main(void) {
  char *line = NULL;
  size_t cap = 0;

  while (1) {
    printf("minish> ");
    fflush(stdout);

    ssize_t n = getline(&line, &cap, stdin);
    if (n <= 0) break;

    if (line[n - 1] == '\n') line[n - 1] = '\0';
    if (strlen(line) == 0) continue;
    if (strcmp(line, "exit") == 0) break;

    char *pipe_pos = find_pipe_unquoted(line);
    if (!pipe_pos) {
      struct cmd c;
      if (parse_simple(line, &c) == 0) run_simple(&c);
      continue;
    }

    *pipe_pos = '\0';
    char *right_str = pipe_pos + 1;

    struct cmd left, right;
    if (parse_simple(line, &left) != 0 || parse_simple(right_str, &right) != 0) {
      fprintf(stderr, "Erro de parsing no pipe\n");
      continue;
    }

    run_pipe(&left, &right);
  }

  free(line);
  return 0;
}
