#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_alrm(int signo);
int main(void)
{
  signal(SIGALRM,sig_alrm);
  system("date");
  alarm(20);
  sleep(5);
  printf("%d\n",alarm(5));
  pause();
}

static void sig_alrm(int signo){
  system("date");
  return;
}
