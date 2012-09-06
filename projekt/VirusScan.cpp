// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <getopt.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include "./VirusScan.h"

using std::ifstream;
using std::ios;
using std::string;
using std::map;
using std::stringstream;

VirusScan::VirusScan() {
}

VirusScan::~VirusScan() {
}

void VirusScan::parseCommandLineArguments(int argc, char** argv) {
  struct option options[] = {
    {"target", 1, NULL, 't'},
    {"signatures", 1, NULL, 's'},
    {NULL, 0, NULL, 0}
  };

  optind = 1;

  while (true) {
    char opt = getopt_long(argc, argv, "t:s:", options, NULL);
    if (opt == -1) break;

    switch (opt) {
      case 't':
        _fileNameTarget = optarg;
        break;
      case 's':
        _fileNameSignatures = optarg;
        break;
      default:
        printf("Ooops wrong argument found\n");
    }
  }
}

void VirusScan::prepareScan() {
  readVirusSignaturesFile(_fileNameSignatures);
  readTargetFile(_fileNameTarget);
}

void VirusScan::readVirusSignaturesFile(const char* fileName) {
  size_t tab;
  size_t i = 0;
  string line;
  string signature;
  string signatureConv;
  ifstream file;
  map<char, vector<string> >::iterator it;
  file.open(fileName);

  while (file.good()) {
    getline(file, line);

    tab = line.find('\t');

    if (++i % 100 == 0) {
      printf("       processing signature #%zu\r", i);
    }

    if (line.length() == 0 || tab < 0) continue;

    signature = line.substr(tab+1, line.length());

    string name = line.substr(0, tab);

    _virusSignatures.add(signature, name);
  }

  printf("\n");

  file.close();
}

void VirusScan::printProgress(size_t current, size_t total) {
  double progress = 0;

  progress = static_cast<double>(current) / static_cast<double>(total);

  printf("       %-2.0f%% (%zu/%zu)\r", progress * 100.0f, current, total);
}

void VirusScan::readTargetFile(const char* fileName) {
  string line;
  ifstream file;
  file.open(fileName);

  file.seekg(0, ios::end);
  _fileLength = file.tellg();
  file.seekg(0, ios::beg);

  _fileBuffer = new char[_fileLength];

  file.read(_fileBuffer, _fileLength);

  file.close();
}

void VirusScan::scanFile() {
  unsigned char ch;
  double progress = 0;
  SignaturesList* ptr = NULL;
  SignaturesList* mptr = NULL;
  vector<SignaturesList*> _tmpTable;

  for (size_t i = 0; i < _fileLength; i++) {
    ch = _fileBuffer[i];

    ptr = _virusSignatures.getPointer(ch);

    if (i % 100 == 0) {
      progress = static_cast<double>(i) / static_cast<double>(_fileLength);
      printf("%-2.0f%% (%zu/%zu) table: %zu\r", progress * 100.0f, i,
        _fileLength, _matchTable.size());
    }
    // printf("current: %zu, table: %zu\n", i, _matchTable.size());

    if (ptr != NULL && ptr->end() == true) {
      printf("\nVirus '%s' found!\n", ptr->virusName().c_str());
    }

    _tmpTable.clear();
    for (vector<SignaturesList*>::iterator it = _matchTable.begin();
      it != _matchTable.end(); ) {
      mptr = (*it)->getPointer(ch);

      if (mptr != NULL) {
        it = _matchTable.erase(it);
        if (mptr->end() == true) {
          printf("\nVirus '%s' found!\n", mptr->virusName().c_str());
        } else {
          _tmpTable.push_back(mptr);
        }
      } else {
        it = _matchTable.erase(it);
      }
    }
    _matchTable.insert(_matchTable.end(), _tmpTable.begin(), _tmpTable.end());

    if (ptr != NULL) {
      _matchTable.push_back(ptr);
    }
  }
}
