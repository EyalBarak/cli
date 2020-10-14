//
// Created by User on 14/10/2020.
//

#include "Detail/menu.h"

#include <string>
#include <utility>

namespace cli {

  Menu::Menu(std::string name) : GenericCommand(std::move(name)) {}
  Menu::Menu(const Menu&)     = default;
  Menu::Menu(Menu&&) noexcept = default;
  Menu& Menu::operator=(const Menu&) = default;
  Menu& Menu::operator=(Menu&&) noexcept = default;
  Menu::~Menu() noexcept                 = default;
} // namespace cli