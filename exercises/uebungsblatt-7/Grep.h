// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@informatik.uni-freiburg.de>.

#ifndef UEBUNGSBLATT_7_GREP_H_
#define UEBUNGSBLATT_7_GREP_H_

#include <string.h>
#include <gtest/gtest.h>

// Class for finding lines (in an input file) containing a given pattern.
// NOTE: there is a well-known Unix/Linux utility called "grep" with this
// functionality, hence the name of the class.
class Grep {
 public:
  // Constructor
  Grep();
  FRIEND_TEST(GrepTest, Grep);
  // Deconstructor
  ~Grep();
  // Parse the command line arguments. The pattern is specified as a non-option
  // argument and cannot be ommitted. Apart from that, the following options
  // should be supported:
  // --input-file, -i  : read from file (default: read from stdin).
  // --output-file, -o  : write to file (default: write to stdout).
  // --replace-with, -r : in the lines shown, replace pattern with this string
  // (default: just show the lines containing the pattern).
  void parseCommandLineArguments(int argc, char** argv);
  FRIEND_TEST(GrepTest, parseCommandLineArguments);
  // Do the actual work, that is, read input, and output only the lines
  // containing the pattern (optionally replacing it).
  void process();
  FRIEND_TEST(GrepTest, processFile);
 private:
  // Print usage info and exit. You don't have to test this method.
  void printUsageAndExit();
  FRIEND_TEST(GrepTest, printUsageAndExit);
  // Membervariables
  char* _inputFile;
  char* _outputFile;
  char* _replace;
  char* _pattern;
  bool _invert;
  bool _count;
};

#endif  // UEBUNGSBLATT_7_GREP_H_
