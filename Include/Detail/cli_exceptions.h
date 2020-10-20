//
// Created by User on 20/10/2020.
//

#ifndef CLI_CLI_EXCEPTIONS_H
#define CLI_CLI_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace cli {

  class ArgumentLengthError final : public std::invalid_argument {
  public:
    ArgumentLengthError() = delete;
    ArgumentLengthError(const std::string& command_name,
                        std::size_t described_args, std::size_t actual_args);
  };

  class IllegalOverload final : public std::invalid_argument {
  public:
    IllegalOverload() = delete;
    IllegalOverload(const std::string& menu_name,
                    const std::string& command_name);
  };

  class UserError : public std::runtime_error {
  public:
    UserError() = delete;
    explicit UserError(const std::string& description);
  };

} // namespace cli

#endif // CLI_CLI_EXCEPTIONS_H
