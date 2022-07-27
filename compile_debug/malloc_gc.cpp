#include <exception>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
  int *p = nullptr;
  for (int i = 0; i < 1000; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    p = new int[i+10];

    for (int j = 0; j < i+10; j++) {
      *(p+j) = j;
    }

    std::cout << "success: " << i << std::endl;
  }

  delete p;

  return 0;
}
