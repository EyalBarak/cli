//
// Created by User on 14/10/2020.
//

#ifndef CLI_ABSTRACT_COMMAND_H
#define CLI_ABSTRACT_COMMAND_H

#include <memory>
#include <string>

namespace cli {

class AbstractCommand {
public:
  AbstractCommand() = delete;

protected:
  explicit AbstractCommand(std::string name);
  AbstractCommand(const AbstractCommand&);
  AbstractCommand(AbstractCommand&&) noexcept;
  AbstractCommand& operator=(const AbstractCommand&);
  AbstractCommand& operator=(AbstractCommand&&) noexcept;

public:
  virtual ~AbstractCommand() noexcept;

  [[nodiscard]] virtual std::unique_ptr<AbstractCommand> clone() const = 0;

protected:
  std::string name;
};

} // namespace cli

#endif // CLI_ABSTRACT_COMMAND_H
