#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  mkfifo("/tmp/fifo", S_IFIFO | 0666);  // mkfifo和S_IFIFO在stat.h
  if (fork()) {
    char buf[1024] = "hello\n";
    int fd = open("/tmp/fifo", O_WRONLY);  // open在fcntl.h
    write(fd, buf, 1024);                  // read和write在unistd.h
    close(fd);
  } else {
    char buf[1024];
    int fd = open("/tmp/fifo", O_RDONLY);
    read(fd, buf, 1024);
    write(STDOUT_FILENO, buf, 1024);
    close(fd);
  }
}