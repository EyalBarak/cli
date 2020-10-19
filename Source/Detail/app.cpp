//
// Created by User on 15/10/2020.
//

#include "Detail/app.h"

#include <memory>
#include <string>
#include <utility>

#include "Detail/Util/string_algs.h"

namespace cli {

  const std::string App::Back {"back"};
  const std::string App::Quit {"quit"};
  const std::string App::Help {"help"};

  App::App(Menu&& root, std::istream& is, std::ostream& os) :
      root_(std::move(root)), is_(is), os_(os), calls_() {}

  App::App(App&&) = default;

  App::~App() noexcept = default;

  void App::run() {
    doQuit();

    calls_.push(&root_);

    doHelp();

    while (!calls_.empty()) {
      prompt();
      std::string buffer {};
      std::getline(is_, buffer);
      auto cmd_line {util::string_split(buffer)};
      if (cmd_line.empty()) continue;

      auto cmd_ptr {findOptionalCommand(cmd_line.front())};
      // TODO errors
      if (cmd_ptr != nullptr) {
        auto next_ptr {
            cmd_ptr->execute(cmd_line.cbegin() + 1, cmd_line.cend(), is_, os_)};
        if (next_ptr != nullptr) {
          calls_.push(next_ptr);
          doHelp();
        }
      } else {
        metaCommand(cmd_line);
      }
    }

    doQuit();
  }

  void App::prompt() {
    assert(!calls_.empty());
    os_ << calls_.top()->name() << "> ";
  }

  AbstractCommand*
  App::findOptionalCommand(const std::string& name) const noexcept {
    assert(!calls_.empty());
    return calls_.top()->findCommand(name);
  }

  void App::metaCommand(const std::vector<std::string>& cmd_line) {
    assert(!cmd_line.empty());
    if (cmd_line.size() != 1) {} // TODO throw
    if (cmd_line.front() == Back) {
      doBack();
    } else if (cmd_line.front() == Quit) {
      doQuit();
    } else if (cmd_line.front() == Help) {
      doHelp();
    } else {
    } // TODO throw
  }

  void App::doBack() {
    calls_.pop();
    if (!calls_.empty()) doHelp();
  }

  void App::doQuit() {
    while (!calls_.empty())
      doBack();
  }

  void App::doHelp() {
    assert(!calls_.empty());
    for (const auto& cmd : calls_.top()->commands()) {
      os_ << cmd->name();
      for (const auto& param : cmd->paramNames())
        os_ << " <" << param << '>';
      os_ << ":\n\t" << cmd->description() << "\n";
    }

    os_ << Help << ":\n\tPrint this.\n";
    os_ << Back << ":\n\tGo to previous menu.\n";
    os_ << Quit << ":\n\tQuit all.\n";
  }

} // namespace cli