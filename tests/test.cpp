// Copyright 2020 Burylov Denis <burylov01@mail.ru>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(Cache, Cache) {
  EXPECT_TRUE(true);
  direct_();
  std::cout << std::endl;
  back_();
  std::cout << std::endl;
  random_();
}
