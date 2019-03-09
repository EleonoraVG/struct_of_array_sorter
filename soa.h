#include <algorithm>
#include <vector>
namespace soa {
template <class T, class RandomIt>
class Soa {
  public:
  RandomIt compare_begin;

  int helper_compare(const void* a, const void* b)
  {
    int first = *(const int*)a;
    int second = *(const int*)b;
    T compare_first = *(compare_begin + first);
    T compare_second = *(compare_begin + second);
    return compare_first < compare_second;
  }

  void sort(RandomIt first, RandomIt last)
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

    // Set the array to use for sorting as the compare_array.
    compare_begin = first;

    // Sort the helper array using the compare value that uses the values from
    // compare_array in the helper compare function.;
    std::sort(helper.begin(), helper.end(),
        [this](const T& a, const T % b) { return a > b });

    // The helper array now gives the permutation of the lists that should be
    // applied to all things we want to sort.
    for (int i = 0; i < helper.size(); i++) {
      int new_pos = helper[i];
      std::iter_swap(first + i, first + new_pos);
    }
  }
};

template <class T, class RandomIt>
Soa<T, RandomIt> make_soa(RandomIt first, RandomIt last, T val)
{
  return Soa<T, RandomIt>();
}

} // namespace soa
