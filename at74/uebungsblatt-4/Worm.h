// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef  UEBUNGSBLATT_4_WORM_H_
#define  UEBUNGSBLATT_4_WORM_H_

// The worm string.
extern const char* wormString;
// The length of the worm string.
extern int n;
// The positions of the characters of the worm string.
extern int posX[];
extern int posY[];
// The current direction of the worm.
extern int dirX;
extern int dirY;
// The screen dimensions.
extern int maxX;
extern int maxY;

void initializeWorm(const char* wormString);
void moveWorm();
void turnWorm(bool turnRight);

#endif  // UEBUNGSBLATT_4_WORM_H_
