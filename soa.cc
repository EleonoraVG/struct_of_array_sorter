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
  std::vector<int> second_vector = { 4, 3, 6, 5, 1, 2 };
  auto dependent_vectors = { second_vector.begin() };
  auto soa = soa::make_soa(test.begin(), test.end(), *(test.begin()));
  soa.sort(test.begin(), test.end(), dependent_vectors);
  std::cout << "test result:"
            << "\n";

  std::cout << "The array that determined the order:"
            << "\n";
  for (auto elem : test) {
    std::cout << elem << "\n";
  }

  std::cout << "The second array:"
            << "\n";
  for (auto elem : second_vector) {
    std::cout << elem << "\n";
  }
  return 0;
}
