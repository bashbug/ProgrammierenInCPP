// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <getopt.h>
#include "./VirusScan.h"

// ____________________________________________________________________________
VirusScan::VirusScan() {
  _inputFileNames.clear();
  _logFileName = NULL;
  _virusSignaturesFileName = NULL;
  _virusNames.clear();
  _virusSignatures.clear();
  _signature = NULL;
  _virus = NULL;
  _inputFile.clear();
  _inputLine = NULL;
  _infectedFiles.clear();
  _cleanFiles.clear();
  _scanningTime = -1;
}

// ____________________________________________________________________________
VirusScan::~VirusScan() {
  _inputFileNames.clear();
  _logFileName = NULL;
  _virusSignaturesFileName = NULL;
  _virusNames.clear();
  _virusSignatures.clear();
  _signature = NULL;
  _virus = NULL;
  _inputFile.clear();
  _inputLine = NULL;
  _infectedFiles.clear();
  _cleanFiles.clear();
  _scanningTime = NULL;
}

// ____________________________________________________________________________
void VirusScan::parseCommandLineArguments(int argc, char** argv) {
  struct option options[] = {
    { "virusSignatures", 1, NULL, 'v' },
    { "log-file", 1, NULL, 'l' },
    { NULL, 0, NULL, 0 }
  };
  optind = 1;  // if the loop starts again, than optind = X without reset
  while (true) {
    char opt = getopt_long(argc, argv, "v:l:", options, NULL);
    if (opt == -1) break;
    switch (opt) {
      case 'v':
        _virusSignaturesFileName = optarg;
        break;
      case 'l':
        _logFileName = optarg;
        break;
    }
  }
  if (argc <= 2) printUsageAndExit();
  // every non-option argument is interpreted as an inputfile
  for (int i = 0; i < argc-optind; i++) {
    _inputFileNames.push_back(argv[optind + i]);
  }
}

// _____________________________________________________________________________
void VirusScan::printUsageAndExit() {
  fprintf(stderr,
          "Usage: :/VirusScan -v [FILE] -l [FILE] [FILE]... \n \n"
          "DESCRIPTION: \n"
          "  VirusScan scanns the named input FILEs for virues. \n"
          "OPTIONS: \n"
          "  --virusSignatures, -v : contains virusname and -signature. \n"
          "  --log-file, -l       : contains logging information. \n");
  exit(1);
}

// ____________________________________________________________________________
// void VirusScan::readVirusSignatures(const char* inputFileName) {
// }
