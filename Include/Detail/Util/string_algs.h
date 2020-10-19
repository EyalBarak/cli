//
// Created by User on 16/10/2020.
//

#ifndef MY_LIB_STRING_ALGS_H
#define MY_LIB_STRING_ALGS_H

#include <iterator>
#include <string>
#include <vector>

#include "algorithms.h"

namespace util {

  template<typename CharT>
  std::vector<std::basic_string<CharT>>
  string_split(const std::basic_string<CharT>& str, CharT split_val = ' ') {
    std::vector<std::basic_string<CharT>> result {};
    split_transform(str.cbegin(), str.cend(), split_val,
                    std::inserter(result, result.begin()),
                    [](auto first, auto last) {
                      return std::basic_string<CharT>(first, last);
                    });
    return result;
  }

} // namespace util

#endif // MY_LIB_STRING_ALGS_H
