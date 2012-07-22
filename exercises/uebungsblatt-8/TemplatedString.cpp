// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include "./TemplatedString.h"

template<class T> TemplatedString<T>::TemplatedString() {
  _contents = NULL;
  _length = 0;
}

template<class T> TemplatedString<T>::~TemplatedString() {
  delete[] _contents;
}

// ____________________________________________________________________________
template <class T>
void TemplatedString<T>::resize(size_t size, T x) {
  T* newContents;
  if (size <= _length) {
    _length = size;
    newContents = new T[_length + 1];
    for (size_t i = 0; i < _length; i++) {
      newContents[i] = _contents[i];
    }
  } else {
    size_t oldlength = _length;
    _length = size;
    newContents = new T[_length + 1];
    // fills with the old contents
    for (size_t i = 0; i < oldlength; i++) {
      newContents[i] = _contents[i];
    }
    // fills the rest with given x
    for (size_t i = oldlength; i < _length; i++) {
      newContents[i] = x;
    }
  }

  delete[] _contents;
  _contents = newContents;
}

// ____________________________________________________________________________
template <class T>
void TemplatedString<T>::set(size_t pos, T x) {
  // fills the array until position < pos
  T* newContents = new T[_length + 1];
  for (size_t i = 0; i < pos; i++) {
    newContents[i] = _contents[i];
  }
  // set x at the right array position
  newContents[pos] = x;
  // fills the rest with the old array content
  for (size_t i = pos + 1; i < _length; i++) {
    newContents[i] = _contents[i];
  }

  delete[] _contents;
  _contents = newContents;
}

// Explicit instantiation for char and int.
template class TemplatedString<char>;
template class TemplatedString<int>;

// Specialization for TemplatedString<bool>.
TemplatedString<bool>::TemplatedString() {
  // for (int i = 0; i < 8; i++) _contents[i] = 0;
  _contents = NULL;
  _length = 0;
  _numBytes = 0;
}

TemplatedString<bool>::~TemplatedString() {
  delete[] _contents;
}

// ____________________________________________________________________________
void TemplatedString<bool>::resize(size_t bit, bool x) {
  // Check, how many bit are needed.
  size_t neededBytes = 0;
  if (bit % 8 == 0) {
    neededBytes = (bit / 8) - _numBytes;  // No new byte is needed.
  } else {
    neededBytes = (bit / 8) - _numBytes + 1;
  }

  if (_length % 8 == 0) {  // 8 bit are already in use.
    char* newContents = new char[_numBytes + neededBytes];

    // new content bits are set false.
    for (size_t i = 0; i < _numBytes + neededBytes; i++) {
      newContents[i] = 0;
    }
    // Copys the old content in the new content.
    for (size_t i = 0; i < _numBytes; i++) {
      newContents[i] = _contents[i];
    }

    if (x == true && bit > _length) {
      size_t setBits = bit - _length;  // How many bits should be set.
      size_t currentNumByte = _numBytes;
      // Fills the new bytes.
      for (size_t i = currentNumByte; i <= neededBytes; i++) {;
        // Fills a byte until his max length = 8 bit.
        for (size_t k = 0; k < 8; k++) {
          newContents[currentNumByte] |= (1 << k % 8);
          setBits--;
          // If all setBits are set, then the loop should be interrupted.
          if (setBits == 0) break;
        }
        currentNumByte++;
      }
    }

    delete[] _contents;
    _contents = newContents;
  } else {  // Still space in the last byte.
    if (x == true) {
      for (size_t i = 0; i <= bit - _length; i++) {
        _contents[_numBytes - 1] |= (1 << i % 8);
      }
    }
  }
  _length = bit;
  _numBytes = _numBytes + neededBytes;
}
