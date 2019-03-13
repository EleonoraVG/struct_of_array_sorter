#include "../src/soa_sort.h"
#include "gmock/gmock.h"
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

  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent, ::testing::ElementsAreArray(expected_dependent));
}

TEST(SoaSortTest, SingleIntIndependentAndSingleIntDependent)
{
  std::vector<int> actual_independent = { 3, 2, 5, 4, 1 };
  std::vector<int> actual_dependent = { 3, 4, 1, 2, 5 };

  // Sort
  soa::SoaSort::sort<>(
      actual_independent.begin(), actual_independent.end(),
      actual_dependent.begin());

  std::vector<int> expected_independent = { 1, 2, 3, 4, 5 };
  std::vector<int> expected_dependent = { 5, 4, 3, 2, 1 };

  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent, ::testing::ElementsAreArray(expected_dependent));
}

TEST(SoaSortTest, Test2IntArrays)
{
  int actual_independent[5] = { 3, 2, 5, 4, 1 };
  int actual_dependent[5] = { 3, 4, 1, 2, 5 };

  // Sort
  soa::SoaSort::sort<decltype(std::begin(actual_independent))>(
      std::begin(actual_independent), std::end(actual_independent),
      std::begin(actual_dependent));

  int expected_independent[5] = { 1, 2, 3, 4, 5 };
  int expected_dependent[5] = { 5, 4, 3, 2, 1 };

  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent, ::testing::ElementsAreArray(expected_dependent));
}

TEST(SoaSortTest, Test2IntArraysOneChar)
{
  int actual_independent[5] = { 3, 2, 5, 4, 1 };
  int actual_dependent_0[5] = { 3, 4, 1, 2, 5 };
  int actual_dependent_1[5] = { 'c', 'b', 'e', 'd', 'a' };

  // Sort
  soa::SoaSort::sort<decltype(std::begin(actual_independent))>(
      std::begin(actual_independent), std::end(actual_independent),
      std::begin(actual_dependent_0), std::begin(actual_dependent_1));

  int expected_independent[5] = { 1, 2, 3, 4, 5 };
  int expected_dependent_0[5] = { 5, 4, 3, 2, 1 };
  int expected_dependent_1[5] = { 'a', 'b', 'c', 'd', 'e' };

  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent_0, ::testing::ElementsAreArray(expected_dependent_0));
  ASSERT_THAT(actual_dependent_1, ::testing::ElementsAreArray(expected_dependent_1));
}
} // namespace
