// Copyright 2020 MrShip15 mr.shi15@gmail.ru

#include <gtest/gtest.h>
#include "SelfSharedPtr.hpp"

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(SelfSharedPtr, func1){
  int k = 1000;
  SelfSharedPtr<int> test0(&k);
  ASSERT_EQ(*test0, k);
}

TEST(SelfSharedPtr, funcOperator){
  int k = 1000;
  SelfSharedPtr<int> test0(&k);
  SelfSharedPtr<int> test1 = test0;
  ASSERT_EQ(*test1, k);
}

TEST(SelfSharedPtr, funcCountOfLinks){
  int k = 1000;
  SelfSharedPtr<int> test0(&k);
  SelfSharedPtr<int> test1(test0);
  SelfSharedPtr<int> test2 = test1;
  ASSERT_EQ(test0.useCount(), 3);
}

TEST(SelfSharedPtr, funcSwap){
  int a = 1;
  int b = 2;
  SelfSharedPtr<int> A(&a);
  SelfSharedPtr<int> B(&b);
  B.swap(A);
  ASSERT_EQ(*B, 1);
}

TEST(SelfSharedPtr, funcRvalueOperator){
  int a = 1;
  SelfSharedPtr<int> A(&a);
  SelfSharedPtr<int> B(std::move(A));
  ASSERT_EQ(B.useCount(), 2);
}

TEST(SelfSharedPtr, funcBool){
  SelfSharedPtr<int> A;
  ASSERT_EQ(A, false);
}

TEST(SelfSharedPtr, funcThrow){
  SelfSharedPtr<int> A;
  ASSERT_THROW(*A, std::out_of_range);
}

TEST(Shared_Ptr, IsMoveConstructable){
  EXPECT_TRUE(std::is_move_constructible<SharedPtr<int>>());
  EXPECT_TRUE(std::is_move_constructible<SharedPtr<std::string>>());
  EXPECT_TRUE(std::is_move_constructible<SharedPtr<double>>());
}

TEST(Shared_Ptr, IsMoveAssygnable){
  EXPECT_TRUE(std::is_move_assignable<SharedPtr<int>>());
  EXPECT_TRUE(std::is_move_assignable<SharedPtr<std::string>>());
  EXPECT_TRUE(std::is_move_assignable<SharedPtr<double>>());
