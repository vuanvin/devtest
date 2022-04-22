#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int shmid = shmget(ftok("/shm_mem", 0), 1024, IPC_CREAT);

  if (fork()) {
    char *shmp = (char *)shmat(shmid, NULL, 0);
    sleep(3);
    write(STDOUT_FILENO, shmp, 1023);
  } else {
    char *shmp = (char *)shmat(shmid, NULL, 0);
    strcpy(shmp, "hello world\n");
  }
}