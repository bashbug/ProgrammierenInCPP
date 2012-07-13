// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "./Worm.h"

// Maximum length of a worm.
const int MAX_WORM_LENGTH = 100;
// The worm string.
const char* wormString;
// The length of the worm string.
int n;
// The positions of the characters of the worm string.
int posX[MAX_WORM_LENGTH];
int posY[MAX_WORM_LENGTH];
// The current direction of the worm.
int dirX = 1;
int dirY = 1;
// The screen dimensions.
int maxX;
int maxY;

bool turn;

void initializeWorm(const char* wormString) {
    n = strlen(wormString);
    for (int i = 0; i <= n; i++) {
        posX[i] = (maxX / 2);
        posY[i] = (maxY - n) / 2+i;
    }
}

void moveWorm() {
    int tempPosX[MAX_WORM_LENGTH];
    int tempPosY[MAX_WORM_LENGTH];

    for (int i = 0; i <= n; i++) {
        tempPosX[i] = posX[i];
        tempPosY[i] = posY[i];
    }

    // Shift the position after wormhead for dynamic moving.
    for (int i = 1; i <= n; i++) {
        posX[i] = tempPosX[i-1];
        posY[i] = tempPosY[i-1];
    }

    // Reflection at the
    // bottom
    if (posX[0] + dirX >= maxX) dirX = -dirX;
    // top
    if (posX[0] + dirX <= 1) dirX = -dirX;
    // right border
    if (posY[0] + dirY >= maxY) dirY = -dirY;
    // left border
    if (posY[0] +dirY <= 1) dirY = -dirY;

    posY[0] += dirY;
    posX[0] += dirX;
}

void turnWorm(bool turnRight) {
    float newDirX;
    float newDirY;

    // Rotation with normalised rotationmatrix
    if (turnRight == true) {
        newDirX = (1 / fabs(sqrt(pow(dirX, 2) + pow(dirY, 2)))) * (dirX - dirY);
        newDirY = (1 / fabs(sqrt(pow(dirX, 2) + pow(dirY, 2)))) * (dirX + dirY);
    } else {
        newDirX = (1 / fabs(sqrt(pow(dirX, 2) + pow(dirY, 2)))) * (dirX + dirY);
        newDirY = (1 / fabs(sqrt(pow(dirX, 2) + pow(dirY, 2)))) * (dirX - dirY);
    }
    dirX = newDirX;
    dirY = newDirY;
}
