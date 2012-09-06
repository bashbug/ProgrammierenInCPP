// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef PROJEKT_VIRUSSCAN_H_
#define PROJEKT_VIRUSSCAN_H_

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include "./SignaturesList.h"

using std::string;
using std::vector;
using std::list;

class VirusScan {
 public:
  VirusScan();
  ~VirusScan();
  FRIEND_TEST(VirusScanTest, VirusScan);

  void parseCommandLineArguments(int argc, char** argv);
  FRIEND_TEST(VirusScanTest, parseCommandLineArguments);

  void readMD5VirusSignaturesFile(const char* fileName);

  void readVirusSignaturesFile(const char* fileName);
  FRIEND_TEST(VirusScanTest, readVirusSignaturesFile);

  void readTargetFile(const char* fileName);
  FRIEND_TEST(VirusScanTest, readTargetFile);

  void printUsageAndExit();

  void printProgress(size_t current, size_t total);

  void prepareScan();

  void scanFile();
  FRIEND_TEST(VirusScanTest, scanFile);

  vector<const char*> _fileNames;
  const char* _fileNameMD5Signatures;
  const char* _fileNameSignatures;
  const char* _log;
  char* _fileBuffer;
  size_t _fileLength;
  SignaturesList _virusSignatures;
  list<SignaturesList*> _matchTable;
};

#endif  // PROJEKT_VIRUSSCAN_H_
