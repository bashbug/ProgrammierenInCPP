// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef VIRUSSCAN_VIRUSSCAN_H_
#define VIRUSSCAN_VIRUSSCAN_H_

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include "./SignaturesList.h"

using std::string;
using std::vector;
using std::map;

class VirusScan {
  const char* _fileNameTarget;
  const char* _fileNameSignatures;
  char* _fileBuffer;
  size_t _fileLength;
  SignaturesList _virusSignatures;
  vector<SignaturesList*> _matchTable;

 public:
  VirusScan();
  ~VirusScan();
  FRIEND_TEST(VirusScanTest, VirusScan);

  void parseCommandLineArguments(int argc, char** argv);
  FRIEND_TEST(VirusScanTest, parseCommandLineArguments);

  void readVirusSignaturesFile(const char* fileName);
  FRIEND_TEST(VirusScanTest, readVirusSignaturesFile);

  void readTargetFile(const char* fileName);
  FRIEND_TEST(VirusScanTest, readTargetFile);

  void printProgress(size_t current, size_t total);

  void prepareScan();

  void scanFile();
  FRIEND_TEST(VirusScanTest, scanFile);
};

#endif  // VIRUSSCAN_VIRUSSCAN_H_
