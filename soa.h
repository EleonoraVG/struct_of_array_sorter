#include <algorithm>
#include <iostream>
#include <vector>
namespace soa {
template <class T, class RandomIt>
class Soa {
  public:
  RandomIt compare_begin;

  Soa(RandomIt begin)
      : compare_begin(begin)
  {
  }

  // Algorithm copied from :
  // https://blogs.msdn.microsoft.com/oldnewthing/20170102-00/?p=95095
  void apply_permutation(std::vector<int> helper, RandomIt first)
  {
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

  void sort(RandomIt first, RandomIt last,
      std::vector<std::pair<RandomIt, RandomIt>> dependent_iterators)
  {

    // Create a helper array with a length the same as the distance between
    // first and last iterators, where the values range from 0 to
    // distance(first,last)-1 (included).
    std::vector<T> helper = {};

    typename std::vector<T>::iterator pos;
    int i = 0;
    for (pos = first; pos != last; pos++, i++) {
      helper.push_back(i);
    }

    // Sort the helper array using the compare value that uses the values from
    // compare_array in the helper compare function.;
    std::sort(helper.begin(), helper.end(), [this](const T& a, const T& b) {
      return *(compare_begin + a) < *(compare_begin + b);
    });

    // std::cout << "helper array"
    //<< "\n";
    // for (auto elem : helper) {
    // std::cout << elem << "\n";
    //}

    // The helper array now gives the permutation of the lists that should
    // be applied to all things we want to sort.
    apply_permutation(helper, first);
    for (auto it : dependent_iterators) {
      apply_permutation(helper, it.first);
    }
  }
};

template <class T, class RandomIt>
Soa<T, RandomIt> make_soa(RandomIt first, RandomIt last, T val)
{
  return Soa<T, RandomIt>(first);
}

} // namespace soa
