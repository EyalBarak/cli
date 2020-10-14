//
// Created by User on 14/10/2020.
//

#include "Detail/abstract_command.h"

#include <utility>

namespace cli {

  AbstractCommand::AbstractCommand(std::string name) : name_(std::move(name)) {}
  AbstractCommand::AbstractCommand(const AbstractCommand&)     = default;
  AbstractCommand::AbstractCommand(AbstractCommand&&) noexcept = default;
  AbstractCommand&
  AbstractCommand::operator=(const AbstractCommand& rhs) = default;
  AbstractCommand&
  AbstractCommand::operator=(AbstractCommand&&) noexcept = default;
  AbstractCommand::~AbstractCommand() noexcept           = default;
} // namespace cli