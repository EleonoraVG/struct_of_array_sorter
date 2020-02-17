#include "../src/soa_sort.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>
#include <array>

namespace {

TEST(SoaSortTest, EmptyIndependentAndEmptyDependent)
{
  std::vector<int> actual_independent = {};
  std::vector<int> actual_dependent = {};

  // Sort
  soa_sort::sort<false, decltype(actual_independent.begin())>(
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
  soa_sort::sort<false>(
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
  soa_sort::sort<false, decltype(std::begin(actual_independent))>(
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
  soa_sort::sort<false, decltype(std::begin(actual_independent))>(
      std::begin(actual_independent), std::end(actual_independent),
      std::begin(actual_dependent_0), std::begin(actual_dependent_1));

  int expected_independent[5] = { 1, 2, 3, 4, 5 };
  int expected_dependent_0[5] = { 5, 4, 3, 2, 1 };
  int expected_dependent_1[5] = { 'a', 'b', 'c', 'd', 'e' };

  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent_0, ::testing::ElementsAreArray(expected_dependent_0));
  ASSERT_THAT(actual_dependent_1, ::testing::ElementsAreArray(expected_dependent_1));
}

TEST(SoaSortTest, TestComparator)
{
  int actual_independent[5] = {  0,  1, 2,  3,  4 };
  int referenced_data[5]    = { 20, 10, 0, 30, 40 };
  int actual_dependent[5]   = {  3,  2, 5,  4,  1 };
  
  // Sort
  soa_sort::sort_cmp<false>(
    std::begin(actual_independent), std::end(actual_independent), 
    [&referenced_data](auto a, auto b)
    {
      return referenced_data[a] < referenced_data[b];
    },
    std::begin(actual_dependent));
  
  int expected_independent[5] = { 2, 1, 0, 3, 4 };
  int expected_dependent[5]   = { 5, 2, 3, 4, 1 };
  
  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent, ::testing::ElementsAreArray(expected_dependent));
}

TEST(SoaSortTest, TestVectorOfArrays)
{
  std::vector<std::array<uint32_t, 2>> actual_independent = 
    { {0, 100}, {1, 101}, {2, 102},  {3, 103},  {4, 104} };
  int referenced_data[5] = { 20, 0, 10, 40, 30 };
  int actual_dependent[5] = { 3, 2, 5,  4, 1 };
  
  // Sort
  soa_sort::sort_cmp<false>(
    std::begin(actual_independent), std::end(actual_independent),
    [&referenced_data](auto a, auto b)
    {
      return referenced_data[a[0]] < referenced_data[b[0]];
    },
    std::begin(actual_dependent));
  
  std::vector<std::array<uint32_t, 2>> expected_independent = 
    { {1, 101}, {2, 102}, {0, 100}, {4, 104}, {3, 103} };
  int expected_dependent[5] = { 2, 5, 3, 1, 4 };
  
  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent, ::testing::ElementsAreArray(expected_dependent));
}

TEST(SoaSortTest, TestPartialSort)
{
  int actual_independent[5] = {  0,  1, 2,  3,  4 };
  int referenced_data[5]    = { 20, 10, 0, 30, 15 };
  int actual_dependent[5]   = {  3,  2, 5,  4,  1 };
  
  // Sort
  soa_sort::sort_cmp<false>(
    std::begin(actual_independent) + 1, std::begin(actual_independent) + 4,
    [&referenced_data](auto a, auto b)
    {
      return referenced_data[a] < referenced_data[b];
    },
    std::begin(actual_dependent) + 1);
  
  int expected_independent[5] = { 0, 2, 1, 3, 4 };
  int expected_dependent[5]   = { 3, 5, 2, 4, 1 };
  
  ASSERT_THAT(actual_independent, ::testing::ElementsAreArray(expected_independent));
  ASSERT_THAT(actual_dependent, ::testing::ElementsAreArray(expected_dependent));
}
} // namespace
