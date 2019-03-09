#include "soa_sort.h"
#include <algorithm>
#include <iostream>
#include <vector>
template <class T>
void print_vector(const std::vector<T>& vector)
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
  std::vector<char> char_vector = { 'd', 'c', 'f', 'e', 'a', 'b' };
  soa::SoaSort::sort<decltype(test.begin())>(
      test.begin(), test.end(), second_vector.begin(), third_vector.begin(),
      char_vector.begin());

  // Print the sorted test vector and the other 2 dependent_vectors.
  std::cout << "first vector: "
            << "\n";
  print_vector(test);
  std::cout << "dependent_vectors: "
            << "\n";
  print_vector(second_vector);
  print_vector(third_vector);
  print_vector(char_vector);
  return 0;
}
