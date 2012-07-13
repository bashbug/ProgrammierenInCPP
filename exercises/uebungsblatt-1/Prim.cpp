// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

// Compute whether the given number is a prime number.
bool isPrim(int num) {
    // Even numbers aren't prime numbers.
    if (num % 2 == 0) {
        return false;
    }
    
    // Check whether the number hasn't a remainder for numbers from 3 to itself.
    for (int i = 3; i < num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}
