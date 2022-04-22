#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  char *addr =
      mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);

  if (fork()) {
    sleep(1);
    write(STDOUT_FILENO, addr, 1024);
  } else {
    strcpy(addr, "hello world\n");
  }
}