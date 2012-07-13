// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef  UEBUNGSBLATT_5_WORM_H_
#define  UEBUNGSBLATT_5_WORM_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>

class Worm {
 public:
  // Constructor
  Worm();
  FRIEND_TEST(WormTest, Worm);
  // Deconstructor
  ~Worm();
  // Get the terminalsize for static variables maxX and maxY.
  static void getTerminalSize();
  // Set outputstring
  void setWormString(const char* wormString);
  FRIEND_TEST(WormTest, setWormString);
  // Set the probability how often the direction changes.
  void setTurnProbability(const float probability);
  FRIEND_TEST(WormTest, setTurnProbability);
  // Print Worm at a default position and set initial variables.
  void initializeWorm();
  FRIEND_TEST(WormTest, initializeWorm);
  // Set the moving direction.
  void moveWorm();
  FRIEND_TEST(WormTest, moveWorm);
  // Print the worm.
  void drawWorm();
  // The screen dimensions as static variables.
  static int _maxX;
  static int _maxY;

 private:
  void turnWorm(bool turnRight);
  FRIEND_TEST(WormTest, turnWorm);
  // The worm string
  const char* _wormString;
  // The length of the worm string.
  int _wormStringLength;
  // The positions of the characters of the worm string.
  int* _posX;
  int* _posY;
  // The current direction of the worm.
  int _dirX;
  int _dirY;
  // Value how often the direction changes.
  float _probability;
  // Value how many worms should be drawn at the screen.
  int _quantity;
};

#endif  // UEBUNGSBLATT_5_WORM_H_
