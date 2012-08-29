// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <string>
#include "./VirusScan.h"

// ____________________________________________________________________________
TEST(VirusScanTest, VirusScan) {
  VirusScan v;
  ASSERT_TRUE(v._inputFileNames.empty());
  ASSERT_EQ(NULL, v._inputFileName);
  ASSERT_EQ(NULL, v._logFileName);
  ASSERT_EQ(NULL, v._virusSignaturesFileName);
  ASSERT_TRUE(v._virusNames.empty());
  ASSERT_TRUE(v._virusSignatures.empty());
  ASSERT_EQ(NULL, v._signature);
  ASSERT_EQ(NULL, v._virus);
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
TEST(VirusScanTest, checkSignature) {
  // normal signature
  {
    VirusScan v;
    string name = "bla";
    string sig = "21b8004233c999cd218bd6b90300b440cd218b4c198b5"
      "41bb80157cd21b43ecd2132ed8a4c18";
    v.checkSignature(sig, name);
    ASSERT_EQ(sig, v._virusSignatures[0]);
    ASSERT_EQ(name, v._virusNames[0]);
    ASSERT_EQ(true, v._virusNamesQuestion.empty());
    ASSERT_EQ(true, v._virusNamesStar.empty());
    ASSERT_EQ(true, v._virusNamesBracket.empty());
    ASSERT_EQ(true, v._signaturesWithQuestion.empty());
    ASSERT_EQ(true, v._signaturesWithStar.empty());
    ASSERT_EQ(true, v._signaturesWithBracket.empty());
  }

  // signature with question mark
  {
    VirusScan v;
    string name = "bla";
    string sig = "6e6574207368617265202f64656c6574652049504324????6e657420737"
      "6f7020226e657462696f7322";
    v.checkSignature(sig, name);
    ASSERT_EQ(name, v._virusNamesQuestion[0]);
    ASSERT_EQ(sig, v._signaturesWithQuestion[0]);
    ASSERT_EQ(true, v._virusNames.empty());
    ASSERT_EQ(true, v._virusNamesStar.empty());
    ASSERT_EQ(true, v._virusNamesBracket.empty());
    ASSERT_EQ(true, v._virusSignatures.empty());
    ASSERT_EQ(true, v._signaturesWithStar.empty());
    ASSERT_EQ(true, v._signaturesWithBracket.empty());
  }

  // signature with star
  {
    VirusScan v;
    string name = "bla";
    string sig = "750030004400300044002500750030004400300044*3c00490046005200";
    v.checkSignature(sig, name);
    ASSERT_EQ(sig, v._signaturesWithStar[0]);
    ASSERT_EQ(name, v._virusNamesStar[0]);
    ASSERT_EQ(true, v._virusNames.empty());
    ASSERT_EQ(true, v._virusNamesQuestion.empty());
    ASSERT_EQ(true, v._virusNamesBracket.empty());
    ASSERT_EQ(true, v._virusSignatures.empty());
    ASSERT_EQ(true, v._signaturesWithQuestion.empty());
    ASSERT_EQ(true, v._signaturesWithBracket.empty());
  }

  // signature with brackets
  {
    VirusScan v;
    string name = "bla";
    string sig = "456c7365496620442e4974656d282250756e7922292e4e616d65203c3e2"
      "e{-10}4e282250756e7922292e4578706f72742022633a5c50756e792e73797322";
    v.checkSignature(sig, name);
    ASSERT_EQ(name, v._virusNamesBracket[0]);
    ASSERT_EQ(sig, v._signaturesWithBracket[0]);
    ASSERT_EQ(true, v._virusNames.empty());
    ASSERT_EQ(true, v._virusNamesQuestion.empty());
    ASSERT_EQ(true, v._virusNamesStar.empty());
    ASSERT_EQ(true, v._virusSignatures.empty());
    ASSERT_EQ(true, v._signaturesWithQuestion.empty());
    ASSERT_EQ(true, v._signaturesWithStar.empty());
  }
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
  ASSERT_EQ("_0017_0001_000", v._virusNames[0]);
  ASSERT_EQ("21b8004233c999cd218bd6b90300b440cd218b4c198b541bb80157cd21b43ec"
    "d2132ed8a4c18", v._virusSignatures[0]);
  ASSERT_EQ("_0017_0001_001", v._virusNames[1]);
  ASSERT_EQ("b3005a8b4e27b440cd21e8c2045a59b440cd21e81902b440cd21b8004233c99"
    "9cd218bd6b90300", v._virusSignatures[1]);

  remove(virusSignaturesFileName);
}

// ____________________________________________________________________________
TEST(VirusScanTest, readInputFile) {
  // make tmp input file for test
  const char* inputfileName = "input.TMP.txt";
  FILE* inputFile = fopen(inputfileName, "w");
  fprintf(inputFile, "Hello\n");
  fclose(inputFile);

  VirusScan v;
  int argc = 4;
  char* argv[4] = {
    const_cast<char*>("prog"),
    const_cast<char*>("--virusSignatures=virus-signatures.TMP.txt"),
    const_cast<char*>("--log-file=log.TMP.txt"),
    const_cast<char*>("input.TMP.txt")
  };

  v.parseCommandLineArguments(argc, argv);
  ASSERT_STREQ("virus-signatures.TMP.txt", v._virusSignaturesFileName);
  ASSERT_STREQ("log.TMP.txt", v._logFileName);
  ASSERT_STREQ("input.TMP.txt", v._inputFileNames[0]);

  v.readInputFile(v._inputFileNames[0]);
  ASSERT_EQ('H', v._buffer[0]);
  ASSERT_EQ('e', v._buffer[1]);
  ASSERT_EQ('l', v._buffer[2]);
  ASSERT_EQ('l', v._buffer[3]);
  ASSERT_EQ('o', v._buffer[4]);
  ASSERT_EQ('\n', v._buffer[5]);
  remove(inputfileName);
}


// ____________________________________________________________________________
// TEST(VirusScanTest, isInfected) {
//   string name = "ClamAV-Test-Signature";
//   string sig = "2443456c6961636d615472455354755363696b67736e24465245452"
//     "d544553542d5349474e415455524524454545454524";
//   // make tmp input file for test
//   char* inputfileName = "input.TMP.txt";
//   FILE* inputFile = fopen(inputfileName, "w");
//   fprintf(inputFile, "bla$cE$CEliacmaTrESTuScikgsn$FREE-TEST-SIGNATURE$EEEEE"
//     "blubb");
//   fclose(inputFile);

//   VirusScan v;
//   v._inputFileNames[0] = inputfileName;
//   v._virusSignatures[0] = sig;
//   v._virusNames[0] = name;
//   v.scanInputFile();
//   ASSERT_EQ(true, _infected);
// }

// ____________________________________________________________________________
TEST(VirusScanTest, howMany) {
  const char* virusSignaturesFile = "virus-signatures.txt";
  VirusScan v;
  v.readVirusSignatures(virusSignaturesFile);
  v.howMany();
}
