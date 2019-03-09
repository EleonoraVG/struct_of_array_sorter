#ifndef SOASORT_H
#define SOASORT_H
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
namespace soa {
class SoaSort {
  static constexpr bool THREADING = false;

  public:
  // Base case.
  template <class Iterator>
  static void sort(const std::vector<int>& indices, Iterator it)
  {
    apply_permutation(indices, it);
  }

  template <class Iterator, class... Iterators>
  static void sort(const std::vector<int>& indices, Iterator i1,
      Iterators... args)
  {
    if (SoaSort::THREADING) {
      std::thread t1(apply_permutation<Iterator>, indices, i1);
      sort(indices, args...);
      t1.join();
    } else {
      apply_permutation(indices, i1);
      sort(indices, args...);
    }
  }

  template <class Iterator, class... Iterators>
  static void sort(Iterator first, Iterator last, Iterators... args)
  {
    auto cmp = [](const decltype(*first)& a, const decltype(*first)& b) {
      return a < b;
    };

    sort_cmp(first, last, cmp, args...);
  }

  template <class Iterator, class... Iterators>
  static void sort_cmp(
      Iterator first, Iterator last,
      std::function<bool(const decltype(*first)& a, const decltype(*first)& b)>
          cmp,
      Iterators... args)
  {
    // Create a helper array to store indices from 0 to
    // distance(first,last)-1 (included).
    std::vector<int> indices(std::distance(first, last));
    std::iota(indices.begin(), indices.end(), 0);

    // Sort the indices using the values found in the first iterator.
    std::sort(indices.begin(), indices.end(),
        [first, cmp](const int& a, const int& b) {
          return cmp(*(first + a), *(first + b));
        });

    // The indices array gives the permutation of the lists that should
    // be applied to all things we want to sort.
    sort(indices, first, args...);
  }

  private:
  // disallow instantiating the class.
  SoaSort();
  template <class Iterator>
  static void apply_permutation(const std::vector<int>& indices,
      Iterator first)
  {

    std::vector<bool> done(indices.size());
    for (std::size_t i = 0; i < indices.size(); i++) {
      if (!done[i]) {
        done[i] = true;
        std::size_t prev_j = i;
        std::size_t j = indices[i];
        while (i != j) {
          std::iter_swap(first + prev_j, first + j);
          done[j] = true;
          prev_j = j;
          j = indices[j];
        }
      }
    }
  }
};

} // namespace soa
#endif
