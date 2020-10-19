//
// Created by User on 14/10/2020.
//

#include "Detail/abstract_command.h"

#include <utility>

namespace cli {

  AbstractCommand::AbstractCommand(const AbstractCommand& original) :
      name_(original.name_), param_names_(original.param_names_),
      description_(original.description_),
      arg_handler_(original.arg_handler_->clone()) {}
  AbstractCommand::AbstractCommand(AbstractCommand&&) noexcept = default;
  AbstractCommand::~AbstractCommand() noexcept                 = default;

  const std::string& AbstractCommand::name() const noexcept { return name_; }

  const std::vector<std::string>& AbstractCommand::paramNames() const noexcept {
    return param_names_;
  }

  const std::string& AbstractCommand::description() const noexcept {
    return description_;
  }

} // namespace cli