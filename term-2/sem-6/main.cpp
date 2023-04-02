#include <bits/iterator_concepts.h>
#include <concepts>

#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "list.hpp"
#include "vector.hpp"


int main() {
//   std::iterator_traits<T>::value_type;
  static_assert(std::output_iterator<List<int>::iterator, int>);
  static_assert(std::bidirectional_iterator<List<int>::iterator>);

  List<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);
  list.PushBack(4);
  list.PushBack(5);

  for (const auto& i : list) {
    std::cout << i << " ";
  }


//   std::vector<int> a = {1, 2, 3, 4, 5};
//   a.begin();
//   a.end();

//   std::cout << std::find(a.begin(), a.end(), 3) - a.begin() << '\n';

//   auto i = a.cbegin();


//   for (const auto& v : a) {
//     std::cout << v << " ";
//   }
}
// https://www.youtube.com/watch?v=dZ2qXPiTmkY&t=4s Впендюрил 2.0.
