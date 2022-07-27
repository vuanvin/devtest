#include <iostream>
#include <new>

class A {
 public:
  int f() { return 10; }
  virtual int vf() { return 20; }
};

class B : public A {
 public:
  int vf() { return 21; }
};

A a;
B b;

int main() {
  int n = 0;

  n += a.f();
  n += b.f();

  n *= a.vf();
  n *= b.vf();

  A *p = &b;
  n = p->vf();

  std::cout << n << std::endl;

  return 0;
}
