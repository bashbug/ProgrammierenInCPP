// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <getopt.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "./Node.h"
#include "./Trie.h"
#include "./VirusScan.h"

using std::ifstream;
using std::iostream;
using std::vector;
using std::string;
using std::stringstream;

// ____________________________________________________________________________
VirusScan::VirusScan() {
}

// ____________________________________________________________________________
VirusScan::~VirusScan() {
}

// ____________________________________________________________________________
void VirusScan::parseCommandLineArguments(int argc, char** argv) {
  struct option options[] = {
    { "virusSignatures", 1, NULL, 'v' },
    { NULL, 0, NULL, 0 }
  };
  optind = 1;  // if the loop starts again, than optind = X without reset
  while (true) {
    char opt = getopt_long(argc, argv, "v:", options, NULL);
    if (opt == -1) break;
    switch (opt) {
      case 'v':
        _virusSignaturesFileName = optarg;
        break;
    }
  }
  if (optind + 1 != argc) printUsageAndExit();
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
void VirusScan::readInputFile(const char* inputFileName) {
  _inputFileName = inputFileName;
  printf("[INFO] read the input file %s \n", inputFileName);
  ifstream inputFile;
  inputFile.open(inputFileName, std::ios::binary);
  // get file length
  inputFile.seekg(0, std::ios::end);
  size_t fileSize = inputFile.tellg();
  inputFile.seekg(0, std::ios::beg);
  char* buffer = new char[fileSize];
  // hold the inputFile binary as a string
  inputFile.read(buffer, fileSize);
  inputFile.close();
  string tmp;
  for (size_t i = 0; i < fileSize; i++) {
    stringstream ss;
    tmp = "";
    // set 0 hex char
    ss << std::setfill('0') << std::setw(2) <<
      std::hex << static_cast<int>(buffer[i]);
    ss >> tmp;
    _buffer.append(tmp);
  }
}

// ____________________________________________________________________________
void VirusScan::readVirusSignatures(const char* virusSignaturesFileName) {
  printf("[INFO] read the given signatures file %s\n", virusSignaturesFileName);
  string line;
  ifstream inputFile;
  inputFile.open(virusSignaturesFileName);
  while (inputFile.good()) {
    getline(inputFile, line);
    // split the input line in virusname and -signature. and convert the
    // string signature to an char array
    splitVirusSignature(line);
  }
  inputFile.close();
}

// ____________________________________________________________________________
void VirusScan::splitVirusSignature(string line) {
  // find position of the tabulator, which seperates name an signatur.
  int pos = line.find('\t');
  string sig = line.substr(pos+1);
  string name = line.substr(0, pos);
  // ignore empty lines or lines without tab.
  if (line.length() <= 0 || pos == -1) return;
  // remove \n at the end of every line.
  if (!sig.empty() && sig[sig.size() - 1] == '\n') {
    sig.erase(sig.size() - 1);
  }
  // fill nameMap with signatur = key without first hex value and name = value
  _virusNames[sig.substr(2)] = name;
  string bytes = sig.substr(0, 2);
  _itSignatures = _signatures.find(bytes);
  if (_itSignatures == _signatures.end()) {
    // set new key with new vector as value
    Trie* trie = new Trie();
    // printf("add signature: %s\n", sig.substr(2).c_str());
    trie->addWord(sig.substr(2));
    if (trie->searchWord(sig.substr(2)) == true) {
      // printf("sig found\n");
    }
    _signatures[bytes] = trie;
    // set first signature length
    vector<int> v;
    v.push_back(sig.length()-2);
    _siglen[bytes] = v;
  } else {
    // key already exists. add new signature to existing vector.
    _signatures[bytes]->addWord(sig.substr(2));
    // set length of each signature
    _siglen[bytes].push_back(sig.length()-2);
  }
}

// ____________________________________________________________________________
void VirusScan::scanInputFile() {
  printf("[INFO] scan input file %s\n", _inputFileName);
  _infected = false;
  string tmp, bytes;
  double progress = 0;

  // erstes byte aus dem buffer holen
  // byte in signature map suchen
  // buffer nach länge der signature länge in trie suchen
  // wenn ja, dann name des virus aus map

  for (size_t i = 0; i < _buffer.length(); i+=2) {
    bytes = _buffer.substr(i, 2);
    if (i % 100 == 0) {
      progress = static_cast<double>(i) / static_cast<double>(_buffer.length());
      printf("%-2.2f\r", progress * 100.0f);
    }
    // get a possible trie
    _itSignatures = _signatures.find(bytes);
    if (_itSignatures != _signatures.end()) {
      for (size_t k = 0; k < _siglen[bytes].size(); k++) {
        // get length of a signature
        int& len = _siglen[bytes][k];
        // cut the buffer for each signature length
        tmp = _buffer.substr(i+2, len);
        // check if the tmp buffer string matchs with a signature
        // in the current trie
        _infected = _itSignatures->second->searchWord(tmp);
        if (_infected == true) {
          // get the virusname for the current signature
          string virusName = _virusNames[tmp];
          printf("Found: %s\n", virusName.c_str());
        }
      }
    }
  }
}
