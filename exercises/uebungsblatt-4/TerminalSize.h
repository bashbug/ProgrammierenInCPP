// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifndef  UEBUNGSBLATT_4_TERMINALSIZE_H_
#define  UEBUNGSBLATT_4_TERMINALSIZE_H_

class TerminalSize {
  public:
    // Declare constructor.
    TerminalSize();
    // Functions to get terminal size.
    const int get_row();
    const int get_col();
};

#endif  // UEBUNGSBLATT_4_TERMINALSIZE_H_
