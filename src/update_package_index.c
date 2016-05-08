#include <unistd.h>

int main() {
  setuid(0);
  setgid(0);
  execl("/usr/bin/apt-get", "apt-get", "-qq", "update", NULL);
  //execl("/usr/bin/apt-get", "apt-get", "update", NULL);
  return 0;
}
