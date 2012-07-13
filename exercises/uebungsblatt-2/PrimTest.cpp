// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Prim.h"

// Check correctness of the isPrim function on a few examples.
TEST(PrimTest, isPrim) {
    ASSERT_FALSE(isPrim(-1));
    ASSERT_FALSE(isPrim(0));
    ASSERT_FALSE(isPrim(1));
    ASSERT_TRUE(isPrim(7));
    ASSERT_TRUE(isPrim(26099));
    ASSERT_TRUE(isPrim(2));
    ASSERT_FALSE(isPrim(25));
    ASSERT_FALSE(isPrim(22222));
}

// Main program runs all tests.
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
