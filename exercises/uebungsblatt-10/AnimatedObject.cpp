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
AnimatedObject::AnimatedObject() {
  // check terminal size
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  // set random position, size and speed
  // get integer by multiply with 10
  _centerX = static_cast<int>((w.ws_row / 2) + (drand48() * 10));
  _centerY = static_cast<int>((w.ws_col / 2) + (drand48() * 10));
  _posX = _centerX;
  _posY = _centerY;
  _oldPosX = _posX;
  _oldPosY = _posY;
  // set random radius and speed, plus 1 for the 0 case,
  // which is only used by circle and square objects
  _radius = static_cast<int>(drand48() * 10 + 1);
  _speed = drand48() * 20 + 1;
}

// ____________________________________________________________________________
void AnimatedObject::animationStep() {
  this->animationMove();
  this->animationDraw();
}

// ____________________________________________________________________________
void AnimatedObject::animationDraw() {
  // copied from the lecture example
  if (_posX != _oldPosX || _posY != _oldPosY) {
    // overwrites the last charaters with an space
    if (_oldPosX > 0 && _oldPosY > 0) {
      printf("\x1b[%d;%dH ", _oldPosX, _oldPosY);
    }
    printf("\x1b[%d;%dH\x1b[7m \x1b[0m", _posX, _posY);
    fflush(stdout);
  }
}
