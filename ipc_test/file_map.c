#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  if (fork()) {
    int fd1 = open("/tmp/file_map", O_RDWR | O_CREAT, 0666);
    ftruncate(fd1, 1024);
    char *addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    close(fd1);
    write(STDOUT_FILENO, addr, 1024);
  } else {
    int fd2 = open("/tmp/file_map", O_RDWR | O_CREAT, 0666);
    ftruncate(fd2, 1024);
    char *addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    close(fd2);
    strcpy(addr, "hello world\n");
  }
}