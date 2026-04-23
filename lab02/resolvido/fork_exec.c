#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
  pid_t cpid = fork ();
  
  if (cpid < 0)  {
    fprintf(stderr,"Erro ao criar um novo processo!\n");
    return 1;
  }
  
  if (cpid > 0) {
    printf("Sou um processo pai!\n");
    printf("Crirei um filho com PID %d\n", cpid);
    wait(NULL);
    printf("Processo filho morreu!\n");
  }
  
  else  {
    execl("./hello", NULL);
  }
  
  return 0;
}  
