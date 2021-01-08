// Copyright 2018 Your Name <your_email>

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

