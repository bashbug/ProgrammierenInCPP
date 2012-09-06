// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include "./VirusScan.h"

int main(int argc, char** argv) {
  VirusScan v;
  v.parseCommandLineArguments(argc, argv);
  v.readVirusSignatures(v._virusSignaturesFileName);
  for (size_t i = 0; i < v._inputFileNames.size(); i++) {
    v.readInputFile(v._inputFileNames[i]);
    v.scanInputFile();
  }
}
