#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* xc(void* arg) {
  char* c = (char*)arg;
  printf("参数%s \n", c);
  int i = 0;
  for (; i < 10; i++) {
    printf("循环%d\n", i);
    if (i == 5) {
      pthread_exit(1090000000);
    }
  }
  return 100000222;
}

void main() {
  pthread_t tid;
  pthread_create(&tid, NULL, xc, "线程！！！！");

  void* status;
  pthread_join(tid, &status);
  printf("返回%d\n", (int)status);
}
