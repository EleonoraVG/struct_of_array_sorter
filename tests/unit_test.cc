#include "../src/soa_sort.h"
#include "gtest/gtest.h"
#include <vector>

namespace {

TEST(SoaSortTest, SingleIntVector)
{
  std::vector<int> actual = { 6, 5, 4, 3, 2, 1, 0 };
  soa::SoaSort::sort<decltype(actual.begin())>(actual.begin(), actual.end());
  std::vector<int> expected = { 0, 1, 2, 3, 4, 5, 6 };
  EXPECT_EQ(actual, expected);
}
} // namespace
