// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>

#ifndef UEBUNGSBLATT_10_ANIMATEDOBJECT_H_
#define UEBUNGSBLATT_10_ANIMATEDOBJECT_H_

// abstact class for geometric objects
class AnimatedObject {
 public:
  // constructor, which holds the random starting values
  AnimatedObject();
  // default deconstructor
  virtual ~AnimatedObject() {}
  // function, which references the move and draw functions
  // of the subclasses below
  virtual void animationStep();
 protected:
  // protected, because the subclasses are using these
  // variables and functions
  // function, which draws the current object
  void animationDraw();
  // abstract function, which is only implemented
  // from the subclasses
  virtual void animationMove() = 0;
  // is needed for the tests, which sets a
  // fix terminal size
  FRIEND_TEST(AnimationTest, animationMoveCircle);
  FRIEND_TEST(AnimationTest, animationMoveSquare);
  FRIEND_TEST(AnimationTest, animationMoveTriangle);
  int _centerX;
  int _centerY;
  int _posX;
  int _posY;
  int _oldPosX;
  int _oldPosY;
  int _speed;
  double _radius;
};

class AnimatedCircle : public AnimatedObject {
 public:
  // constructor
  AnimatedCircle();
 protected:
  // implements abstract move function from above
  void animationMove();
  FRIEND_TEST(AnimationTest, animationMoveCircle);
 private:
  double _angle;
};

class AnimatedSquare : public AnimatedObject {
 public:
  // constructor
  AnimatedSquare();
 protected:
  // implements abstract move function from above
  void animationMove();
  FRIEND_TEST(AnimationTest, animationMoveSquare);
};

class AnimatedTriangle : public AnimatedObject {
 public:
  // constructor
  AnimatedTriangle();
 protected:
  // implements abstract move function from above
  void animationMove();
  FRIEND_TEST(AnimationTest, animationMoveTriangle);
 private:
  // double is needed for smooth move
  double _doublePosX;
  double _doublePosY;
};

#endif  // UEBUNGSBLATT_10_ANIMATEDOBJECT_H_
