// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Worm.h"
#include "./TerminalSize.h"

TEST(WormTest, Worm) {
  Worm::_maxX = 100;
  Worm::_maxY = 100;
  const char* wormString;
  wormString = "6chars";
  Worm* worms = new Worm[2];

  ASSERT_TRUE(worms[0]._dirX == 1 || worms[0]._dirX == -1);
  ASSERT_TRUE(worms[0]._dirY == 1 || worms[0]._dirY == -1);
  ASSERT_TRUE(worms[1]._dirX == 1 || worms[1]._dirX == -1);
  ASSERT_TRUE(worms[1]._dirY == 1 || worms[1]._dirY == -1);
}

TEST(WormTest, setWormString) {
  Worm::_maxX = 100;
  Worm::_maxY = 100;
  const char* wormString;
  wormString = "6chars";
  Worm* worms = new Worm[2];

  // Test setWormString function
  worms[0].setWormString(wormString);
  worms[1].setWormString(wormString);

  ASSERT_STREQ("6chars", worms[0]._wormString);
  ASSERT_STREQ("6chars", worms[1]._wormString);
}

TEST(WormTest, setTurnProbability) {
  Worm::_maxX = 100;
  Worm::_maxY = 100;
  const char* wormString;
  wormString = "6chars";
  Worm* worms = new Worm[2];

  worms[0].setWormString(wormString);
  worms[1].setWormString(wormString);
  worms[0].initializeWorm();
  worms[1].initializeWorm();

  /* Test setTurnProbability function
  If probability = 0 than dirX = newDirX. Analog for Y*/
  worms[0].moveWorm();
  worms[1].moveWorm();
  int dirX1 = worms[0]._dirX;
  int dirY1 = worms[0]._dirY;
  int dirX2 = worms[1]._dirX;
  int dirY2 = worms[1]._dirY;
  worms[0].setTurnProbability(0);
  worms[1].setTurnProbability(0);
  int newDirX1 = worms[0]._dirX;
  int newDirY1 = worms[0]._dirY;
  int newDirX2 = worms[1]._dirX;
  int newDirY2 = worms[1]._dirY;
  ASSERT_EQ(dirX1, newDirX1);
  ASSERT_EQ(dirY1, newDirY1);
  ASSERT_EQ(dirX2, newDirX2);
  ASSERT_EQ(dirY2, newDirY2);
}

TEST(WormTest, initializeWorm) {
  Worm::_maxX = 100;
  Worm::_maxY = 100;
  const char* wormString;
  wormString = "6chars";
  Worm* worms = new Worm[2];

  // Test initializeWorm function
  worms[0].setWormString(wormString);
  worms[1].setWormString(wormString);
  worms[0].initializeWorm();
  worms[1].initializeWorm();

  ASSERT_EQ(Worm::_maxX/2, worms[0]._posX[0]);
  ASSERT_EQ((Worm::_maxY-6)/ 2+0, worms[0]._posY[0]);
  ASSERT_EQ(Worm::_maxX/2, worms[1]._posX[0]);
  ASSERT_EQ((Worm::_maxY-6)/ 2+0, worms[1]._posY[0]);
}

TEST(WormTest, moveWorm) {
  Worm::_maxX = 100;
  Worm::_maxY = 100;
  const char* wormString;
  wormString = "6chars";
  Worm* worms = new Worm[2];

  worms[0].setWormString(wormString);
  worms[1].setWormString(wormString);
  worms[0].initializeWorm();
  worms[1].initializeWorm();

  // Test moveWorm function
  worms[0]._posX[0] = Worm::_maxX;
  worms[1]._posX[0] = Worm::_maxX;
  worms[0].moveWorm();
  worms[1].moveWorm();
  ASSERT_NE(Worm::_maxX+1, worms[0]._posX[0]);
  ASSERT_NE(Worm::_maxX+1, worms[1]._posX[0]);
  worms[0]._posX[0] = 1;
  worms[1]._posX[0] = 1;
  worms[0].moveWorm();
  worms[1].moveWorm();
  ASSERT_NE(0, worms[0]._posX[0]);
  ASSERT_NE(0, worms[1]._posX[0]);
  worms[0]._posY[0] = Worm::_maxY;
  worms[1]._posY[0] = Worm::_maxY;
  worms[0].moveWorm();
  worms[1].moveWorm();
  ASSERT_NE(Worm::_maxY+1, worms[0]._posY[0]);
  ASSERT_NE(Worm::_maxY+1, worms[1]._posY[0]);
  worms[0]._posY[0] = 1;
  worms[1]._posY[0] = 1;
  worms[0].moveWorm();
  worms[1].moveWorm();
  ASSERT_NE(0, worms[0]._posY[0]);
  ASSERT_NE(0, worms[1]._posY[0]);
}

TEST(WormTest, turnWorm) {
  Worm::getTerminalSize();
  const char* wormString;
  wormString = "6chars";
  Worm* worms = new Worm[2];

  worms[0].setWormString(wormString);
  worms[1].setWormString(wormString);
  worms[0].initializeWorm();
  worms[1].initializeWorm();

  worms[0]._dirX = 1;
  worms[0]._dirY = 1;
  worms[1]._dirX = 1;
  worms[1]._dirY = 1;
  worms[0].turnWorm(true);
  worms[1].turnWorm(true);
  ASSERT_EQ(0, worms[0]._dirX);
  ASSERT_EQ(1, worms[0]._dirY);
  ASSERT_EQ(0, worms[1]._dirX);
  ASSERT_EQ(1, worms[1]._dirY);
  worms[0]._dirX = 0;
  worms[0]._dirY = 1;
  worms[1]._dirX = 0;
  worms[1]._dirY = 1;
  worms[0].turnWorm(false);
  worms[1].turnWorm(false);
  ASSERT_EQ(1, worms[0]._dirX);
  ASSERT_EQ(-1, worms[0]._dirY);
  ASSERT_EQ(1, worms[1]._dirX);
  ASSERT_EQ(-1, worms[1]._dirY);
  worms[0]._dirX = -1;
  worms[0]._dirY = -1;
  worms[1]._dirX = -1;
  worms[1]._dirY = -1;
  worms[0].turnWorm(true);
  worms[1].turnWorm(true);
  ASSERT_EQ(0, worms[0]._dirX);
  ASSERT_EQ(-1, worms[0]._dirY);
  ASSERT_EQ(0, worms[1]._dirX);
  ASSERT_EQ(-1, worms[1]._dirY);
  worms[0]._dirX = 0;
  worms[0]._dirY = -1;
  worms[1]._dirX = 0;
  worms[1]._dirY = -1;
  worms[0].turnWorm(false);
  worms[1].turnWorm(false);
  ASSERT_EQ(-1, worms[0]._dirX);
  ASSERT_EQ(1, worms[0]._dirY);
  ASSERT_EQ(-1, worms[1]._dirX);
  ASSERT_EQ(1, worms[1]._dirY);
}
