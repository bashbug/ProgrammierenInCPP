// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include "./VirusScan.h"

// ____________________________________________________________________________
TEST(VirusScanTest, VirusScan) {
  VirusScan v;
  ASSERT_TRUE(v._inputFileNames.empty());
  ASSERT_EQ(NULL, v._logFileName);
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
    printf("TEST1\n");
    ASSERT_STREQ("virus-signatures.txt", v._virusSignaturesFileName);
    printf("TEST2\n");
    ASSERT_STREQ("log.txt", v._logFileName);
    ASSERT_STREQ("file.txt", v._inputFileNames[0]);
  }
}
//   // Test without logfile
//   {
//     VirusScan v;
//     int argc = 3;
//     char* argv[3] = {
//       const_cast<char*>("prog"),
//       const_cast<char*>("--virusSignatures=virus-signatures.txt"),
//       const_cast<char*>("file.txt")
//     };
//     v.parseCommandLineArguments(argc, argv);
//     ASSERT_EQ(NULL, v._logFileName);
//     ASSERT_STREQ("virus-signatures.txt", v._virusSignaturesFileName);
//     ASSERT_STREQ("file.txt", v._inputFileNames[0]);
//   }

//   // Test with more than one Input file
//   {
//     VirusScan v;
//     int argc = 6;
//     char* argv[6] = {
//       const_cast<char*>("prog"),
//       const_cast<char*>("--virusSignatures=virus-signatures.txt"),
//       const_cast<char*>("--log-file=log.txt"),
//       const_cast<char*>("file1.txt"),
//       const_cast<char*>("file2.txt"),
//       const_cast<char*>("file3.txt")
//     };
//     v.parseCommandLineArguments(argc, argv);
//     ASSERT_STREQ("virus-signatures.txt", v._virusSignaturesFileName);
//     ASSERT_STREQ("log.txt", v._logFileName);
//     ASSERT_STREQ("file1.txt", v._inputFileNames[0]);
//     ASSERT_STREQ("file2.txt", v._inputFileNames[1]);
//     ASSERT_STREQ("file3.txt", v._inputFileNames[2]);
//   }

//   // Test without options and without arguments.
//   {
//     VirusScan v;
//     ::testing::FLAGS_gtest_death_test_style = "threadsafe";
//     int argc = 1;
//     char* argv[1] = {
//       const_cast<char*>("prog")
//     };
//     ASSERT_DEATH(v.parseCommandLineArguments(argc, argv), "Usage:.*");
//   }
// }
