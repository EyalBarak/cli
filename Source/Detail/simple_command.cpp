//
// Created by User on 19/10/2020.
//

#include "Detail/simple_command.h"

namespace cli {

  SimpleCommand::SimpleCommand(const SimpleCommand&)     = default;
  SimpleCommand::SimpleCommand(SimpleCommand&&) noexcept = default;
  SimpleCommand::~SimpleCommand() noexcept               = default;

  Menu*
  SimpleCommand::execute(std::vector<std::string>::const_iterator first_param,
                         std::vector<std::string>::const_iterator end_param,
                         std::istream& is, std::ostream& os) const {
    arg_handler_->handle(first_param, end_param, is, os);
    return nullptr;
  }
} // namespace cli