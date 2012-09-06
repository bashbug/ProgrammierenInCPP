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
    int argc = 5;
    char* argv[5] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--md5=md5Signatures.txt"),
      const_cast<char*>("--hex=hexSignatures.txt"),
      const_cast<char*>("--log=log.txt"),
      const_cast<char*>("test.txt"),
    };
    v.parseCommandLineArguments(argc, argv);

    ASSERT_STREQ("test.txt", v._fileNames[0]);
    ASSERT_STREQ("log.txt", v._log);
    ASSERT_STREQ("md5Signatures.txt", v._fileNameMD5Signatures);
    ASSERT_STREQ("hexSignatures.txt", v._fileNameSignatures);
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
  v.readVirusSignaturesFile("data/virus-signatures.txt");
  // v.readTargetFile("data/testfile2.txt");
  v.readTargetFile("data/virussum.doc");
  v.scanFile();
  ASSERT_TRUE(true);
}
