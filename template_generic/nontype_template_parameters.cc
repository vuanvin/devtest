#include <bits/stdc++.h>
using namespace std;

template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
  return strcmp(p1, p2);
}

int main() {
  auto n = compare("hi", "hello");
  cout << n << endl;
}