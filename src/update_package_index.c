#include <unistd.h>

int main() {
  setuid(0);
  setgid(0);

  execle("/usr/bin/apt-get", "apt-get", "-qq", "update", NULL, NULL);
  return 0;
}
