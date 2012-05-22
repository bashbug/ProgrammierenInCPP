// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./TerminalSize.h"
#include "./Animation.h"

int main(int argc, char** argv) {
  if (argc != 1) {
    printf("./AnimationMain\n");
    exit(1);
  }

  // Get terminal size by using standard constructor
  // of class TerminalSize (for dynamic version see below).
  TerminalSize myTerminalSize;
  // maxX = myTerminalSize.get_row();
  // maxY = myTerminalSize.get_col();

  // Move the mighty owl forever.
  while (true) {
    // Recheck of terminal size.
    maxX = myTerminalSize.get_row();
    maxY = myTerminalSize.get_col();

    // Hide the cursor.
    printf("\x1b[?25l");
    // Clear the screen.
    printf("\x1b[2J");

    if (posX%2 == 0 && posY%2 ==0) {
        printf("\x1b[%d;%dH__(*,*)^^\n", posX, posY);
        printf("\x1b[%d;%dH  _| '< \n", posX+1, posY);
    } else {
        printf("\x1b[%d;%dH^^(*,*)__", posX, posY);
        printf("\x1b[%d;%dH  >' |_  \n", posX+1, posY);
    }

    // Show the cursor again before exiting.
    // Fails when using strg+c to exit program.
    fflush(stdout);
    printf("\x1b[?25h");
    flyingOwl();
    usleep(200 * 1000);
  }
}
