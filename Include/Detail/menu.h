//
// Created by User on 14/10/2020.
//

#ifndef CLI_MENU_H
#define CLI_MENU_H

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "generic_command.h"

namespace cli {

  class Menu final : public GenericCommand<Menu> {
  public:
    Menu() = delete;
    explicit Menu(std::string name);
    Menu(const Menu&);
    Menu(Menu&&) noexcept;
    Menu& operator=(const Menu&);
    Menu& operator=(Menu&&) noexcept;

    ~Menu() noexcept override;

    void swap(Menu&) noexcept;

    Menu& add(AbstractCommand&& submenu);

  private:
    std::vector<std::unique_ptr<AbstractCommand>> commands_;
  };

  void swap(Menu& lhs, Menu& rhs) noexcept;

} // namespace cli

#endif // CLI_MENU_H
