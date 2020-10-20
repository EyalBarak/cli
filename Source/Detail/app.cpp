//
// Created by User on 15/10/2020.
//

#include "Detail/app.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Detail/Util/string_algs.h"
#include "Detail/simple_command.h"

namespace cli {

  const std::string App::Back {"back"};
  const std::string App::Quit {"quit"};
  const std::string App::Help {"help"};

  using namespace std::literals;

  App::App(Menu&& root, std::istream& is, std::ostream& os,
           const std::string& welcome, const std::string& goodbye) :
      root_(std::move(root)),
      is_(is), os_(os), calls_(), welcome_(welcome), goodbye_(goodbye),
      meta_commands_ {
          SimpleCommand {Help,
                         {},
                         [this](std::istream&, std::ostream&) { doHelp(); },
                         "Print this."},
          SimpleCommand {Back,
                         {},
                         [this](std::istream&, std::ostream&) { doBack(); },
                         "Go to previous menu."},
          SimpleCommand {Quit,
                         {},
                         [this](std::istream&, std::ostream&) { doQuit(); },
                         "Quit all."}} {}

  App::App(App&&) = default;

  App::~App() noexcept = default;

  void App::run() {
    doQuit();
    os_ << welcome_ << std::endl;
    calls_.push(&root_);

    doHelp();

    while (!calls_.empty()) {
      prompt();
      std::string buffer {};
      std::getline(is_, buffer);
      auto cmd_line {util::string_split(buffer)};
      if (cmd_line.empty()) continue;

      auto cmd_ptr {calls_.top()->findCommand(cmd_line.front())};
      try {
        if (cmd_ptr != nullptr) {
          auto next_ptr {cmd_ptr->execute(cmd_line.cbegin() + 1,
                                          cmd_line.cend(), is_, os_)};
          if (next_ptr != nullptr) {
            calls_.push(next_ptr);
            doHelp();
          }
        } else {
          metaCommand(cmd_line);
        }
      } catch (const UserError& error) { os_ << error.what() << std::endl; }
    }

    doQuit();
    os_ << goodbye_ << std::endl;
  }

  void App::prompt() {
    assert(!calls_.empty());
    os_ << calls_.top()->name() << "> ";
  }

  void App::metaCommand(const std::vector<std::string>& cmd_line) {
    assert(!cmd_line.empty());

    auto it {std::find_if(meta_commands_.cbegin(), meta_commands_.cend(),
                          [&cmd_line](const auto& cmd) {
                            return (cmd.name() == cmd_line.front());
                          })};

    if (it != meta_commands_.cend()) {
      static_cast<void>(
          it->execute(cmd_line.cbegin() + 1, cmd_line.cend(), is_, os_));
    } else {
      throw UserError {"Unrecognised command '"s + cmd_line.front() +
                       "', type '" + Help + "' for info."};
    }
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

    prompt();
    os_ << std::endl;

    auto print_command = [this](const auto& cmd) {
      os_ << '\t' << cmd.name();
      for (const auto& param : cmd.paramNames())
        os_ << " <" << param << '>';
      os_ << ":\n\t\t" << cmd.description() << "\n";
    };

    for (const auto& cmd_ptr : calls_.top()->commands()) {
      print_command(*cmd_ptr);
    }

    for (const auto& cmd : meta_commands_) {
      print_command(cmd);
    }
  }

} // namespace cli