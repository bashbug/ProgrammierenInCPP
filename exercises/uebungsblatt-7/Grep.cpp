// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <getopt.h>
#include "./String.h"
#include "./Grep.h"

// _____________________________________________________________________________
Grep::Grep() {
  _inputFile = NULL;
  _outputFile = NULL;
  _replace = NULL;
  _pattern = NULL;
  _invert = false;
  _count = false;
}

// ____________________________________________________________________________
Grep::~Grep() {
  _inputFile = NULL;
  _outputFile = NULL;
  _replace = NULL;
  _pattern = NULL;
  _invert = NULL;
  _count = NULL;
}

// _____________________________________________________________________________
void Grep::parseCommandLineArguments(int argc, char** argv) {
  // needed if object is parsed again
  _inputFile = NULL;
  _outputFile = NULL;
  _replace = NULL;
  _pattern = NULL;
  _invert = false;
  _count = false;

  struct option options[] = {
    { "input-file", 1, NULL, 'i' },
    { "output-file", 1, NULL, 'o' },
    { "replace-with", 1, NULL, 'r' },
    { "invert-match", 0, NULL, 'v' },  // has no argument
    { "count", 0, NULL, 'c'},  // has no argument
    { NULL, 0, NULL, 0 }
  };
  optind = 1;  // if the loop starts again, than optind = X without reset
  while (true) {
    char opt = getopt_long(argc, argv, "i:o:r:vc", options, NULL);
    if (opt == -1) break;
    switch (opt) {
      case 'i':
        _inputFile = optarg;
        break;
      case 'o':
        _outputFile = optarg;
        break;
      case 'r':
        _replace = optarg;
        break;
      case 'v':
        _invert = true;
        break;
      case 'c':
        _count = true;
      break;
    }
  }
  if (optind + 1 != argc) printUsageAndExit();
  _pattern = argv[optind];  // is the last non-option argument in argv
}

// _____________________________________________________________________________
void Grep::process() {
  const size_t MAX_LINE_LENGTH = 1000;
  char line[MAX_LINE_LENGTH + 1];
  size_t lineCount = 1;
  size_t count;

  // default: read from stdin and write to stdout
  FILE* inputFile = stdin;
  FILE* outputFile = stdout;

  if (_inputFile != NULL) {
    inputFile = fopen(_inputFile, "r");
  }
  if (_outputFile != NULL) {
    outputFile = fopen(_outputFile, "w");
  }

  while (true) {
    fgets(line, MAX_LINE_LENGTH, inputFile);
    if (feof(inputFile)) break;
    String s(line);
    if (_replace != NULL && count == false) {
      s.findAndReplace(_pattern, _replace);
      fprintf(outputFile, "%3zu : %s", lineCount, s.getString());
      lineCount++;
    // without replace argument
    } else {
      if (s.find(_pattern, 0) != -1 && _invert == false) {
        if (_count == true) {
          count = lineCount;
        } else {
          fprintf(outputFile, "%3zu : %s", lineCount, s.getString());
        }
        lineCount++;
      }
      // if invert == true print all lines in which pattern is not found
      if (s.find(_pattern, 0) == -1 && _invert == true) {
        if (_count == true) {
          count = lineCount;
        } else {
          fprintf(outputFile, "%3zu : %s", lineCount, s.getString());
        }
        lineCount++;
      }
    }
  }

  // if count == true print how often pattern is found
  if (_count == true) {
    fprintf(outputFile, "%zu\n", lineCount-1);
    // -1 because, lineCount is initialized with 1
  }

  fclose(inputFile);
  fclose(outputFile);
}

// _____________________________________________________________________________
void Grep::printUsageAndExit() {
  fprintf(stderr,
          "Usage: :/Grep -i [FILE] -o [FILE] -r [REPLACE] [PATTERN]\n \n"
          "DESCRIPTION: \n"
          "   Grep searches the named input FILEs for lines containing a match"
          "\n   to the given PATTERN. \n"
          "OPTIONS: \n"
          "   --input-file, -i   : read from file. \n"
          "   --output-file, -o  : write to file. \n"
          "   --replace-with, -r : replace pattern with this string.\n"
          "   --invert-match, -v : invert the sense of matching, to select "
          "non-matching lines.\n"
          "   --count, -c        : count of matching lines. "
          "with -v count  non-matching lines.");
  exit(1);
}
