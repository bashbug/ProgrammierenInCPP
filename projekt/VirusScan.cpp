// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <getopt.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "./VirusScan.h"

using std::ifstream;
using std::iostream;
using std::vector;

// ____________________________________________________________________________
VirusScan::VirusScan() {
  _inputFileNames.clear();
  _inputFileName = NULL;
  _logFileName = NULL;
  _virusSignaturesFileName = NULL;
  _virusNames.clear();
  _virusSignatures.clear();
  _signature = NULL;
  _virus = NULL;
  _infectedFiles.clear();
  _cleanFiles.clear();
  _scanningTime = -1;
}

// ____________________________________________________________________________
VirusScan::~VirusScan() {
  _inputFileNames.clear();
  _inputFileName = NULL;
  _logFileName = NULL;
  _virusSignaturesFileName = NULL;
  _virusNames.clear();
  _virusSignatures.clear();
  _signature = NULL;
  _virus = NULL;
  _infectedFiles.clear();
  _cleanFiles.clear();
  _scanningTime = -1;
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
void VirusScan::readVirusSignatures(const char* virusSignaturesFileName) {
  string line;
  ifstream inputFile;
  inputFile.open(virusSignaturesFileName);
  // ios::good returns true if none of the stream's error flags
  // (eofbit, failbit and badbit) are set.
  while (inputFile.good()) {
    getline(inputFile, line);
    // split the input line in virusname and -signature.
    splitVirusSignature(line);
  }
  inputFile.close();
}

// ____________________________________________________________________________
void VirusScan::splitVirusSignature(string line) {
  // find position of the tabulator, which seperates name an signatur.
  size_t pos = line.find('\t');
  string sig = line.substr(pos+1);
  string name = line.substr(0, pos);

  // remove \n at the end of every line.
  if (!sig.empty() && sig[sig.size() - 1] == '\n') {
    sig.erase(sig.size() - 1);
  }
  // check if any siganture has special operators like '?*{}'.
  checkSignature(sig, name);
  // howMany();
}


// ____________________________________________________________________________
void VirusScan::checkSignature(string sig, string name) {
  // if the content is not found, the member value npos is returned.
  // npos indicates the end of the string.
  // size_t npos = -1;

  if (sig.find('?') != npos) {
    _signaturesWithQuestion.push_back(sig);
    _virusNamesQuestion.push_back(name);
  } else if (sig.find('*') != npos) {
    _signaturesWithStar.push_back(sig);
    _virusNamesStar.push_back(name);
  } else if (sig.find(123) != npos) {
    _signaturesWithBracket.push_back(sig);
    _virusNamesBracket.push_back(name);
  } else {
    _virusSignatures.push_back(sig);
    _virusNames.push_back(name);
  }
}

// ____________________________________________________________________________
// void VirusScan::scanInputFile() {
//   // read and scan each inputFile
//   for (size_t i = 0; i < _inputFileNames.size(); i++) {
//     _inputFileName = _inputFileNames[i];
//     readInputFile(_inputFileName);
//     _infected = isInfected(_buffer);
//     if (_infected == true) {
//       _infectedFiles.push_back(_inputFileName);
//     } else {
//       _cleanFiles.push_back(_inputFileName);
//     }
//   }
// }

// ____________________________________________________________________________
void VirusScan::readInputFile(const char* inputFileName) {
  ifstream file;
  file.open(inputFileName, std::ios::binary);
  // get file length
  file.seekg(0, std::ios::end);
  size_t fileSize = file.tellg();
  file.seekg(0, std::ios::beg);
  // hold all the bytes of the inputFile
  _buffer = new char[fileSize];
  file.read(_buffer, fileSize);
}

// ____________________________________________________________________________
// bool VirusScan::isInfected(char* buffer) {
//   char* highNibble = 0xf0;
//   char* lowNibble = 0x0f;
//   size_t k = 0;
//   string sig = _virusSignatures[0];
//   for (size_t i = 0; i < strlen(buffer); i++) {
//       if (buffer[i] == sig[k]) {
//         k++;
//         if (k == strlen(sig) return true;
//       } else {
//         k = 0;
//       }
//     }
//   }
// }
