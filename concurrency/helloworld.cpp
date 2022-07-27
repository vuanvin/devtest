#include <iostream>
#include <thread>

int main() {
  std::thread t([]() { std::cout << "hello world." << std::endl; });
  std::cout << "hello main." << std::endl;
  t.join();

  return 0;
}