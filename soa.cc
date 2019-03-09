#include "soa.h"
#include <algorithm>
#include <iostream>
#include <vector>
int main()
{
  std::vector<int> test = { 4, 3, 6, 5, 1, 2 };
  auto soa = soa::make_soa(test.begin(), test.end(), 4);
  soa.sort(test.begin(), test.end());
  return 0;
}
