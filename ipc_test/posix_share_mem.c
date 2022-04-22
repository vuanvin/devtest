#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd = shm_open("/shm_open", O_RDWR | O_CREAT, 0666);
  ftruncate(fd, 1024);

  if (fork()) {
    char *addr =
        (char *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sleep(2);
    write(STDOUT_FILENO, addr, 1024);
  } else {
    char *addr =
        (char *)mmap(NULL, 1024, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    strcpy(addr, "hello world\n");
  }
}