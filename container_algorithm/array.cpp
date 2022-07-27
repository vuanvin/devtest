#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;
  std::cout << "size: " << v.size() << std::endl;
  std::cout << "capacity: " << v.capacity() << std::endl;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  std::cout << "size: " << v.size() << std::endl;
  std::cout << "capacity: " << v.capacity() << std::endl;

  v.push_back(4);
  v.push_back(5);

  std::cout << "size: " << v.size() << std::endl;
  std::cout << "capacity: " << v.capacity() << std::endl;

  v.clear();
  std::cout << "size: " << v.size() << std::endl;
  std::cout << "capacity: " << v.capacity() << std::endl;

  v.shrink_to_fit();
  std::cout << "size: " << v.size() << std::endl;
  std::cout << "capacity: " << v.capacity() << std::endl;

  constexpr int len = 4;
  std::array<int, len> arr = {1, 2, 3, 4};
  arr.empty();
  arr.size();

  for (auto& i : arr) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::sort(arr.begin(), arr.end(), [](int a, int b) { return b < a; });

  return 0;
}
