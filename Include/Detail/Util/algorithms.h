//
// Created by User on 16/10/2020.
//

#ifndef MY_LIB_ALGORITHMS_H
#define MY_LIB_ALGORITHMS_H

#include <algorithm>

namespace util {

  template<typename InIter, typename OutIter, typename Func>
  void split_transform(InIter in_first, InIter in_last,
                       const typename InIter::value_type& split_val,
                       OutIter out_first, Func func) {
    auto is_split_val = [&split_val](const auto& val) {
      return val == split_val;
    };
    in_first = std::find_if_not(in_first, in_last, is_split_val);

    while (in_first != in_last) {
      auto block_end {std::find_if(in_first, in_last, is_split_val)};

      *out_first = func(in_first, block_end);
      ++out_first;

      in_first = block_end;
      in_first = std::find_if_not(in_first, in_last, is_split_val);
    }
  }

} // namespace util

#endif // MY_LIB_ALGORITHMS_H
