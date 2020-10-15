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
    explicit GenericCommand(std::string name) :
        AbstractCommand(std::move(name)) {}
    GenericCommand(const GenericCommand&)     = default;
    GenericCommand(GenericCommand&&) noexcept = default;
    GenericCommand& operator=(const GenericCommand&) = default;
    GenericCommand& operator=(GenericCommand&&) noexcept = default;

    ~GenericCommand() noexcept override = default;

    void swap(GenericCommand& other) { AbstractCommand::swap(other); }

  public:
    [[nodiscard]] std::unique_ptr<AbstractCommand>
    clone() const& override final {
      return std::make_unique<Derived>(static_cast<const Derived&>(*this));
    }

    [[nodiscard]] virtual std::unique_ptr<AbstractCommand>
        clone() && override final {
      return std::make_unique<Derived>(std::move(static_cast<Derived&>(*this)));
    }
  };
} // namespace cli

#endif // CLI_GENERIC_COMMAND_H