// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@informatik.uni-freiburg.de>.

#include <sys/ioctl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "./AnimatedObject.h"

// Main function.
int main(int argc, char** argv) {
  // Parse command line arguments.
  if (argc != 2) {
    printf("Usage: ./AnimationMain <number of objects>\n"
       "Shows random animated objects on the screen\n");
    exit(1);
  }
  int n = atoi(argv[1]);

  // Create n objects of random types. The default constructor for each type
  // should construct an object of this type with a random position, random
  // size, and random animation speed (= how much the animation changes with one
  // call of animationStep below).
  std::vector<AnimatedObject*> animatedObjects(n);
  srand48(time(NULL));
  for (size_t i = 0; i < animatedObjects.size(); i++) {
    AnimatedObject* ao = NULL;
    switch (static_cast<int>(3 * drand48())) {
      case 0 :
        ao = new AnimatedCircle();
        printf("CIRCLE\n");
        break;
      case 1 :
        ao = new AnimatedSquare();
        printf("SQUARE\n");
        break;
      case 2 :
        ao = new AnimatedTriangle();
        printf("TRIANGLE\n");
        break;
    }
    assert(ao != NULL);
    animatedObjects[i] = ao;
  }

  // Animate the objects forever.
  while (true) {
    for (size_t i = 0; i < animatedObjects.size(); i++) {
      animatedObjects[i]->animationStep();
    }
    usleep(10000 * 10);
    // Some waiting time between steps, so that it looks good.
  }
}
