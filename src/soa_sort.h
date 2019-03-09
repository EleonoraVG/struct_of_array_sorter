#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
namespace soa {
class SoaSort {
  public:
  // Base case.
  template <class Iterator>
  static void sort_0(const std::vector<int>& indices, Iterator it)
  {
    apply_permutation(indices, it);
  }
  template <class Iterator, class... Iterators>
  static void sort_0(const std::vector<int>& indices, Iterator i1,
      Iterators... args)
  {
    apply_permutation(indices, i1);
    sort_0(indices, args...);
  }

  template <class Iterator, class... Iterators>
  static void sort(Iterator first, Iterator last, Iterators... args)
  {
    // Create a helper array to store indices from 0 to
    // distance(first,last)-1 (included).
    std::vector<int> indices(std::distance(first, last));
    std::iota(indices.begin(), indices.end(), 0);

    // Sort the indices using the values found in the first iterator.
    std::sort(indices.begin(), indices.end(),
        [first](const decltype(*indices.begin())& a,
            const decltype(*indices.begin())& b) {
          return *(first + a) < *(first + b);
        });

    // The indices array gives the permutation of the lists that should
    // be applied to all things we want to sort.
    apply_permutation<Iterator>(indices, first);
    sort_0(indices, args...);
  }

  private:
  // disallow instantiating the class.
  SoaSort();
  template <class Iterator>
  static void apply_permutation(std::vector<int> helper, Iterator first)
  {
    // Algorithm from :
    // https://blogs.msdn.microsoft.com/oldnewthing/20170102-00/?p=95095
    for (int i = 0; i < helper.size(); i++) {
      // holds the value at i.
      auto temp { *(first + i) };
      auto current = i;
      while (i != helper.at(current)) {
        auto next = helper.at(current);
        std::iter_swap(first + current, first + next);
        helper.at(current) = current;
        current = next;
      }
      *(first + current) = temp;
      helper.at(current) = current;
    }
  }
};

} // namespace soa
