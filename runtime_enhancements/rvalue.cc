#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class A {
 public:
  A() { std::cout << "A()" << std::endl; }
  A(const std::string str, int data) : str_(std::move(str)), data_(data) {
    std::cout << "A(str, data)" << std::endl;
  }
  A(const A &a) : str_(a.str_), data_(a.data_) {
    std::cout << "A(const A &a)" << std::endl;
  }
  A(A &&a) : str_(a.str_), data_(a.data_) {
    std::cout << "rvalue A(A && a)" << std::endl;
  }

  std::string str() { return str_; }

 private:
  std::string str_;
  int data_;
};

int main() {
  std::vector<A> vec;
  A a1;
  A a2("good", 12);
  A a3(a1);
  A a4 = std::move(a3);

  std::cout << std::endl;

  std::cout << "------ emplace_back ---------------" << std::endl;
  vec.emplace_back(a3);
  // vec.emplace_back(std::move(a3));

  std::cout << "------push_back ------------" << std::endl;
  vec.push_back(std::move(a2));
  std::cout << a2.str() << std::endl;

  return 0;
}
