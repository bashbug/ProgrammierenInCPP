// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./Worm.h"

int main(int argc, char** argv) {
  // Variables with default initialized.
  const char* wormString = "~0-oooOOOoooOOOooo=--";
  float probability = 50;
  float speed = 6;
  int quantity = 6;

  // -h for to print usage information.
  if (argv[1] != NULL && strcmp(argv[1], "-h") == 0) {
    printf("Usage: ./AnimationMain <string> <probability in percent>"
      " <speedrange from 1 to 10> <quantity>\n");
    exit(1);
  }

  // Check the inputvalues.
  if (argc == 5) {
    wormString = argv[1];
    probability = atof(argv[2]);
    speed = atof(argv[3]);
    quantity = atoi(argv[4]);
    if (speed > 10 || speed < 1 || probability > 100 || probability <= 1 ||
      quantity < 1) {
      printf("Usage: ./AnimationMain <string> <probability in percent>"
        " <speedrange from 1 to 10> <quantity>\n");
      exit(1);
    }
  // Default for speed.
  } else if (argc == 4) {
    wormString = argv[1];
    probability = atof(argv[2]);
    speed = atof(argv[3]);
    if (speed > 10 || speed < 1 || probability > 100 || probability <= 1 ||
      quantity < 1) {
      printf("Usage: ./AnimationMain <string> <probability in percent>"
        " <speedrange from 1 to 10> <quantity>\n");
      exit(1);
    }
  // Default for speed and quantity.
  } else if (argc == 3) {
    wormString = argv[1];
    probability = atof(argv[2]);
    if (speed > 10 || speed < 1 || probability > 100 || probability <= 1 ||
      quantity < 1) {
      printf("Usage: ./AnimationMain <string> <probability in percent>"
        " <speedrange from 1 to 10> <quantity>\n");
      exit(1);
    }
    printf("%s\n", "oh man");
  // Default for probability, speed and quantity.
  } else if (argc == 2) {
    wormString = argv[1];
    if (speed > 10 || speed < 1 || probability > 100 || probability <= 1 ||
      quantity < 1) {
      printf("Usage: ./AnimationMain <string> <probability in percent>"
        " <speedrange from 1 to 10> <quantity>\n");
      exit(1);
    }
  }

  Worm::getTerminalSize();
  Worm* worms = new Worm[quantity];

  for (int i = 0; i < quantity; i++) {
    worms[i].setWormString(wormString);
    worms[i].initializeWorm();
  }

  // Hide the cursor.
  printf("\x1b[?25l");

  for (int k = 0; k < 1500; k++) {
    // Clear the screen.
    printf("\x1b[2J");

    for (int i = 0; i < quantity; i++) {
      worms[i].moveWorm();
      worms[i].drawWorm();
      worms[i].setTurnProbability(probability);
    }

    fflush(stdout);
    // Speed
    usleep(1/speed * 100000);
  }

  delete[] worms;
  printf("\x1b[?25h");
}
