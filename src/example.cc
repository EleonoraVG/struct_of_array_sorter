#include "soa_sort.h"
#include <algorithm>
#include <iostream>
#include <vector>
void print_vector(const std::vector<int>& vector)
{
  for (auto elem : vector) {
    std::cout << elem << " ";
  }
  std::cout << '\n';
}

int main()
{
  std::vector<int> test = { 4, 3, 6, 5, 1, 2 };
  std::vector<int> second_vector = { 4, 3, 6, 5, 1, 2 };
  std::vector<int> third_vector = { 1, 2, 3, 4, 5, 6 };
  auto dependent_vectors = { second_vector.begin(), third_vector.begin() };
  soa::SoaSort::sort<decltype(test.begin())>(test.begin(), test.end(),
      dependent_vectors);

  // Print the sorted test vector and the other 2 dependent_vectors.
  std::cout << "first vector: "
            << "\n";
  print_vector(test);
  std::cout << "dependent_vectors: "
            << "\n";
  print_vector(second_vector);
  print_vector(third_vector);
  return 0;
}
