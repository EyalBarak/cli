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

  App::App(Menu&& root, std::istream& is, std::ostream& os) :
      root_(std::move(root)), is_(is), os_(os), calls_() {}

  App::App(App&&) = default;

  App::~App() noexcept = default;

  void App::run() {
    while (!calls_.empty())
      calls_.pop();

    calls_.push(&root_);

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
        if (next_ptr != nullptr) calls_.push(next_ptr);
      } else if (cmd_line.front() == Back) {
        calls_.pop();
      } else if (cmd_line.front() == Quit) {
        while (!calls_.empty())
          calls_.pop();
      } else {
        // TODO
      }
    }
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

} // namespace cli