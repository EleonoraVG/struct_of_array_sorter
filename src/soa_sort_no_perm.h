#ifndef SOASORTNOPERM_H
#define SOASORTNOPERM_H
#include <functional>

namespace soa_sort_no_perm {
namespace {
  constexpr int MIN_N_QUICKSORT = 32;

  // Base case for parameter packing of swap.
  template <class Iterator, class IteratorDiff>
  void swap(IteratorDiff i, IteratorDiff j, Iterator it)
  {
    std::iter_swap(it + i, it + j);
  }

  // apply the swap to all args.
  template <class Iterator, class IteratorDiff, class... Iterators>
  void swap(IteratorDiff i, IteratorDiff j, Iterator it, Iterators... args)
  {
    std::iter_swap(it + i, it + j);
    swap(i, j, args...);
  }

  template <class Iterator, class IteratorDiff, typename Compare, class... Iterators>
  auto partition(Iterator it, IteratorDiff lo, IteratorDiff hi, Compare cmp, Iterators... args)
  {
    auto pivot = *(it + hi);
    auto i = lo;
    for (auto j = lo; j < hi; j++) {
      if (cmp(*(it + j), pivot)) {
        swap(i, j, it, args...);
        i += 1;
      }
    }
    swap(i, hi, it, args...);

    return i;
  }

  template <class Iterator, class IteratorDiff, typename Compare, class... Iterators>
  void insertion_sort(Iterator list, IteratorDiff lo, IteratorDiff hi, Compare cmp, Iterators... args)
  {
    for (auto i = lo + 1; i < hi; i++)
    {
	  auto curItem = list + i;
      std::rotate(std::upper_bound(list + lo, curItem, *curItem), curItem, curItem + 1);
    }
  }

  template <class Iterator, class IteratorDiff, typename Compare, class... Iterators>
  void quick_sort(Iterator list, IteratorDiff lo, IteratorDiff hi, Compare cmp, Iterators... args)
  {
    if (lo < hi) {
      if (hi - lo < MIN_N_QUICKSORT)
      {
        insertion_sort(list, lo, hi, cmp, args...);
        return;
      }

      auto p = partition(list, lo, hi, cmp, args...);
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
  using IteratorDiff = typename std::iterator_traits<Iterator>::difference_type;
  IteratorDiff lo = 0;
  IteratorDiff hi = std::distance(first, last) - 1;
  quick_sort(first, lo, hi, cmp, args...);
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
