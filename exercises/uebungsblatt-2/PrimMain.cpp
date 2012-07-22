// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "./Prim.h"

int main(int argc, char** argv) {
    int num = atoi(argv[1]);

    // Test whether the argument is a legal number.
    if (num > INT_MAX) {
        printf("Usage: ./PrimMain <only numbers till %d>\n", INT_MAX);
        exit(1);
    }

    // Compute whether the argument is a prime number.
    if (isPrim(num) == true) {
        printf("Number %d is a prime number.\n", num);
    } else {
        printf("Number %d is not a prime number.\n", num);
    }
}
