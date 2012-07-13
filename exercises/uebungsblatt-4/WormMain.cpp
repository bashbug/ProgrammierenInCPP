// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./TerminalSize.h"
#include "./Worm.h"

int main(int argc, char** argv) {
  const char* wormString;
  float probability;
  float speed;

  if (argc == 4) {
    wormString = argv[1];
    probability = atof(argv[2]);
    speed = atof(argv[3]);
    if (speed > 10 || speed < 1 || probability > 100 || probability <= 1) {
      printf("Usage: ./AnimationMain <string> <probability in percent>"
        " <speedrange from 1 to 10>\n");
      exit(1);
    }
  } else if (argc == 3) {
    wormString = argv[1];
    probability = atof(argv[2]);
    speed = 3;
  } else if (argc == 2) {
    wormString = argv[1];
    probability = 50;
    speed = 3;
  } else {
    // default worm
    wormString = "~0-oooOOOoooOOOooo=--";
    probability = 50;
    speed = 3;
  }

  // Terminal size check
  TerminalSize myTerminalSize;
  maxX = myTerminalSize.get_row();
  maxY = myTerminalSize.get_col();

  initializeWorm(wormString);

  while (true) {
    // Hide the cursor.
    printf("\x1b[?25l");
    // Clear the screen.
    printf("\x1b[2J");

    // Print worm in red, yellow, green
    for (int i = n; i > 0; i--) {
      const char* style = "\x1b[1;32m\x1b[2m";
      if (i == 1) {
        style = "\x1b[1;31m\x1b[2m";
      } else if (i == 2) {
        style = "\x1b[1;33m\x1b[1m";
      }
      printf("%s\x1b[%d;%dH%c", style, posX[i], posY[i],
        wormString[i-1]);
    }

    // Show the cursor again before exiting.
    // Fails when using strg+c to exit program.
    fflush(stdout);
    printf("\x1b[?25h");

    moveWorm();

    // Randomnumber for probability
    double rnum = drand48();
    if (rnum <= 2*(probability/100)/3) {
      turnWorm(false);
    }
    if (rnum <= (probability/100)/3) {
      turnWorm(true);
    }

    // Speed
    usleep(1/speed * 100000);
  }
}
