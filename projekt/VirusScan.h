// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef PROJEKT_VIRUSSCAN_H_
#define PROJEKT_VIRUSSCAN_H_

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stack>

using std::vector;
using std::string;

/* ************************************************************************* */
/* class for finding viruses in a given inputfile or files.                  */
/* setup a log file about: scanning time, infected and clean files.          */
/* ************************************************************************* */

class VirusScan {
 public:
  // constructor
  VirusScan();
  FRIEND_TEST(VirusScanTest, VirusScan);

  // deconstructor
  ~VirusScan();

  // parse the command line arguments.
  // --virusSignatures, -v : contains virusname and -signature
  // --log-file, -l : contains logging information
  // argument/s without options will be interpreted as inputfile/s
  void parseCommandLineArguments(int argc, char** argv);
  FRIEND_TEST(VirusScanTest, parseCommandLineArguments);

  // read the file, which contains the virus signatures.
  void readVirusSignatures(const char* inputFileName);
  FRIEND_TEST(VirusScanTest, readVirusSignatures);

  // scan Inputfile for viruses.
  void scanInputFile();
  FRIEND_TEST(VirusScanTest, scanInputFile);

  // read Inputfile as binary hex code and put the lines in a vector.
  void readInputFile(const char* inputFile);
  FRIEND_TEST(VirusScanTest, readInputFile);

  // prints logging information on the screen and in an output file
  // during the file scanning.
  void writeLogfile(const char* logfile);
  FRIEND_TEST(VirusScanTest, writeLogfile);

  // output which contains information about scanning time, infected files
  // and clean files.
  void writeStatistic();

  void howMany();
  FRIEND_TEST(VirusScanTest, howMany);


 private:
  // print usage info and exit.
  void printUsageAndExit();

  // split the virus-signatures.txt in a name and a signature vector.
  void splitVirusSignature(string line);
  FRIEND_TEST(VirusScanTest, splitVirusSignature);

  // check if a signature has special operators like '?*',
  // and handle it.
  void checkSignature(string sig, string name);
  FRIEND_TEST(VirusScanTest, checkSignature);

  // returns true, if an virus signature is matching with a line of
  // the input file.
  bool isInfected(char* buffer);
  FRIEND_TEST(VirusScanTest, isInfected);

  // name of the file, which contains name and signature of each virus.
  char* _virusSignaturesFileName;
  // name of the logfile, set from user at commandline
  char* _logFileName;
  // contains all filenames from the commandline
  vector<char*> _inputFileNames;
  // name of the current inpute file
  char* _inputFileName;

  // current hex signature for scanning
  char* _signature;
  // the name of an specific virus
  char* _virus;
  // stores the name of normal viruses
  vector<string> _virusNames;
  // stores the name of special viruses
  vector<string> _virusNamesQuestion;
  vector<string> _virusNamesStar;
  vector<string> _virusNamesBracket;
  // hex-sequenz of every virus signature
  vector<string> _virusSignatures;
  // signatures with special operatores '?*{}'.
  vector<string> _signaturesWithQuestion;
  vector<string> _signaturesWithStar;
  vector<string> _signaturesWithBracket;

  // the byte-sequenz of the inputfile
  char* _buffer;

  // stores filenames of all infected files
  vector<string> _infectedFiles;
  // stores filenames of all clean files
  vector<string> _cleanFiles;
  // is true, if an inputFile is infected
  bool _infected;
  // shows how long the scann takes
  long double _scanningTime;
};

#endif  // PROJEKT_VIRUSSCAN_H_
