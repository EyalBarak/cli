//
// Created by User on 14/10/2020.
//

#ifndef CLI_GENERIC_COMMAND_H
#define CLI_GENERIC_COMMAND_H

#include <memory>
#include <string>
#include <utility>

#include "abstract_command.h"

namespace cli {
  template<typename Derived> class GenericCommand : public AbstractCommand {
  public:
    GenericCommand() = delete;

  protected:
    template<typename F>
    GenericCommand(const std::string&                 name,
                   std::initializer_list<std::string> param_names, F&& f,
                   const std::string& description) :
        AbstractCommand(name, param_names, std::forward<F>(f), description) {}
    GenericCommand(const GenericCommand&)     = default;
    GenericCommand(GenericCommand&&) noexcept = default;

  public:
    GenericCommand& operator=(const GenericCommand&) = delete;
    GenericCommand& operator=(GenericCommand&&) = delete;

  protected:
    ~GenericCommand() noexcept override = default;

  public:
    [[nodiscard]] std::unique_ptr<AbstractCommand>
    clone() const final override {
      return std::make_unique<Derived>(static_cast<const Derived&>(*this));
    }

    [[nodiscard]] std::unique_ptr<AbstractCommand>
        toUnique() && final override {
      return std::make_unique<Derived>(std::move(static_cast<Derived&>(*this)));
    }
  };
} // namespace cli

#endif // CLI_GENERIC_COMMAND_H
