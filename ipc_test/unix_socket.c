#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  int sfd, cfd;
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, "/tmp/unix_socket");

  if (fork()) {
    char buf[1024];
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sfd, /* backlog */ 5);
    cfd = accept(sfd, NULL, NULL);
    int num = read(cfd, buf, 6);
    write(STDOUT_FILENO, buf, num);
  } else {
    char buf[1024] = "hello\n";
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    connect(sfd, (struct sockaddr*)&addr, sizeof(addr));
    write(sfd, buf, 1024);
  }
}