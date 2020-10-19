//
// Created by User on 19/10/2020.
//

#ifndef CLI_SIMPLE_COMMAND_H
#define CLI_SIMPLE_COMMAND_H

#include <utility>

#include "generic_command.h"

namespace cli {

  class SimpleCommand final : public GenericCommand<SimpleCommand> {
  public:
    SimpleCommand() = delete;
    template<typename F>
    SimpleCommand(const std::string&                 name,
                  std::initializer_list<std::string> param_names, F&& f,
                  const std::string& description) :
        GenericCommand(name, param_names, std::forward<F>(f), description) {
    } // TODO count params

    SimpleCommand(const SimpleCommand&);
    SimpleCommand(SimpleCommand&&) noexcept;
    SimpleCommand& operator=(const SimpleCommand&) = delete;
    SimpleCommand& operator=(SimpleCommand&&) = delete;

    ~SimpleCommand() noexcept override;

    [[nodiscard]] Menu*
    execute(std::vector<std::string>::const_iterator first_param,
            std::vector<std::string>::const_iterator end_param,
            std::istream& is, std::ostream& os) const override;
  };

} // namespace cli

#endif // CLI_SIMPLE_COMMAND_H
