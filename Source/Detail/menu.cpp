//
// Created by User on 14/10/2020.
//

#include "Detail/menu.h"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace cli {

  Menu::Menu(const std::string& name) :
      GenericCommand(
          name, {}, [](std::istream&, std::ostream&) {}, ""),
      commands_() {}

  Menu::Menu(const Menu& original) :
      GenericCommand(original), commands_([&original] {
        auto commands_copy {std::vector<std::unique_ptr<AbstractCommand>>(
            original.commands_.size())};
        std::transform(original.commands_.cbegin(), original.commands_.cend(),
                       commands_copy.begin(), [](const auto& command_ptr) {
                         return command_ptr->clone();
                       });
        return commands_copy;
      }()) {}

  Menu::Menu(Menu&&) noexcept = default;
  Menu::~Menu() noexcept      = default;

  Menu* Menu::executeImpl(std::vector<std::string>::const_iterator first_param,
                          std::vector<std::string>::const_iterator end_param,
                          std::istream& is, std::ostream& os) const {
    arg_handler_->handle(first_param, end_param, is, os);
    return const_cast<Menu*>(this);
  }

  Menu&& Menu::add(AbstractCommand&& command) && {
    if (std::find_if(commands_.begin(), commands_.end(),
                     [&command](const auto& cmd_ptr) {
                       return (cmd_ptr->name() == command.name());
                     }) != commands_.end()) {
      throw IllegalOverload {name_, command.name()};
    }

    commands_.emplace_back(std::move(command).toUnique());
    return std::move(*this);
  }

  AbstractCommand* Menu::findCommand(const std::string& name) const {
    auto it {std::find_if(
        commands_.begin(), commands_.end(),
        [&name](const auto& cmd_ptr) { return (cmd_ptr->name() == name); })};

    if (it == commands_.end()) return nullptr;
    return it->get();
  }

  const std::vector<std::unique_ptr<AbstractCommand>>&
  Menu::commands() const noexcept {
    return commands_;
  }

} // namespace cli