#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> count = {0};

int main() {
  std::thread t1([]() { count.fetch_add(1); });
  std::thread t2([]() {
    count++;
    count += 1;
  });
  t1.join();
  t2.join();
  std::cout << count << std::endl;
  return 0;
}