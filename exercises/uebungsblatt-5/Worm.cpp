// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "./TerminalSize.h"
#include "./Worm.h"

// ______________________________________________________________
const char* _wormString;
// ______________________________________________________________
int _wormStringLength;
// ______________________________________________________________
int* _posX;
int* _posY;
// ______________________________________________________________
int _dirX;
int _dirY;
// ______________________________________________________________
int Worm::_maxX;
int Worm::_maxY;
// ______________________________________________________________
float _probability;
// ______________________________________________________________
int _quantity;

// ______________________________________________________________
Worm::Worm() {
  _dirX = drand48() < 0.5 ? -1 : 1;
  _dirY = drand48() < 0.5 ? -1 : 1;
}

// ______________________________________________________________
Worm::~Worm() {
  delete[] _posX;
  delete[] _posY;
}

// ______________________________________________________________
void Worm::getTerminalSize() {
  TerminalSize myTerminalSize;
  _maxX = myTerminalSize.get_row();
  _maxY = myTerminalSize.get_col();
}

// ______________________________________________________________
void Worm::setWormString(const char* wormString) {
  _wormString = wormString;
  _wormStringLength = strlen(wormString);
}

// ______________________________________________________________
void Worm::setTurnProbability(const float probability) {
  // Randomnumber for probability.
  double rnum = drand48();
  if (rnum <= 2*(probability/100)/3) {
    turnWorm(false);
  }
  if (rnum <= (probability/100)/3) {
    turnWorm(true);
  }
}

// ______________________________________________________________
void Worm::initializeWorm() {
  // Dynamic memory allocation
  _posX = new int[_wormStringLength];
  _posY = new int[_wormStringLength];
   // Set memebervariables with default value.
  for (int i = 0; i < _wormStringLength; i++) {
    _posX[i] = (_maxX / 2);
    _posY[i] = (_maxY - _wormStringLength) / 2+i;
  }
}

// ______________________________________________________________
void Worm::drawWorm() {
  for (int i = _wormStringLength - 1; i >= 0; i--) {
    const char* style = "\x1b[1;32m\x1b[2m";
    if (i == 0) {
      style = "\x1b[1;31m\x1b[2m";
    } else if (i == 1) {
      style = "\x1b[1;33m\x1b[1m";
    }
    printf("%s\x1b[%d;%dH%c", style, _posX[i], _posY[i],
      _wormString[i]);
  }
}

// ______________________________________________________________
void Worm::moveWorm() {
  // Dynamic memory allocation
  int* tempPosX = new int[_wormStringLength];
  int* tempPosY = new int[_wormStringLength];

  for (int i = 0; i < _wormStringLength; i++) {
    tempPosX[i] = _posX[i];
    tempPosY[i] = _posY[i];
  }

  // Shift the position after wormhead for dynamic moving.
  for (int i = 1; i < _wormStringLength; i++) {
    _posX[i] = tempPosX[i-1];
    _posY[i] = tempPosY[i-1];
  }

  // Reflection at the
  // bottom
  if (_posX[0] + _dirX >= _maxX) _dirX = -1;
  // top
  if (_posX[0] + _dirX <= 1) _dirX = 1;
  // right border
  if (_posY[0] + _dirY >= _maxY) _dirY = -1;
  // left border
  if (_posY[0] + _dirY <= 1) _dirY = 1;

  _posY[0] += _dirY;
  _posX[0] += _dirX;
}

// ______________________________________________________________
void Worm::turnWorm(bool turnRight) {
  float newDirX;
  float newDirY;

  // Rotation with normalised rotationmatrix.
  if (turnRight == true) {
    newDirX = (1 / fabs(sqrt(pow(_dirX, 2) + pow(_dirY, 2)))) *
      (_dirX - _dirY);
    newDirY = (1 / fabs(sqrt(pow(_dirX, 2) + pow(_dirY, 2)))) *
      (_dirX + _dirY);
  } else {
    newDirX = (1 / fabs(sqrt(pow(_dirX, 2) + pow(_dirY, 2)))) *
      (_dirX + _dirY);
    newDirY = (1 / fabs(sqrt(pow(_dirX, 2) + pow(_dirY, 2)))) *
      (_dirX - _dirY);
  }
  _dirX = newDirX;
  _dirY = newDirY;
}
