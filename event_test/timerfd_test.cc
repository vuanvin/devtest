#include <errno.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int epoll_fd;

void do_task() {
  // do something
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void consumer(int id) {
  epoll_event events[1024];
  uint64_t buf;

  while (true) {
    int num = epoll_wait(epoll_fd, events, 1024, 0);
    if (num < 0) {
      perror("epoll_wait");
    }
    for (int i = 0; i < num; i++) {
      auto& event = events[i];
      if (event.events & EPOLLIN) {
        int ret = read(event.data.fd, &buf, sizeof(buf));
        if (ret < 0) {
          perror("read");
        }

        do_task();
        std::clog << "[consumer-" << id << "] has done task" << std::endl;
      }
    }
  }
}

void producer(int id) {
  struct itimerspec its;
  its.it_value.tv_sec = 1;  // initial expiration
  its.it_value.tv_nsec = 0;
  its.it_interval.tv_sec = 1;  // interval
  its.it_interval.tv_nsec = 0;

  auto timer_fd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);

  epoll_event event;
  event.data.fd = timer_fd;
  event.events = EPOLLIN | EPOLLET;

  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &event);

  ret = timerfd_settime(timer_fd, 0, &its, NULL);
}

int main() {
  epoll_fd = epoll_create1(EPOLL_CLOEXEC);
  std::vector<std::thread> ts(12);

  for (int i = 0; i < 8; i++) {
    ts[i] = std::thread(consumer, i);
  }

  for (int i = 8; i < 12; i++) {
    ts[i] = std::thread(producer, i);
  }

  for (auto& t : ts) {
    t.join();
  }
}