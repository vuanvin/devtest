#include <stdio.h>
#include <sys/socket.h>
int main() {
  int fd[2];
  socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
  if (fork()) {
    char buf[] = "hello";
    write(fd[0], buf, 6);
    read(fd[0], buf, 6);
    printf("%s\n", buf);
  } else {
    char buf[6];
    read(fd[1], buf, 6);
    printf("%s\n", buf);
    buf[1] = 'a';
    write(fd[1], buf, 6);
  }
}