//
// Created by User on 20/10/2020.
//

#include "Detail/cli_exceptions.h"

#include <stdexcept>
#include <string>

namespace cli {

  using namespace std::literals;

  ArgumentLengthError::ArgumentLengthError(const std::string& command_name,
                                           std::size_t        described_args,
                                           std::size_t        actual_args) :
      std::invalid_argument("Error: '"s + command_name +
                            "' was constructed with " +
                            std::to_string(described_args) +
                            " named parameters and "
                            "a callable that takes " +
                            std::to_string(actual_args) + " parameters.") {}

  IllegalOverload::IllegalOverload(const std::string& menu_name,
                                   const std::string& command_name) :
      std::invalid_argument("Error: '"s + command_name + "' was added to '" +
                            menu_name + "' more than once.") {}

  UserError::UserError(const std::string& description) :
      std::runtime_error(description) {}

} // namespace cli