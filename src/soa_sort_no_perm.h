#ifndef SOASORTNOPERM_H
#define SOASORTNOPERM_H
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
namespace soa_sort_no_perm {
namespace {

  // Base case for swap parameter packing.
  template <class Iterator>
  void swap(int i, int j, Iterator it)
  {
    std::iter_swap(it + i, it + j);
  }

  template <class Iterator, class... Iterators>
  void swap(int i, int j, Iterator it, Iterators... args)
  {
    std::iter_swap(it + i, it + j);
    swap(i, j, args...);
  }

  template <class Iterator, typename Compare, class... Iterators>
  int partition(Iterator it, int lo, int hi, Compare cmp, Iterators... args)
  {
    int pivot = *(it + hi);
    int i = lo;
    for (int j = lo; j < hi; j++) {
      if (cmp(*(it + j), pivot)) {
        swap(i, j, it, args...);
        i += 1;
      }
    }
    swap(i, hi, it, args...);

    return i;
  }
  template <class Iterator, typename Compare, class... Iterators>
  void quick_sort(Iterator list, int lo, int hi, Compare cmp, Iterators... args)
  {
    if (lo < hi) {
      int p = partition(list, lo, hi, cmp, args...);
      quick_sort(list, lo, p - 1, cmp, args...);
      quick_sort(list, p + 1, hi, cmp, args...);
    }
  }
} // namespace

// Sort the elements in range [first, last) with a custom comparator.
//
// First and last determine the range of elements to sort.
// The value of the elements from [first, last) determine the permutation
//
// The args are iterators which point to starting point where the permutation will be applied.
template <class Iterator, typename Compare, class... Iterators>
void sort_cmp(
    Iterator first, Iterator last,
    Compare cmp,
    Iterators... args)
{
  int hi = std::distance(first, last) - 1;
  quick_sort(first, 0, hi, cmp, args...);
}

// Sort the elements in range [first, last) with a custom comparator.
//
// First and last determine the range of elements to sort.
// The value of the elements from [first, last) determine the permutation
//
// The args are iterators which point to starting point where the permutation will be applied.
template <class Iterator, class... Iterators>
void sort(Iterator first, Iterator last, Iterators... args)
{
  auto cmp = [](const decltype(*first)& a, const decltype(*first)& b) {
    return a < b;
  };

  sort_cmp(first, last, cmp, args...);
}

} // namespace soa_sort_no_perm
#endif // SOASORTNOPERM_H
