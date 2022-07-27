#include <iostream>

int main() {
  int* ptr = new int[10];

  *ptr = 0;

  delete ptr;

  return 0;
}
