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

TEST(BasicMenuTests, MenuCopyAndClone) {
  auto menu {cli::Menu("menu").add(cli::Menu("sub"))};
  EXPECT_EQ(menu.name(), "menu");
  auto copy {menu};
  EXPECT_EQ(copy.name(), menu.name());
  EXPECT_NE(copy.name().c_str(), menu.name().c_str());
  auto clone {copy.clone()};
  EXPECT_EQ(copy.name(), clone->name());
}

TEST(BasicMenuTests, FirstFreeForm) {
  using Mu = cli::Menu;

  cli::App(Mu("menu")
               .add(Mu("sub1").add(Mu("subsub1.1")))
               .add(Mu("sub2").add(Mu("subsub2.1")).add(Mu("subsub2.2")))
               .add(Mu("sub3"))
               .add(Mu("sub4")),
           std::cin, std::cout)
      .run();
}