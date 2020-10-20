//
// Created by User on 20/10/2020.
//

#include "gtest/gtest.h"

#include "Detail/cli_exceptions.h"
#include "cli.h"

TEST(ArgumentLength, GetsThrown) {
  EXPECT_THROW(cli::SimpleCommand(
                   "e", {}, [](std::istream&, std::ostream&, int) {}, "d"),
               cli::ArgumentLengthError);
  EXPECT_THROW(cli::SimpleCommand(
                   "e", {"a"}, [](std::istream&, std::ostream&) {}, "d"),
               cli::ArgumentLengthError);
  EXPECT_NO_THROW(cli::SimpleCommand(
      "e", {}, [](std::istream&, std::ostream&) {}, "d"));
}

TEST(OverloadError, GetsThrown) {
  EXPECT_THROW(
      cli::Menu("menu").add(cli::Menu("submenu")).add(cli::Menu("submenu")),
      cli::IllegalOverload);
}