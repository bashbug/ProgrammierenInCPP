// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./String.h"
#include "./Grep.h"

int main(int argc, char** argv) {
  Grep g;
  g.parseCommandLineArguments(argc, argv);
  g.process();
}
