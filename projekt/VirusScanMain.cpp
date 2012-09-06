// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include "./VirusScan.h"

int main(int argc, char** argv) {
  VirusScan v;
  v.parseCommandLineArguments(argc, argv);
  v.readVirusSignaturesFile(v._fileNameSignatures);
  for (size_t i = 0; i < v._fileNames.size(); i++) {
    v.readTargetFile(v._fileNames[i]);
    v.scanFile();
  }
}
