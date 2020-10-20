//
// Created by User on 14/10/2020.
//

#include "Detail/abstract_command.h"

#include <string>
#include <utility>

#include "Detail/cli_exceptions.h"

namespace cli {

  using namespace std::literals;

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

  std::size_t AbstractCommand::numArguments() const noexcept {
    return param_names_.size();
  }

  Menu*
  AbstractCommand::execute(std::vector<std::string>::const_iterator first_param,
                           std::vector<std::string>::const_iterator end_param,
                           std::istream& is, std::ostream& os) const {
    if (auto given_args {end_param - first_param};
        given_args != static_cast<int>(numArguments())) {
      throw UserError {
          "'"s + name_ + "' expects exactly " + std::to_string(numArguments()) +
          " arguments, was given " + std::to_string(given_args) + "."};
    }

    return executeImpl(first_param, end_param, is, os);
  }

} // namespace cli