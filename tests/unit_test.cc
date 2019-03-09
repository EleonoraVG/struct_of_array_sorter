#include "../src/soa_sort.h"
#include "gtest/gtest.h"
#include <vector>

namespace {

TEST(SoaSortTest, EmptyIndependentAndEmptyDependent)
{
  std::vector<int> actual_independent = {};
  std::vector<int> actual_dependent = {};

  // Sort
  soa::SoaSort::sort<decltype(actual_independent.begin())>(
      actual_independent.begin(), actual_independent.end(),
      actual_dependent.begin());

  // Verify that nothing happend to both lists.
  std::vector<int> expected_independent = {};
  std::vector<int> expected_dependent = {};

  EXPECT_EQ(actual_independent, expected_independent);
  EXPECT_EQ(actual_dependent, expected_dependent);
}
} // namespace
