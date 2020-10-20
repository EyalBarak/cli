//
// Created by User on 14/10/2020.
//

#ifndef CLI_ABSTRACT_COMMAND_H
#define CLI_ABSTRACT_COMMAND_H

#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Util/meta.h"
#include "argument_handler.h"
#include "cli_exceptions.h"

namespace cli {

  class Menu;

  class AbstractCommand {
  public:
    AbstractCommand() = delete;

  protected:
    template<typename F>
    AbstractCommand(const std::string&                 name,
                    std::initializer_list<std::string> param_names, F&& f,
                    const std::string& description) :
        name_(name),
        param_names_(param_names), description_(description),
        arg_handler_(makeArgHandler(std::forward<F>(f))) {
      if (param_names.size() !=
          (util::count_arguments(std::forward<F>(f)) - 2)) {
        throw ArgumentLengthError {
            name, param_names.size(),
            (util::count_arguments(std::forward<F>(f)) - 2)};
      }
    }
    AbstractCommand(const AbstractCommand&);
    AbstractCommand(AbstractCommand&&) noexcept;

  public:
    AbstractCommand& operator=(const AbstractCommand&) = delete;
    AbstractCommand& operator=(AbstractCommand&&) = delete;

  public:
    virtual ~AbstractCommand() noexcept;

    [[nodiscard]] virtual std::unique_ptr<AbstractCommand> clone() const = 0;

    [[nodiscard]] virtual std::unique_ptr<AbstractCommand> toUnique() && = 0;

    [[nodiscard]] const std::string&              name() const noexcept;
    [[nodiscard]] const std::vector<std::string>& paramNames() const noexcept;
    [[nodiscard]] const std::string&              description() const noexcept;
    [[nodiscard]] std::size_t                     numArguments() const noexcept;

    [[nodiscard]] Menu*
    execute(std::vector<std::string>::const_iterator first_param,
            std::vector<std::string>::const_iterator end_param,
            std::istream& is, std::ostream& os) const;

  protected:
    std::string                      name_;
    std::vector<std::string>         param_names_;
    std::string                      description_;
    std::unique_ptr<ArgumentHandler> arg_handler_;

    [[nodiscard]] virtual Menu*
    executeImpl(std::vector<std::string>::const_iterator first_param,
                std::vector<std::string>::const_iterator end_param,
                std::istream& is, std::ostream& os) const = 0;
  };

} // namespace cli

#endif // CLI_ABSTRACT_COMMAND_H
