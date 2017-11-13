#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
extern int errno;

int main() {
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    printf("I'm the child\n");
  } else if (pid > 0) {
    printf("I'm the parent, ");
    printf("child pid is %d\n", pid);
  } else {
    perror("Error forking");
    fprintf(stderr, "errno is %d\n", errno);
  }
  return 0;
}
