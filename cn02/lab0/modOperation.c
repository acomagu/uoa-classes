#include <stdio.h>

int moduloOperator(int, int);
int congruence(int, int, int);

int main(void) {
  int a, b, n;
  scanf("%d%d%d", &a, &b, &n);

  printf("a mod n = %d\n", moduloOperator(a, n));
  if (congruence(a, b, n)) {
    printf("%d and %d are congruent modulo %d\n", a, b, n);
  } else {
    printf("%d and %d are not congruent modulo %d\n", a, b, n);
  }

  return 0;
}

int moduloOperator(int x, int n) {
  return x % n;
}

int congruence(int x, int y, int n) {
  return x % n == y % n;
}
