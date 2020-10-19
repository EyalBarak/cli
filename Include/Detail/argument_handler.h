//
// Created by User on 17/10/2020.
//

#ifndef CLI_ARGUMENT_HANDLER_H
#define CLI_ARGUMENT_HANDLER_H

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace cli {

  class ArgumentHandler {
  protected:
    constexpr ArgumentHandler() noexcept = default;

  protected:
    ArgumentHandler(const ArgumentHandler&)               = default;
    constexpr ArgumentHandler(ArgumentHandler&&) noexcept = default;

  public:
    ArgumentHandler& operator=(const ArgumentHandler&) = delete;
    ArgumentHandler& operator=(ArgumentHandler&&) = delete;
    virtual ~ArgumentHandler() noexcept           = default;

    virtual void handle(std::vector<std::string>::const_iterator first_param,
                        std::vector<std::string>::const_iterator end_param,
                        std::istream& is, std::ostream& os) const = 0;

    [[nodiscard]] virtual std::unique_ptr<ArgumentHandler> clone() const = 0;
  };

  template<typename F, typename...> struct Invoker;

  template<typename F> struct Invoker<F> {
    static void invoke(F f, std::vector<std::string>::const_iterator first,
                       std::vector<std::string>::const_iterator last) {
      assert(first == last);
      f();
    }
  };

  template<typename F, typename Arg, typename... Args>
  struct Invoker<F, Arg, Args...> {
    static void invoke(F f, std::vector<std::string>::const_iterator first,
                       std::vector<std::string>::const_iterator last) {
      assert(first != last);
      std::istringstream current_argument_string {*first};
      Arg                current_argument {};
      current_argument_string >> current_argument;
      if (!current_argument_string.eof()) {} // TODO throw

      auto my_invokable = [&](Args&&... args) {
        f(current_argument, std::forward<Args>(args)...);
      };

      Invoker<decltype(my_invokable), Args...>::invoke(my_invokable, ++first,
                                                       last);
    }
  };

  template<typename F, typename... Args>
  class ConcreteArgumentHandler final : public ArgumentHandler {
    static_assert(
        std::is_invocable_v<F, std::istream&, std::ostream&, Args...>);

  public:
    ConcreteArgumentHandler() = delete;
    explicit constexpr ConcreteArgumentHandler(F&& f) noexcept :
        ArgumentHandler(), f_(std::forward<F>(f)) {}
    ConcreteArgumentHandler(const ConcreteArgumentHandler&) = default;
    constexpr ConcreteArgumentHandler(ConcreteArgumentHandler&&) noexcept =
        default;
    ConcreteArgumentHandler& operator=(const ConcreteArgumentHandler&) = delete;
    ConcreteArgumentHandler& operator=(ConcreteArgumentHandler&&) = delete;
    ~ConcreteArgumentHandler() noexcept override                  = default;

    void handle(std::vector<std::string>::const_iterator first_param,
                std::vector<std::string>::const_iterator end_param,
                std::istream& is, std::ostream& os) const override {
      assert(end_param - first_param == sizeof...(Args));

      auto pass_streams = [&](Args&&... args) {
        f_(is, os, std::forward<Args>(args)...);
      };

      Invoker<decltype(pass_streams), Args...>::invoke(pass_streams,
                                                       first_param, end_param);
    }

    [[nodiscard]] std::unique_ptr<ArgumentHandler> clone() const override {
      return std::make_unique<ConcreteArgumentHandler<F, Args...>>(*this);
    }

  private:
    F f_;
  };

  template<typename F, typename... Args>
  constexpr ConcreteArgumentHandler<F, Args...>
  _createArgHandler(F&& f, void (F::*)(std::istream&, std::ostream&, Args...)
                               const) noexcept {
    return ConcreteArgumentHandler<F, Args...> {std::forward<F>(f)};
  }

  template<typename F> std::unique_ptr<ArgumentHandler> makeArgHandler(F&& f) {
    auto handler {
        _createArgHandler(std::forward<F>(f), &std::decay_t<F>::operator())};
    return std::make_unique<decltype(handler)>(std::move(handler));
  }

} // namespace cli

#endif // CLI_ARGUMENT_HANDLER_H
