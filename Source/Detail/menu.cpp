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

  Menu::Menu(std::string name) : GenericCommand(std::move(name)), commands_() {}
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
  Menu& Menu::operator        =(const Menu& rhs) {
    auto copy {rhs};
    swap(copy);
    return *this;
  }
  Menu& Menu::operator=(Menu&&) noexcept = default;
  Menu::~Menu() noexcept                 = default;

  void Menu::swap(Menu& other) noexcept {
    GenericCommand::swap(other);
    commands_.swap(other.commands_);
  }

  Menu& Menu::add(AbstractCommand&& command) {
    commands_.emplace_back(std::move(command).clone());
    return *this;
  }

  void swap(Menu& lhs, Menu& rhs) noexcept { lhs.swap(rhs); }

} // namespace cli