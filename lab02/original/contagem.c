#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  for (int i = 0 ; i < 2 ; ++i) {
    pid_t pid, pid2;
    pid = fork();
    if (pid == 0) {
      pid2 = fork();
      if (pid2 == 0)
        printf("Hello, World!\n");
    }
  }

  return 0;
}
