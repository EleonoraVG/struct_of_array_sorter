#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
namespace soa {
class SoaSort {
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
    apply_permutation(indices, i1);
    sort(indices, args...);
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
    sort(indices, args...);
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
