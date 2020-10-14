//
// Created by User on 14/10/2020.
//

#ifndef CLI_MENU_H
#define CLI_MENU_H

#include <string>

#include "generic_command.h"

namespace cli {

  class Menu final : public GenericCommand<Menu> {
  public:
    Menu() = delete;
    Menu(std::string name);
    Menu(const Menu&);
    Menu(Menu&&) noexcept;
    Menu& operator=(const Menu&);
    Menu& operator=(Menu&&) noexcept;

    ~Menu() noexcept override;
  };

} // namespace cli

#endif // CLI_MENU_H
