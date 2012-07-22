// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef UEBUNGSBLATT_11_VIRUSSCAN_H_
#define UEBUNGSBLATT_11_VIRUSSCAN_H_

#include <gtest/gtest.h>
#include <string>
#include <vector>

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
  // --log-file, -l : contains logging information
  // argument/s without options will be interpreted as inputfile/s
  void parseCommandLineArguments(int argc, char** argv);
  FRIEND_TEST(VirusScanTest, parseCommandLineArguments);

  // read the file, which contains the virus signatures.
  void readVirusSignatures(const char* inputFileName);
  FRIEND_TEST(VirusScanTest, readVirusSignatures);

  // read Inputfile as binary hex code and put the lines in a vector.
  void readInputFile(const char* inputFile);
  FRIEND_TEST(VirusScanTest, readInputFile);

  // scan Inputfile for viruses.
  void scanInputFile(vector<string> virusSignatures, vector<string> input,
    vector<string>* infectedFiles, vector<string>* cleanFiles);
  FRIEND_TEST(VirusScanTest, scanInputFile);

  // prints logging information on the screen and in an output file
  // during the file scanning.
  void writeLogfile(const char* logfile);
  FRIEND_TEST(VirusScanTest, writeLogfile);

  // output which contains information about scanning time, infected files
  // and clean files.
  void writeStatistic();

 private:
  // print usage info and exit.
  void printUsageAndExit();

  // split the virus-signatures.txt in a name and a signature vector.
  void splitVirusSignatureFile();
  FRIEND_TEST(VirusScanTest, splitVirusSignatureFile);

  // check if a signature has special operators like '?*',
  // and handle it.
  void checkSignature();
  FRIEND_TEST(VirusScanTest, checkSignature);

  // returns true, if an virus signature is matching with a line of
  // the input file.
  bool isInfected(char _signature, char _inputFile,
    vector<string>* infectedFiles);
  FRIEND_TEST(VirusScanTest, isInfected);

  // name of the file, which contains name and signature of each virus.
  char* _virusSignaturesFileName;
  // name of the logfile, set from user at commandline
  char* _logFileName;
  // vector contains all filenames from the commandline
  vector<char*> _inputFileNames;

  // stores the name of all viruses
  vector<string> _virusNames;
  // hex-sequenz of every virus signature
  vector<string> _virusSignatures;
  // current hex signature for scanning
  char* _signature;
  // the name of an specific virus
  char* _virus;

  // the hex-sequenz of the inputfile
  vector<string> _inputFile;
  // current line of the input file for scanning
  char* _inputLine;

  // stores filenames of all infected files
  vector<string> _infectedFiles;
  // stores filenames of all clean files
  vector<string> _cleanFiles;
  // shows how long the scann takes
  long double _scanningTime;
};

#endif  // UEBUNGSBLATT_11_VIRUSSCAN_H_
