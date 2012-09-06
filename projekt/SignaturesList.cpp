// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include "./SignaturesList.h"

using std::string;
using std::stringstream;
using std::ios;
using std::map;

SignaturesList::SignaturesList() {
  _endOfSignature = false;
}

SignaturesList::~SignaturesList() {}

void SignaturesList::id() {
  std::cout << "Class-ID: " << this << std::endl;
}

SignaturesList* SignaturesList::getPointer(unsigned char c) {
  _itRoot = _root.find(c);
  if (_itRoot == _root.end()) {
    return NULL;
  } else {
    return _root[c];
  }
}

string SignaturesList::virusName() {
  return _virusName;
}

bool SignaturesList::end() {
  return _endOfSignature;
}

void SignaturesList::add(string signature, const string& name) {
  if (signature.length() == 0) {
    _virusName = name;
    _endOfSignature = true;
    return;
  }

  if (signature.substr(0, 1)[0] == '*') {
    signature.replace(0, 1, "");
  }

  if (signature.find('{') != string::npos) {
    int start = signature.find('{');
    int end = signature.find('}');
    signature.replace(start, end - start + 1, "");
  }

  if (signature.find('(') != string::npos) {
    int start = signature.find('(');
    int end = signature.find('(');
    signature.replace(start, end - start + 1, "");
  }

  if (signature.substr(0, 2).find('?') != string::npos) {
    signature.replace(0, 2, "");
  }

  int val = hexToDec(signature.substr(0, 2));
  _itRoot = _root.find(val);

  signature.replace(0, 2, "");
  if (_itRoot != _root.end()) {
    return _itRoot->second->add(signature, name);
  } else {
    SignaturesList* s = new SignaturesList();
    _root[val] = s;
    // _itRoot->second = s;
    return s->add(signature, name);
  }
}

bool SignaturesList::exists(string str) {
  int val = hexToDec(str.substr(0, 2));

  if (str.length() == 0 && end() == true) {
    return true;
  }

  _itRoot = _root.find(val);

  if (_itRoot != _root.end()) {
    return _itRoot->second->exists(str.substr(2));
  } else {
    return false;
  }
}

int SignaturesList::size() {
  return _root.size();
}

int SignaturesList::hexToDec(string str) {
  int dec;
  stringstream ss;

  ss.str("");
  ss.clear();
  ss << std::hex << str;
  ss >> dec;

  return dec;
}
