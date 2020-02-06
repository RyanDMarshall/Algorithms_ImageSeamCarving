#include "Matrix.h"
#include "test_helpers.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;


// This is the public Matrix test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Matrix module.
// It will only really tell you if your code compiles and you remembered to
// write the functions. It is not to be trusted. It tells the truth, but not
// the whole truth. It might put you in a blender. You get the point.
// You must write your own comprehensive unit tests in Matrix_tests.cpp!


int main() {
  Matrix mat;
  Matrix_init(&mat, 5, 5);

  assert(Matrix_width(&mat) == 5);
  assert(Matrix_height(&mat) == 5);

  Matrix_fill(&mat, 0);

  int *ptr = Matrix_at(&mat, 2, 3);
  assert(Matrix_row(&mat, ptr) == 2);
  assert(Matrix_column(&mat, ptr) == 3);
  assert(*ptr == 0);
  *ptr = 42;

  const int *cptr = Matrix_at(&mat, 2, 3);
  assert(*cptr == 42);

  Matrix_fill_border(&mat, 2);
  assert(*Matrix_at(&mat, 0, 0) == 2);

  assert(Matrix_max(&mat) == 42);

  Matrix_init(&mat, 1, 1);
  *Matrix_at(&mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  assert(expected.str() == actual.str());

  cout << "Matrix_public_test PASS" << endl;
}
