// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Prim.cpp"

// Check correctness of the isPrim function on a few examples.
TEST(PrimTest, isPrim) {
    ASSERT_EQ(true, isPrim(7));
    ASSERT_EQ(true, isPrim(26099));
    ASSERT_EQ(false, isPrim(25));
    ASSERT_EQ(false, isPrim(22222));
}

// Main program runs all tests.
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
