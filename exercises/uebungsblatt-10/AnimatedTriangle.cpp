// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include "./AnimatedObject.h"

// ____________________________________________________________________________
AnimatedTriangle::AnimatedTriangle() {
  // starts from the left corner
  _doublePosX = _centerX - _radius;
  _doublePosY = _centerY;
}

// ____________________________________________________________________________
void AnimatedTriangle::animationMove() {
  _oldPosX = _doublePosX;
  _oldPosY = _doublePosY;
  for (int i = 0; i < _speed; i++) {
    // from left bottom to right
    if (_doublePosY < _centerY + 3/(2* sqrt(3)) * _radius
        && _doublePosX >= _centerX + _radius) {
      _doublePosY += 1;
    // from right bottom to triangle top
    } else if (_doublePosX >_centerX - _radius
        && _doublePosY > _centerY) {
      _doublePosY -= 0.5;
      _doublePosX -= sqrt(3)/2;
    // from triangle top to left bottom
    } else {
      _doublePosY -= 0.5;
      _doublePosX += sqrt(3)/2;
    }
    _posX = _doublePosX;
    _posY = _doublePosY;
  }
}
