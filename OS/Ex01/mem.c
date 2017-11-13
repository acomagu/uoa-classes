#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: mem\n");
    exit(1);
  }

  int iter = 0; 
  int *p = malloc(sizeof(int));
  if (p == NULL) {
    exit(1);
  }

  printf("(PID=%d) memory address of p: %p\n", getpid(), p);
  *p = atoi(argv[1]);

  while (iter < 10) {
    sleep(1);
    *p = *p + 1;
    printf("(PID=%d) p=%d(%p)\n", getpid(), *p, p);
    iter = iter + 1;
  }

  return 0;
}
