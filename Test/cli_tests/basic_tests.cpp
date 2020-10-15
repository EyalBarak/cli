//
// Created by User on 14/10/2020.
//

#include "gtest/gtest.h"

#include "cli.h"

#include <memory>

TEST(NothingTests, FirstTest) { EXPECT_TRUE(true); }

TEST(LinkTests, LinkingWorks) {
  cli::Menu menu {"word name"};
  auto      copy {menu.clone()};
}

TEST(BasicMenuTests, MenuBuilder) {
  auto menu {cli::Menu("menu").add(cli::Menu("sub"))};
  EXPECT_EQ(menu.name(), "menu");
  auto copy {menu};
  EXPECT_EQ(copy.name(), menu.name());
  EXPECT_NE(copy.name().c_str(), menu.name().c_str());
  auto clone {copy.clone()};
  EXPECT_EQ(copy.name(), clone->name());
}