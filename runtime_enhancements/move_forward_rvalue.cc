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

  void Fn(A<T> &&a) {}
};

template<typename T>
A<T> fr(const A<T>& a) {
  return a;
}

template<typename T>
A<T>&& frr(A<T>& a) {
  return std::move(a);
}


int main() {
  A<string> a("string a");
  cout << a.data << endl;

  auto &&xref = A<string>("string without name one.");
  xref = A<string>("string without name two.");

  // typedef int &A;
  // const A aref = 3;

  int vi = 1;
  const int ci = 2;
  const int *p1 = &vi;
  const int *const p2 = &vi;


  cout << "--------------------" << endl;

  auto b = fr(a);
  auto c = frr<string>(a);

  cout << "--------------------" << endl;
}