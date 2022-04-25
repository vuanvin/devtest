#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_alrm(int signo);
int main() {
  signal(SIGALRM,sig_alrm);
  system("date");

  alarm(15);
  sleep(5);
  int ret = alarm(5);
  printf("alarm return: %d\n", ret);

  pause();
}

static void sig_alrm(int signo){
  system("date");
  return;
}
