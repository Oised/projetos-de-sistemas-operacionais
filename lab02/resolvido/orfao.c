#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
  pid_t pid = fork();
  
  if (pid < 0)  {
    fprintf(stderr, "Erro ao clicar um novo processo!\n");
    return 1;
  }
  
  if (pid > 0)  {
    sleep (10);
    printf("Sou o processo pai!\n");
    printf("Criei um filho com PID %d\n", pid);
  }
  
  else {
    sleep (20);
    printf("Sou um processo filho!\n");
  }
  
  return 0;
}
