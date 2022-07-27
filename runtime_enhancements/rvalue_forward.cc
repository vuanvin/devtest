#include <bits/stdc++.h>
using namespace std;

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
    a.str_ = "null";
  }

  std::string str() { return str_; }

 private:
  std::string str_;
  int data_;
};

int main() {
  A x("I am x.", 10);
  A y(x);
  A z(std::move(x));
  cout << x.str() << endl;

  int a = 20;
  int &&b = 10;
  int &c = b;

  b = a;
  a = 100;
  cout << b << " " << a << endl;

  c = 111;
  cout << b << " " << a << endl;
}