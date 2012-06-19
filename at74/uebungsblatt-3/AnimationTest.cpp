// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Animation.h"
#include "./TerminalSize.h"

// _____________________________________________________________________________
TEST(AnimationTest, flyingOwl) {
  posX = 1;
  posY = 1;
  flyingOwl();
  ASSERT_EQ(2, posX);
  ASSERT_EQ(2, posY);
  flyingOwl();
  ASSERT_EQ(3, posX);
  ASSERT_EQ(3, posY);

  TerminalSize myTerminalSize;
  maxX = myTerminalSize.get_row();
  maxY = myTerminalSize.get_col();

  // Bottom test
  posX = maxX-1;
  flyingOwl();  // the owl is at the bottom
  ASSERT_EQ(maxX, posX);
  flyingOwl();  // the owl flying back to the top
  ASSERT_EQ(maxX-1, posX);

  // Top test
  posX = 2;
  flyingOwl();  // the owl is at the top
  ASSERT_EQ(1, posX);
  flyingOwl();  // the owl flying back to the bottom
  ASSERT_EQ(2, posX);

  // Right boarder test
  posY = maxY-9-1;
  flyingOwl();  // the owl is at the right boarder
  ASSERT_EQ(maxY-9, posY);
  flyingOwl();  // the owl flying back
  ASSERT_EQ(maxY-9-1, posY);

  // Left boarder test
  posY = 2;
  flyingOwl();  // the owl is at the left boarder
  ASSERT_EQ(1, posY);
  flyingOwl();  // the owl flying back
  ASSERT_EQ(2, posY);
}
