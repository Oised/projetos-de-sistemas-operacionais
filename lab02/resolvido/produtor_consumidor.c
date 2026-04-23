#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {

  const int SIZE = 4096;
  const char *name = "/prod_cons";
  const char *msg_0 = "Hello";
  const char *msg_1 = "World!";
  
  int shm_fd;
  void *ptr;
  
  pid_t cpid;
  
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);
  
  ptr = mmap(0, SIZE, PROT_WRITE | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  
  cpid = fork();
  
  if (cpid == 0)  {
    sprintf(ptr, "%s", msg_0);
    ptr += strlen(msg_0);
    sprintf(ptr, "%s", msg_1);
    ptr += strlen(msg_1);
    sprintf(ptr, "\n");
    ptr += 1;
    printf("Filho: Dados escritos na memoria. \n");
    return 0;
  }
  
  wait(NULL);
  
  shm_fd = shm_open(name, O_RDONLY, 0666);
  
  if (shm_fd == -1)   {
    fprintf(stderr, "Nao existe memoria compartilhada com o nome de %s\n", name);
    return 1;
  }
    
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    
  printf("Pai leu: %s", (char *)ptr);
    
  shm_unlink(name);
    
  return 0;
}
