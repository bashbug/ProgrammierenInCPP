// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./String.h"
#include "./Grep.h"

// _____________________________________________________________________________
TEST(GrepTest, Grep) {
  Grep g;
  ASSERT_TRUE(NULL == g._inputFile);
  ASSERT_TRUE(NULL == g._outputFile);
  ASSERT_TRUE(NULL == g._replace);
}

// _____________________________________________________________________________
TEST(GrepTest, parseCommandLineArguments) {
  Grep g;
  // Test with all options and arguments
  {
    int argc = 5;
    char* argv[5] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--input-file=input.txt"),
      const_cast<char*>("--output-file=output.txt"),
      const_cast<char*>("--replace-with=Katze"),
      const_cast<char*>("Maus")
    };
    g.parseCommandLineArguments(argc, argv);
    ASSERT_STREQ("input.txt", g._inputFile);
    ASSERT_STREQ("output.txt", g._outputFile);
    ASSERT_STREQ("Katze", g._replace);
    ASSERT_STREQ("Maus", g._pattern);
  }

  // Test default
  {
    int argc = 2;
    char* argv[2] = {
      const_cast<char*>("prog"),
      const_cast<char*>("Maus")
    };
    g.parseCommandLineArguments(argc, argv);
    ASSERT_TRUE(g._inputFile == NULL);
    ASSERT_TRUE(g._outputFile == NULL);
    ASSERT_TRUE(g._replace == NULL);
    ASSERT_STREQ("Maus", g._pattern);
  }

  // Test without options and without arguments.
  {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    int argc = 1;
    char* argv[1] = {
      const_cast<char*>("prog")
    };
    ASSERT_DEATH(g.parseCommandLineArguments(argc, argv), "Usage:.*");
  }
}

// _____________________________________________________________________________
TEST(GrepTest, processFile) {
  Grep g;

  // Test with all arguments
  {
    const char* inputFileName = "Input.TMP.txt";
    FILE* inputFile = fopen(inputFileName, "w");
    fprintf(inputFile, "Die Katze\nlacht und\njagt die Katze\num das Haus\n");
    fclose(inputFile);

    int argc = 5;
    char* argv[5] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--input-file=Input.TMP.txt"),
      const_cast<char*>("--output-file=Output.TMP.txt"),
      const_cast<char*>("--replace-with=Maus"),
      const_cast<char*>("Katze")
    };

    g.parseCommandLineArguments(argc, argv);
    g.process();

    const char* outputFileName = "Output.TMP.txt";
    FILE* outputFile = fopen(outputFileName, "r");
    const size_t MAX_LINE_LENGTH = 1000;
    char line[MAX_LINE_LENGTH + 1];

    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  1 : Die Maus\n", line);
    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  2 : lacht und\n", line);
    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  3 : jagt die Maus\n", line);
    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  4 : um das Haus\n", line);

    remove(inputFileName);
    remove(outputFileName);
  }

  // Test without replace argument
  {
    const char* inputFileName = "Input.TMP.txt";
    FILE* inputFile = fopen(inputFileName, "w");
    fprintf(inputFile, "Die Katze\nlacht und\njagt die Katze\num das Haus\n");
    fclose(inputFile);

    int argc = 4;
    char* argv[4] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--input-file=Input.TMP.txt"),
      const_cast<char*>("--output-file=Output.TMP.txt"),
      const_cast<char*>("Katze")
    };

    g.parseCommandLineArguments(argc, argv);
    g.process();

    const char* outputFileName = "Output.TMP.txt";
    FILE* outputFile = fopen(outputFileName, "r");
    const size_t MAX_LINE_LENGTH = 1000;
    char line[MAX_LINE_LENGTH + 1];

    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  1 : Die Katze\n", line);
    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  2 : jagt die Katze\n", line);

    remove(inputFileName);
    remove(outputFileName);
  }

  // Test invert argument
  {
    const char* inputFileName = "Input.TMP.txt";
    FILE* inputFile = fopen(inputFileName, "w");
    fprintf(inputFile, "Die Katze\nlacht und\njagt die Katze\num das Haus\n");
    fclose(inputFile);

    int argc = 5;
    char* argv[5] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--input-file=Input.TMP.txt"),
      const_cast<char*>("--output-file=Output.TMP.txt"),
      const_cast<char*>("--invert-match"),
      const_cast<char*>("Katze")
    };

    g.parseCommandLineArguments(argc, argv);
    g.process();

    const char* outputFileName = "Output.TMP.txt";
    FILE* outputFile = fopen(outputFileName, "r");
    const size_t MAX_LINE_LENGTH = 1000;
    char line[MAX_LINE_LENGTH + 1];

    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  1 : lacht und\n", line);
    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_STREQ("  2 : um das Haus\n", line);

    remove(inputFileName);
    remove(outputFileName);
  }

  // Test count with invert == false
  {
    const char* inputFileName = "Input.TMP.txt";
    FILE* inputFile = fopen(inputFileName, "w");
    fprintf(inputFile, "Die Katze\nlacht und\njagt die Katze\num das Haus\n");
    fclose(inputFile);

    int argc = 5;
    char* argv[5] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--input-file=Input.TMP.txt"),
      const_cast<char*>("--output-file=Output.TMP.txt"),
      const_cast<char*>("--count"),
      const_cast<char*>("Katze")
    };

    g.parseCommandLineArguments(argc, argv);
    g.process();

    const char* outputFileName = "Output.TMP.txt";
    FILE* outputFile = fopen(outputFileName, "r");
    const size_t MAX_LINE_LENGTH = 1000;
    char line[MAX_LINE_LENGTH + 1];

    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_TRUE(g._count);
    ASSERT_FALSE(g._invert);
    ASSERT_STREQ("2\n", line);

    remove(inputFileName);
    remove(outputFileName);
  }

  // Test count with invert == true
  {
    const char* inputFileName = "Input.TMP.txt";
    FILE* inputFile = fopen(inputFileName, "w");
    fprintf(inputFile, "Die Katze\nlacht und\njagt die Katze\num das Haus\n");
    fclose(inputFile);

    int argc = 6;
    char* argv[6] = {
      const_cast<char*>("prog"),
      const_cast<char*>("--input-file=Input.TMP.txt"),
      const_cast<char*>("--output-file=Output.TMP.txt"),
      const_cast<char*>("--invert-match"),
      const_cast<char*>("--count"),
      const_cast<char*>("Katze")
    };

    g.parseCommandLineArguments(argc, argv);
    g.process();

    const char* outputFileName = "Output.TMP.txt";
    FILE* outputFile = fopen(outputFileName, "r");
    const size_t MAX_LINE_LENGTH = 1000;
    char line[MAX_LINE_LENGTH + 1];

    fgets(line, MAX_LINE_LENGTH, outputFile);
    ASSERT_TRUE(g._count);
    ASSERT_TRUE(g._invert);
    ASSERT_STREQ("2\n", line);

    remove(inputFileName);
    remove(outputFileName);
  }
}
