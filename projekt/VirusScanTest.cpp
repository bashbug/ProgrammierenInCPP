// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include "./VirusScan.h"

TEST(VirusScanTest, VirusScan) {
  ASSERT_TRUE(true);
}

TEST(VirusScanTest, parseCommandLineArguments) {
  {
    VirusScan v;
    int argc = 3;
    char* argv[3] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--target=test.txt"),
      const_cast<char*>("--signatures=signatures.txt")
    };
    v.parseCommandLineArguments(argc, argv);

    ASSERT_STREQ("test.txt", v._fileNameTarget);
    ASSERT_STREQ("signatures.txt", v._fileNameSignatures);
  }
}

// TEST(VirusScanTest, readVirusSignaturesFile) {
//   VirusScan v;
//   v.readVirusSignaturesFile("virus-signatures.txt");
// }

// TEST(VirusScanTest, readTargetFile) {
//   VirusScan v;
//   v.readTargetFile("virus-test.txt");
//   ASSERT_EQ("X5O!P%@AP[4\\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*", v._fileBuffer[0]);  // NOLINT
// }

TEST(VirusScanTest, scanFile) {
  VirusScan v;
  printf("[TEST] reading and converting signatures ...\n");
  v.readVirusSignaturesFile("virus-signatures.txt");
  printf("[TEST] reading file ...\n");
  v.readTargetFile("testfile2.txt");
  // v.readTargetFile("virussum.doc");
  printf("[TEST] scanning file ...\n");
  v.scanFile();
  ASSERT_TRUE(true);
}
