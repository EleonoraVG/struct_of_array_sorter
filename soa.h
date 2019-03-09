#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
namespace soa {
template <class T, class Iterator>
class SoaSort {
  public:
  void sort(Iterator first, Iterator last,
      const std::vector<Iterator>& dependent_iterators)
  {
    // Create a helper array to store indices from 0 to
    // distance(first,last)-1 (included).
    int i = 0;
    std::vector<int> indices(std::distance(first, last));
    std::iota(indices.begin(), indices.end(), i++);

    // Sort the indices using the values found in the first iterator.
    std::sort(indices.begin(), indices.end(), [first](const T& a, const T& b) {
      return *(first + a) < *(first + b);
    });

    // The helper array now gives the permutation of the lists that should
    // be applied to all things we want to sort.
    apply_permutation(indices, first);
    for (auto it : dependent_iterators) {
      apply_permutation(indices, it);
    }
  }

  private:
  void apply_permutation(std::vector<int> helper, Iterator first)
  {
    // Algorithm from :
    // https://blogs.msdn.microsoft.com/oldnewthing/20170102-00/?p=95095
    for (int i = 0; i < helper.size(); i++) {
      // holds the value at i.
      auto temp { *(first + i) };
      auto current = i;
      while (i != helper.at(current)) {
        auto next = helper.at(current);
        *(first + current) = *(first + next);
        helper.at(current) = current;
        current = next;
      }
      *(first + current) = temp;
      helper.at(current) = current;
    }
  }
};

template <class T, class Iterator>
SoaSort<T, Iterator> make_soa(Iterator first, Iterator last, T val)
{
  return SoaSort<T, Iterator>();
}

} // namespace soa
