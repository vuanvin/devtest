#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

char buf[1024];
int main() {
  int fd = open("/tmp/test_flock", O_RDWR | O_CREAT, 0666);
  write(fd, "hello world\n", 13);
  int ret = read(fd, buf, 12);
  printf("%d\n", ret);
  // flock(fd, LOCK_EX);
}