// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Worm.h"
#include "./TerminalSize.h"

// _____________________________________________________________________________
TEST(WormTest, initializeWorm) {
  TerminalSize myTerminalSize;
  maxX = myTerminalSize.get_row();
  maxY = myTerminalSize.get_col();

  const char* wormString;
  wormString = "6chars";

  // Test initializeWorm function
  initializeWorm(wormString);
  ASSERT_EQ(posX[0], maxX/2);
  ASSERT_EQ(posY[0], (maxY-6)/ 2+0);
}

TEST(WormTest, moveWorm) {
  TerminalSize myTerminalSize;
  maxX = myTerminalSize.get_row();
  maxY = myTerminalSize.get_col();

  const char* wormString;
  wormString = "6chars";

  initializeWorm(wormString);

  // Test moveWorm function
  posX[0] = maxX;
  moveWorm();
  ASSERT_NE(posX[0], maxX+1);
  posX[0] = 1;
  moveWorm();
  ASSERT_NE(posX[0], 0);
  posY[0] = maxY;
  moveWorm();
  ASSERT_NE(posY[0], maxY+1);
  posY[0] = 1;
  moveWorm();
  ASSERT_NE(posY[0], 0);
}

TEST(WormTest, turnWorm) {
  dirX = 1;
  dirY = 1;
  turnWorm(true);
  ASSERT_EQ(dirX, 0);
  ASSERT_EQ(dirY, 1);
  dirX = 0;
  dirY = 1;
  turnWorm(false);
  ASSERT_EQ(dirX, 1);
  ASSERT_EQ(dirY, -1);
  dirX = -1;
  dirY = -1;
  turnWorm(true);
  ASSERT_EQ(dirX, 0);
  ASSERT_EQ(dirY, -1);
  dirX = 0;
  dirY = -1;
  turnWorm(false);
  ASSERT_EQ(dirX, -1);
  ASSERT_EQ(dirY, 1);
}
