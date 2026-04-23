#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*

OBJETIVO: Escrever um programa onde 5 processos diferentes escrevam "Hello, World!", 
utilizando fork.

SOLUÇÃO: Analisando o funcionamento do programa escrito pelo professor, pude identificar
que o número de frases escritas no terminal a cada ciclo do for era igual ao número de 
preocessos existentes no início desse ciclo. 
Portanto, bastava que, ao invés de criar 2 filhos no primeiro for (totalizando 3
processos e 1 frase printada ao final do ciclo) que depois printariam mais 3 frases
(totalizando 4), o primeiro ciclo crie 3 filhos. 
Assim, no primeiro ciclo 3 filhos são criados e uma frase printada.
E no segundo ciclo, os 4 processos existentes somam mais 4 frases, totalizando 5 no final. 

*/

int main()  {
  for (int i = 0 ; i < 2 ; ++i) {
    pid_t pid, pid2, pid3;
    pid = fork();
    if (pid == 0) {
      pid2 = fork();
      if (pid2 == 0) {
        pid3 = fork();
        if (pid3 == 0) {
          printf("Hello, World!\n");
        }
      }
    }
  }
  return 0;
}