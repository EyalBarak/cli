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
    explicit Menu(const std::string& name);
    Menu(const Menu&);
    Menu(Menu&&) noexcept;
    Menu& operator=(const Menu&) = delete;
    Menu& operator=(Menu&&) = delete;

    ~Menu() noexcept override;

    Menu&& add(AbstractCommand&& submenu) &&;

    [[nodiscard]] AbstractCommand* findCommand(const std::string& name) const;

    [[nodiscard]] const std::vector<std::unique_ptr<AbstractCommand>>&
    commands() const noexcept;

  protected:
    [[nodiscard]] Menu*
    executeImpl(std::vector<std::string>::const_iterator first_param,
                std::vector<std::string>::const_iterator end_param,
                std::istream& is, std::ostream& os) const override;

  private:
    std::vector<std::unique_ptr<AbstractCommand>> commands_;
  };

} // namespace cli

#endif // CLI_MENU_H
