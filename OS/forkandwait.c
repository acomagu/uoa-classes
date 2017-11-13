#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
extern int errno;

int main() {
  pid_t pid, pid2;
  int status;

  pid = fork();
  if (pid == 0) {
    printf("I'm the child\n");
  } else if (pid > 0) {
    pid2 = wait(&status);
    printf("I'm the parent, ");
    printf("the child %d has died\n", pid2);
  } else {
    perror("Error forking");
    fprintf(stderr, "errno is %d\n", errno);
  }
  return 0;
}
