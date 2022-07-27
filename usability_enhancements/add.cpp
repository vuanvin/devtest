#include <iostream>
#include <type_traits>

template<typename T, typename U>
auto add2(T x, U y) -> decltype(x + y) {
  return x + y;
}

template<typename T, typename U>
auto add3(T x, U y) {
  return x + y;
}

int main() {
  auto w = add2<int, double>(1, 2.0);
  if (std::is_same<decltype(w), double>::value) {
    std::cout << "w is double: ";
  }
  std::cout << w << std::endl;

  auto q = add3<double, int>(1.0, 2);
  std::cout << "q: " << q << std::endl;
}
