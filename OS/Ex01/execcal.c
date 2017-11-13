#include <unistd.h>

int main() {
  execl("/usr/bin/cal", "cal", NULL);
  return 0;
}
