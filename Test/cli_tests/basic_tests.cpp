//
// Created by User on 14/10/2020.
//

#include "gtest/gtest.h"

#include "cli.h"

TEST(NothingTests, FirstTest) { EXPECT_TRUE(true); }

TEST(LinkTests, LinkingWorks) { cli::Menu menu {"word name"}; }