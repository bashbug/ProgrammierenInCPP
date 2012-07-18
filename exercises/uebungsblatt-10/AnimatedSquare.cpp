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
AnimatedSquare::AnimatedSquare() {
  printf("Radius Startwert: %f\n", _radius);
  // starts from the top of the triangle
  _posX = _centerX + _radius;
  _posY = _centerY - _radius;
}

// ____________________________________________________________________________
void AnimatedSquare::animationMove() {
  _oldPosX = static_cast<int>(_posX);
  _oldPosY = static_cast<int>(_posY);
  for (size_t i = 0; i < _speed; i++) {
    // from left bottom to right
    if (_posX == _centerX + _radius
        && _posY < _centerY + _radius) {
      _posY++;
    // from right bottom to right top
    } else if (_posY == _centerY + _radius
        && _posX > _centerX - _radius) {
      _posX--;
    // from right top to left
    } else if (_posX == _centerX - _radius
        && _posY > _centerY - _radius) {
      _posY--;
    // from left top to left bottom
    } else if (_posY == _centerY - _radius
        && _posX < _centerX + _radius) {
      _posX++;
    }
  }
}
