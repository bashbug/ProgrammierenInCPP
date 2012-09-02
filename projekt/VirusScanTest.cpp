// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <string>
#include "./VirusScan.h"

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
    // ASSERT_EQ(NULL, v._logFileName);
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
TEST(VirusScanTest, readInputFile) {
  // make tmp input file for test
  const char* inputfileName = "input.TMP.txt";
  FILE* inputFile = fopen(inputfileName, "w");
  fprintf(inputFile, "Hello World");
  fclose(inputFile);

  {
    VirusScan v;
    v.readInputFile("input.TMP.txt");
    ASSERT_STREQ("48656c6c6f20576f726c64", v._buffer.c_str());
  }

  remove(inputfileName);
}

// ____________________________________________________________________________
TEST(VirusScanTest, splitVirusSignature) {
  // make tmp input file for test
  const char* inputfileName = "input.TMP.txt";
  FILE* inputFile = fopen(inputfileName, "w");
  fprintf(inputFile, "_0017_0001_000\t21b8004233c999cd218bd6b90300b440cd218b4c"
    "198b541bb80157cd21b43ecd2132ed8a4c18\n"
    "_0017_0001_001\tb3005a8b4e27b440cd21e8c2045a59b440cd21e81902b440cd21b8004"
    "233c999cd218bd6b90300\n"
    "_0104_0004_001\t2133c9b8004299cd21b91a00b440ba5704cd21b801575a59cd21b43ec"
    "d21585a1f59cd215a1fb8\n");
  fclose(inputFile);

  {
    VirusScan v;
    v.readVirusSignatures("input.TMP.txt");
    // hex 21 -> int 33
    bool tmp = v._signatures["21"]->searchWord("b8004233c999cd218bd6b90300b44"
      "0cd218b4c198b541bb80157cd21b43ecd2132ed8a4c18");
    ASSERT_EQ(true, tmp);
    tmp = v._signatures["21"]->searchWord("33c9b8004299cd21b91a00b440ba5704cd"
      "21b801575a59cd21b43ecd21585a1f59cd215a1fb8");
    ASSERT_EQ(true, tmp);
    // hex b3 -> int 179
    tmp = v._signatures["b3"]->searchWord("005a8b4e27b440cd21e8c2045a59b440c"
      "d21e81902b440cd21b8004233c999cd218bd6b90300");
    ASSERT_EQ(true, tmp);
  }
  remove(inputfileName);
}

// ____________________________________________________________________________
TEST(VirusScanTest, scanInputFile) {
  // make tmp input file with viruses for test
  const char* inputfileName = "input.TMP.txt";
  FILE* inputFile = fopen(inputfileName, "w");
  fprintf(inputFile, "$CEliacmaTrESTuScikgsn$FREE-TEST-SIGNATURE$EEEEE$\n"
    "X5O!P%%@AP[4\\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*\n" // NOLINT
    "fdsfml c$CEliacmaTrESTuScikgsn$FREE-TEST-SIGNATURE$EEEEE$wdeX5O!P%%@AP["
    "4\\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*\n"); // NOLINT
  fclose(inputFile);

  // two signatures, which are included in input file above
  const char* signaturesfileName = "signatures.TMP.txt";
  FILE* signaturesFile = fopen(signaturesfileName, "w");
  fprintf(signaturesFile, "ClamAV-Test-Signature\t2443456c6961636d615472455354"
    "755363696b67736e24465245452d544553542d5349474e415455524524454545454524\n"
    "Eicar-Test\t58354f2150254041505b345c505a58353428505e2937434329377d244549"
    "4341522d5354414e444152442d414e544956495255532d544553542d46494c452124482b"
    "482a\n");
  fclose(signaturesFile);

  {
    VirusScan v;
    v.readInputFile("input.TMP.txt");
    v.readVirusSignatures("signatures.TMP.txt");
    ASSERT_EQ("ClamAV-Test-Signature", v._virusNames["43456c6961636d6154724"
      "55354755363696b67736e24465245452d544553542d5349474e415455524524454545454"
      "524"]);
    v.scanInputFile();
    // hex 24 -> int 36
    ASSERT_EQ(true, v._signatures["24"]->searchWord("43456c6961636d615472455354"
    "755363696b67736e24465245452d544553542d5349474e415455524524454545454524"));
    ASSERT_EQ(true, v._signatures["58"]->searchWord("354f2150254041505b345c"
      "505a58353428505e2937434329377d244549"
      "4341522d5354414e444152442d414e544956495255532d544553542d46494c452124482b"
      "482a"));
  }

  remove(inputfileName);
  remove(signaturesfileName);
}
