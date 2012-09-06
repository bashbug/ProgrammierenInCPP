// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef VIRUSSCAN_SIGNATURESLIST_H_
#define VIRUSSCAN_SIGNATURESLIST_H_

#include <gtest/gtest.h>
#include <string>
#include <map>

using std::string;
using std::map;

class SignaturesList {
 private:
  map<unsigned char, SignaturesList* > _root;
  map<unsigned char, SignaturesList* >::iterator _itRoot;
  bool _endOfSignature;
  string _virusName;

 public:
  SignaturesList();
  ~SignaturesList();
  FRIEND_TEST(SignaturesListTest, SignaturesList);

  void id();

  void printPointers();

  string virusName();

  SignaturesList* getPointer(unsigned char c);

  bool end();

  int size();

  void add(string signature, const string& name);
  FRIEND_TEST(SignaturesListTest, add);

  bool exists(string str);
  // FRIEND_TEST(SignaturesListTest, check);

  int hexToDec(string str);
  FRIEND_TEST(SignaturesListTest, hexToDec);
};

#endif  // VIRUSSCAN_SIGNATURESLIST_H_
