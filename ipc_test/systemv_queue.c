#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main() {
  int msgid = msgget(ftok("/tmp/mymsg", 0), IPC_CREAT | 0666);
  struct msgbuf {
    long msgtype;
    char msgtext[1024];
  } sndmsg, rcvmsg;

  if (fork()) {
    int status = msgrcv(msgid, (struct msgbuf*)&rcvmsg, 100, 222, IPC_NOWAIT);
    printf("%s\n", rcvmsg.msgtext);
  } else {
    strcpy(sndmsg.msgtext, "hello");
    sndmsg.msgtype = 222;
    msgsnd(msgid, (struct msgbuf*)&sndmsg, 100, 0);
  }
}