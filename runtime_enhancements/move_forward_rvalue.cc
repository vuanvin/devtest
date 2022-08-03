#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct A {
  T data;
  A(T &&d) : data(move(d)) { cout << "A(data)" << endl; }
  A(const A<T> &a) : data(a.data) { cout << "A(const A &a)" << endl; }
  A(A<T> &&a) : data(a.data) { cout << "A(A &&a)" << endl; }

  A &operator=(const A &other) {
    cout << "operator =" << endl;
    return *this;
  }

  virtual ~A() { cout << data << endl; }

  void fn(A<T> &&a) {}
};

template<typename T>
A<T>& fl(A<T>& a) {
  return a;
}

template<typename T>
A<T> f(const A<T>& a) {
  return a;
}

template<typename T>
A<T>&& fr(A<T>& a) {
  return std::move(a);
}

int&& func(int&& p) {
  return std::move(p);
}

A<string> && errfunc() {
  return A<string>("errfunc!!!");
}

int ifunc() {
  return 10;
}

int main() {
  A<string> a("string a");
  cout << a.data << endl;
  auto & dref = a.data;

  auto &&xref = A<string>("string without name one.");
  xref = A<string>("string without name two.");

  // typedef int &A;
  // const A aref = 3;

  int vi = 1;
  const int ci = 2;
  const int *p1 = &vi;
  const int *const p2 = &vi;


  cout << "--------------------" << endl;

  auto b = f(a);
  auto c = fr(a);
  auto & d = fl(a);

  cout << "--------------------" << endl;

  int p = 100;
  int&& w = func(std::move(p));
  w ++;
  cout << w << endl;
  cout << p << endl;

  cout << "--------------------" << endl;

  auto fref = ifunc;
  int tref();
  int tref();
  // tref = ifunc;
  auto & lfref = ifunc;
  auto && rfref = std::move(ifunc);

  cout << fref() << endl;
  cout << rfref() << endl;

  // auto err = errfunc();
  cout << "--------------------" << endl;
}