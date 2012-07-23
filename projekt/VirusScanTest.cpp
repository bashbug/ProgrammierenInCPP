// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <string>
#include "./VirusScan.h"

// ____________________________________________________________________________
TEST(VirusScanTest, VirusScan) {
  VirusScan v;
  ASSERT_TRUE(v._inputFileNames.empty());
  ASSERT_EQ(NULL, v._logFileName);
  ASSERT_EQ(NULL, v._virusSignaturesFileName);
  ASSERT_TRUE(v._virusNames.empty());
  ASSERT_TRUE(v._virusSignatures.empty());
  ASSERT_EQ(NULL, v._signature);
  ASSERT_EQ(NULL, v._virus);
  ASSERT_TRUE(v._inputFile.empty());
  ASSERT_EQ(NULL, v._inputLine);
  ASSERT_TRUE(v._infectedFiles.empty());
  ASSERT_TRUE(v._cleanFiles.empty());
  ASSERT_EQ(-1, v._scanningTime);
}

// _____________________________________________________________________________
TEST(VirusScanTest, parseCommandLineArguments) {
  // Test with all options and one inputfile
  {
    VirusScan v;
    int argc = 4;
    char* argv[4] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--virusSignatures=virus-signatures.txt"),
      const_cast<char*>("--log-file=log.txt"),
      const_cast<char*>("file.txt")
    };

    v.parseCommandLineArguments(argc, argv);
    ASSERT_STREQ("virus-signatures.txt", v._virusSignaturesFileName);
    ASSERT_STREQ("log.txt", v._logFileName);
    ASSERT_STREQ("file.txt", v._inputFileNames[0]);
  }

  // Test without logfile
  {
    VirusScan v;
    int argc = 3;
    char* argv[3] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--virusSignatures=virus-signatures.txt"),
      const_cast<char*>("file.txt")
    };
    v.parseCommandLineArguments(argc, argv);
    ASSERT_EQ(NULL, v._logFileName);
    ASSERT_STREQ("virus-signatures.txt", v._virusSignaturesFileName);
    ASSERT_STREQ("file.txt", v._inputFileNames[0]);
  }

  // Test with more than one Input file
  {
    VirusScan v;
    int argc = 6;
    char* argv[6] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--virusSignatures=virus-signatures.txt"),
      const_cast<char*>("--log-file=log.txt"),
      const_cast<char*>("file1.txt"),
      const_cast<char*>("file2.txt"),
      const_cast<char*>("file3.txt")
    };
    v.parseCommandLineArguments(argc, argv);
    ASSERT_STREQ("virus-signatures.txt", v._virusSignaturesFileName);
    ASSERT_STREQ("log.txt", v._logFileName);
    ASSERT_STREQ("file1.txt", v._inputFileNames[0]);
    ASSERT_STREQ("file2.txt", v._inputFileNames[1]);
    ASSERT_STREQ("file3.txt", v._inputFileNames[2]);
  }

  // Test without options and without arguments.
  {
    VirusScan v;
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    int argc = 1;
    char* argv[1] = {
      const_cast<char*>("prog")
    };
    ASSERT_DEATH(v.parseCommandLineArguments(argc, argv), "Usage:.*");
  }
}

// ____________________________________________________________________________
TEST(VirusScanTest, splitVirusSignature) {
  VirusScan v;
  string line = "_0017_0001_000\t21b8004233c999cd218bd6b90300b440cd218b4c198b5"
    "41bb80157cd21b43ecd2132ed8a4c18\n";
  v.splitVirusSignature(line);
  ASSERT_EQ("_0017_0001_000", v._virusNames[0]);
  ASSERT_EQ("21b8004233c999cd218bd6b90300b440cd218b4c198b541bb80157cd21b43ec"
    "d2132ed8a4c18", v._virusSignatures[0]);
}

// ____________________________________________________________________________
TEST(VirusScanTest, readVirusSignatures) {
  // make tmp virusSignaturesFile for test
  const char* virusSignaturesFileName = "virus-signatures.TMP.txt";
  FILE* inputFile = fopen(virusSignaturesFileName, "w");
  fprintf(inputFile, "_0017_0001_000\t21b8004233c999cd218bd6b90300b440cd218b4c"
    "198b541bb80157cd21b43ecd2132ed8a4c18\n");
  fprintf(inputFile, "_0017_0001_001\tb3005a8b4e27b440cd21e8c2045a59b440cd21e8"
    "1902b440cd21b8004233c999cd218bd6b90300\n");
  fclose(inputFile);

  VirusScan v;
  int argc = 4;
  char* argv[4] = {
    const_cast<char*>("prog"),
    const_cast<char*>("--virusSignatures=virus-signatures.TMP.txt"),
    const_cast<char*>("--log-file=log.TMP.txt"),
    const_cast<char*>("file.txt")
  };

  v.parseCommandLineArguments(argc, argv);
  ASSERT_STREQ("virus-signatures.TMP.txt", v._virusSignaturesFileName);
  ASSERT_STREQ("log.TMP.txt", v._logFileName);
  ASSERT_STREQ("file.txt", v._inputFileNames[0]);

  v.readVirusSignatures(v._virusSignaturesFileName);
  ASSERT_EQ(false, v._virusNames.empty());
  ASSERT_EQ(false, v._virusSignatures.empty());
  ASSERT_EQ("_0017_0001_000", v._virusNames[0]);
  ASSERT_EQ("21b8004233c999cd218bd6b90300b440cd218b4c198b541bb80157cd21b43ec"
    "d2132ed8a4c18", v._virusSignatures[0]);
  ASSERT_EQ("_0017_0001_001", v._virusNames[1]);
  ASSERT_EQ("b3005a8b4e27b440cd21e8c2045a59b440cd21e81902b440cd21b8004233c99"
    "9cd218bd6b90300", v._virusSignatures[1]);
}

