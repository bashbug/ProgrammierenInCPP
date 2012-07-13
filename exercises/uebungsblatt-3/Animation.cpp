// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include "./Animation.h"

int posX = 1;
int posY = 1;
int dirX = 1;
int dirY = 1;
int maxX = 43;
int maxY = 124;

void flyingOwl() {
  // Move the owl in the given direction.
  posX += dirX;
  posY += dirY;
  // Reflect the owl on the terminal boarders.
  if (posX >= maxX) dirX = -dirX;
  if (posX == 1) dirX = dirX * -1;
  if (posY >= maxY-9) dirY = -dirY;  // -9 for the 9 chars of __(*,*)^^
  if (posY == 1) dirY = dirY * -1;
}
