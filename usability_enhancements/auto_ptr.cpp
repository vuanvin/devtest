#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i) {
  (*i)++;
}

int main() {
  auto pointer = std::make_shared<int>(10);
  foo(pointer);
  std::cout << *pointer << std::endl;

  return 0;
}
