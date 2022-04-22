#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

mqd_t mqid;
char buf[8192];
struct sigevent sigev;

static void handler(int signo) {
  mq_notify(mqid, &sigev);
  mq_receive(mqid, buf, 8192, NULL);
  printf("message: %s\n", buf);
}

int main() {
  signal(SIGUSR1, handler);
  mqid = mq_open("/abc", O_RDWR | O_CREAT, 0666, NULL);
  sigev.sigev_notify = SIGEV_SIGNAL;
  sigev.sigev_signo = SIGUSR1;
  mq_notify(mqid, &sigev);
  if (fork()) {
    while (1) {
      sleep(1);
    }
  } else {
    mqid = mq_open("/abc", O_WRONLY | O_CREAT);
    while (1) {
      mq_send(mqid, "hello world", 12, 0);
      sleep(2);
    }
  }
}