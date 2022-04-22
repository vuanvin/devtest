#include <unistd.h>
int main() {
  int pfd[2];  // 定义两个文件描述符
  pipe(pfd);   // 创建管道，并将文件描述符值赋给pfd
  if (fork() == 0) {
    char buf[1024];
    int n = read(pfd[0], buf, 1024);
    write(STDOUT_FILENO, buf, n);
  } else {
    char buf[1024] = "hello\n";
    write(pfd[1], buf, 1024);
  }
}
