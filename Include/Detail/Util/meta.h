//
// Created by User on 19/10/2020.
//

#ifndef MY_LIB_META_H
#define MY_LIB_META_H

#include <type_traits>

namespace util {

  template<typename F, typename R, typename... Args>
  constexpr std::size_t _count_arguments(const F&,
                                         R (F::*)(Args...) const) noexcept {
    static_assert(std::is_invocable_v<F, Args...>);
    return sizeof...(Args);
  }

  template<typename F, typename R, typename... Args>
  constexpr std::size_t _count_arguments(const F&, R (F::*)(Args...)) noexcept {
    static_assert(std::is_invocable_v<F, Args...>);
    return sizeof...(Args);
  }

  template<typename F>
  constexpr std::size_t count_arguments(const F& f) noexcept {
    return _count_arguments(f, &F::operator());
  }

} // namespace util

#endif // MY_LIB_META_H
