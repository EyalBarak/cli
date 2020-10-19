//
// Created by User on 15/10/2020.
//

#ifndef CLI_APP_H
#define CLI_APP_H

#include <iostream>
#include <memory>
#include <stack>

#include "abstract_command.h"
#include "menu.h"

namespace cli {

  class App final {
  public:
    App() = delete;
    App(Menu&& root, std::istream& is, std::ostream& os);
    App(const App&) = delete;
    App(App&&);
    App& operator=(const App&) = delete;
    App& operator=(App&&) = delete;
    ~App() noexcept;

    void run();

    static const std::string Back;
    static const std::string Quit;

  private:
    Menu              root_;
    std::istream&     is_;
    std::ostream&     os_;
    std::stack<Menu*> calls_;

    void prompt();

    [[nodiscard]] AbstractCommand*
    findOptionalCommand(const std::string& name) const noexcept;
  };

} // namespace cli

#endif // CLI_APP_H
