//
// Created by User on 15/10/2020.
//

#ifndef CLI_APP_H
#define CLI_APP_H

#include <iostream>
#include <memory>
#include <stack>
#include <vector>

#include "abstract_command.h"
#include "menu.h"
#include "simple_command.h"

namespace cli {

  class App final {
  public:
    App() = delete;
    App(Menu&& root, std::istream& is, std::ostream& os,
        const std::string& welcome = "WELCOME!!!",
        const std::string& goodbye = "GOODBYE!!!");
    App(const App&) = delete;
    App(App&&);
    App& operator=(const App&) = delete;
    App& operator=(App&&) = delete;
    ~App() noexcept;

    void run();

    static const std::string Back;
    static const std::string Quit;
    static const std::string Help;

  private:
    Menu                       root_;
    std::istream&              is_;
    std::ostream&              os_;
    std::stack<Menu*>          calls_;
    std::string                welcome_;
    std::string                goodbye_;
    std::vector<SimpleCommand> meta_commands_;

    void prompt();

    void metaCommand(const std::vector<std::string>& cmd_line);

    void doBack();
    void doQuit();
    void doHelp();
  };

} // namespace cli

#endif // CLI_APP_H
