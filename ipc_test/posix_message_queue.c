#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>
int main() {
  struct mq_attr attr;
  attr.mq_msgsize = 1024;
  attr.mq_maxmsg = 10;

  int mqid = mq_open("/mymsg", O_RDWR | O_CREAT, 0666, &attr);
  char buf[attr.mq_msgsize];
  if (fork()) {
    int n = mq_receive(mqid, buf, attr.mq_msgsize, NULL);
    write(STDOUT_FILENO, buf, n);
  } else {
    char msg[] = "hello\n";
    mq_send(mqid, msg, sizeof(msg), 0);
  }
}