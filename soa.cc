#include "soa.h"
#include <algorithm>
#include <iostream>
#include <vector>
int main()
{
  std::vector<int> test = { 4, 3, 6, 5, 1, 2 };
  std::cout << "test start:"
            << "\n";
  for (auto elem : test) {
    std::cout << elem << "\n";
  }

  auto soa = soa::make_soa(test.begin(), test.end(), *(test.begin()));
  soa.sort(test.begin(), test.end());
  std::cout << "test result:"
            << "\n";
  for (auto elem : test) {
    std::cout << elem << "\n";
  }
  return 0;
}
