// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include "./AnimatedObject.h"

AnimatedCircle::AnimatedCircle() {
  _angle = 0;
}

void AnimatedCircle::animationMove() {
  // draw circle with this values, copied from lecture example
  _oldPosX = _posX;
  _oldPosY = _posY;
  _posX = _centerX + static_cast<int>(_radius * cos(_angle));
  _posY = _centerY + static_cast<int>(2 * _radius * sin(_angle));
  _angle += 0.02 * _speed;
}


