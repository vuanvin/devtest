#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

void print_time() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(localtime(&in_time_t), "%Y-%m-%d %X");
  std::cout << "now is: " << ss.str() << std::endl;
}

void sleep_fn() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "[thread-" << std::this_thread::get_id() << "] is waking up"
            << std::endl;
}

void loop_fn() {
  for (int i = 0; i < 100; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "[thread-" << std::this_thread::get_id() << "] print: " << i
              << std::endl;
  }
}

int main() {
  print_time();
  std::thread t1(sleep_fn);
  std::thread t2(loop_fn);

  t1.join();
  t2.detach();

  print_time();
  return 0;
}