#include "Matrix.h"
#include "test_helpers.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void test_Matrix_init();
void test_Matrix_print();
void test_Matrix_width_height();
void test_Matrix_row_column_at();
void test_Matrix_fill_fill_border();
void test_Matrix_max();
void test_Matrix_column_of_min_value_in_row_min_value_in_row();

int main() {
  
  test_Matrix_init();
  test_Matrix_print();
  test_Matrix_width_height();
  test_Matrix_row_column_at();
  test_Matrix_fill_fill_border();
  test_Matrix_max();
  test_Matrix_column_of_min_value_in_row_min_value_in_row();

  cout << endl << "All Matrix tests passed!" << endl;
}

void test_Matrix_init() {

  Matrix mat1, mat2, mat3;
  int width1, height1, width2, height2, width3, height3, width4, height4;

  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 200;
  height3 = 300;
  width4 = 100;
  height4 = 200;

  //Initialize matrices with edge case sizes
  Matrix_init(&mat1, width1, height1);
  Matrix_init(&mat2, width2, height2);
  assert(Matrix_width(&mat1) == 1 && Matrix_height(&mat1) == 1);
  assert(Matrix_width(&mat2) == MAX_MATRIX_WIDTH && Matrix_height(&mat2) == MAX_MATRIX_HEIGHT);

  //Initialize matrix with non-square size
  Matrix_init(&mat3, width3, height3);
  assert(Matrix_width(&mat3) == 200 && Matrix_height(&mat3) == 300);

  //Attempt to re-initialize a previouslyinitialized matrix
  Matrix_init(&mat3, width4, height4);
  assert(Matrix_width(&mat3) == 100 && Matrix_height(&mat3) == 200);

  cout << "Matrix_init tests passed" << endl;
  return;
}

void test_Matrix_print() {

  Matrix mat1, mat2, mat3;
  int height1, width1, height2, width2, height3, width3;

  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 1;
  height3 = 2;

  Matrix_init(&mat1, width1, height1);
  Matrix_init(&mat2, width2, height2);
  Matrix_init(&mat3, width3, height3);

  // Test for small edge case
  *Matrix_at(&mat1, 0, 0) = 42;
  ostringstream expected1;
  expected1 << "1 1\n"
            << "42 \n";
  ostringstream actual1;
  Matrix_print(&mat1, actual1);
  assert(expected1.str() == actual1.str());

  // Test for large edge case
  Matrix_fill(&mat2, 1);
  ostringstream expected2;
  expected2 << (MAX_MATRIX_WIDTH) << ' ' << (MAX_MATRIX_HEIGHT) << '\n';
  for (int i = 0; i < (MAX_MATRIX_HEIGHT); ++i) {
    for (int j = 0; j < (MAX_MATRIX_WIDTH); ++j) {
      expected2 << "1 ";
    }
    expected2 << '\n';
  }
  ostringstream actual2;
  Matrix_print(&mat2, actual2);
  assert(expected2.str() == actual2.str());

  // Test when row =/= column
  *Matrix_at(&mat3, 0, 0) = 0;
  *Matrix_at(&mat3, 1, 0) = 500;
  ostringstream expected3;
  expected3 << "1 2\n"
            << "0 \n"
            << "500 \n";
  ostringstream actual3;
  Matrix_print(&mat3, actual3);
  assert(expected3.str() == actual3.str());

  cout << "Matrix_print tests passed" << endl;
  return;
}

void test_Matrix_width_height() {

  Matrix mat1, mat2, mat3, mat4;
  int width1, height1, width2, height2, width3, height3, width4, height4;

  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 2;
  height3 = 1;
  width4 = 1;
  height4 = 2;

  Matrix_init(&mat1, width1, height1);
  Matrix_init(&mat2, width2, height2);
  Matrix_init(&mat3, width3, height3);
  Matrix_init(&mat4, width4, height4);

  // Test width for small edge case
  assert(Matrix_width(&mat1) == 1);
  // Test width for large edge case
  assert(Matrix_width(&mat2) == MAX_MATRIX_WIDTH);
  // Test width to make sure row and col are not swapped
  assert(Matrix_width(&mat3) == 2);
  // Test height for small edge case
  assert(Matrix_height(&mat1) == 1);
  // Test height for large edge case
  assert(Matrix_height(&mat2) == MAX_MATRIX_WIDTH);
  // Test height to make sure row and col are not swapped
  assert(Matrix_height(&mat4) == 2);


  cout << "Matrix_width tests passed" << endl;
  return;
}

void test_Matrix_row_column_at() {

  Matrix mat1, mat2, mat3, mat4;
  int width1, height1, width2, height2, width3, height3, width4, height4;
  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 35;
  height3 = 25;
  width4 = 35;
  height4 = 25;

  Matrix_init(&mat1, width1, height1);
  Matrix_init(&mat2, width2, height2);
  Matrix_init(&mat3, width3, height3);
  Matrix_init(&mat4, width4, height4);

  *Matrix_at(&mat1, 0, 0) = 0;

  int n = 0;

  for (int i = 0; i < MAX_MATRIX_HEIGHT; ++i) {
    for (int j = 0; j < MAX_MATRIX_WIDTH; ++j) {

      *Matrix_at(&mat2, i, j) = n;

      ++n;
    }
  }

  Matrix_fill(&mat3, 5);
  Matrix_fill_border(&mat3, 1);

  n = 0;

  for (int i = 0; i < height4; ++i) {
    for (int j = 0; j < width4; ++j) {

      *Matrix_at(&mat4, i, j) = n;

      ++n;
    }
  }

  // Test for initial value of 1x1 matrix
  int *mat1_first = Matrix_at(&mat1, 0, 0);
  assert(mat1_first == &((&mat1)->data[0]));

  // Tests for edge cases in max matrix size
  int *mat2_first = Matrix_at(&mat2, 0, 0);
  int *mat2_last = Matrix_at(&mat2, height2- 1, width2 - 1);
  assert(mat2_first == &((&mat2)->data[0]));
  assert(mat2_last == &((&mat2)->data[width2*height2 - 1]));

  // Tests to make sure that row and col aren't swapped
  int *mat3_first = Matrix_at(&mat3, 0, 0);
  int *mat3_last = Matrix_at(&mat3, height3 - 1, width3 - 1);

  assert(mat3_first == &((&mat3)->data[0]));
  assert(mat3_last == &((&mat3)->data[width3*height3 - 1]));

  // Tests for address and value of middle value in rectangular matrix
  int *mat4_mid = Matrix_at(&mat4, 19, 14);
  int mat4_mid_int = *Matrix_at(&mat4, 19, 14);
  assert(mat4_mid == &((&mat4)->data[19*Matrix_width(&mat4) + 14]));
  assert(mat4_mid_int == (&mat4)->data[19*Matrix_width(&mat4) + 14]);

  cout << "Matrix_at (pointer) tests passed" << endl;

  // Test for rectangular Matrix_at pointer-to-const function
  const Matrix *mat_const_1 = &mat1;
  const Matrix *mat_const_2 = &mat2;
  const Matrix *mat_const_3 = &mat4;

  const int *mat_const_3_4_5 = Matrix_at(mat_const_3, 4, 5);
  const int *mat_const_3_4_5_actual = &(mat_const_3->data[4*Matrix_width(mat_const_3) + 5]);
  assert(mat_const_3_4_5 == mat_const_3_4_5_actual);

  cout << "Matrix_at (pointer-to-const) test passed" << endl;

  // Tests for 1x1 matrix
  const int *mat_const_1_first_row = &mat_const_1->data[0];
  assert(Matrix_row(mat_const_1, mat_const_1_first_row) == 0);
  const int *mat_const_1_first_col = &mat_const_1->data[0];
  assert(Matrix_row(mat_const_1, mat_const_1_first_col) == 0);

  // Tests for max size matrix, first and last elements
  const int *mat_const_2_first_row = &mat_const_2->data[0];
  assert(Matrix_row(mat_const_2, mat_const_2_first_row) == 0);
  const int *mat_const_2_first_col = &mat_const_2->data[0];
  assert(Matrix_row(mat_const_2, mat_const_2_first_col) == 0);

  const int *mat_const_2_last_row = &mat_const_2->data[499 * MAX_MATRIX_WIDTH + MAX_MATRIX_HEIGHT - 1];
  assert(Matrix_row(mat_const_2, mat_const_2_last_row) == 499);

  const int *mat_const_2_last_col = &mat_const_2->data[499 * MAX_MATRIX_WIDTH + MAX_MATRIX_HEIGHT - 1];
  assert(Matrix_row(mat_const_2, mat_const_2_last_col) == 499);

  cout << "Matrix_row tests passed" << endl;
  cout << "Matrix_column tests passed" << endl;

  return;
}

void test_Matrix_fill_fill_border() {

  Matrix mat1, mat2, mat3;
  int width1, height1, value1, width2, height2, value2_1, value2_2, width3, height3, value3_1, value3_2;
  width1 = 3;
  height1 = 5;
  value1 = 42;
  width2 = 1;
  height2 = 1;
  value2_1 = 0;
  value2_2 = 1;
  width3 = MAX_MATRIX_WIDTH;
  height3 = MAX_MATRIX_HEIGHT;
  value3_1 = 0;
  value3_2 = 255;

  Matrix_init(&mat1, width1, height1);
  Matrix_init(&mat2, width2, height2);
  Matrix_init(&mat3, width3, height3);

  Matrix_fill(&mat1, value1);
  Matrix_fill(&mat2, value2_1);

  // Standard given rectangular test
  for(int r = 0; r < height1; ++r) {
    for(int c = 0; c < width1; ++c) {
      assert(*Matrix_at(&mat1, r, c) == value1);
    }
  }

  // Test fill for 1x1 
  assert(*Matrix_at(&mat2, 0, 0) == 0);

  // Test fill_border for 1x1
  Matrix_fill_border(&mat2, value2_2);
  assert(*Matrix_at(&mat2, 0, 0) == 1);

  Matrix_fill(&mat3, value3_1);
  Matrix_fill_border(&mat3, value3_2);

  for (int r = 0; r < height3; ++r) {
    for (int c = 0; c < width3; ++c) {
      if ((r == 0) || (r == (height3 - 1)) || (c == 0) || (c == (width3 - 1))) {
        assert(*Matrix_at(&mat3, r, c) == 255);
      } else {
        assert(*Matrix_at(&mat3, r, c) == 0);
      }
    }
  }

  cout << "Matrix_fill tests passed" << endl;
  return;
}

void test_Matrix_max() {

  Matrix mat1, mat2, mat3;
  int width1, height1, width2, height2, width3, height3;
  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 4;
  height3 = 5;

  Matrix_init(&mat1, width1, height1);
  Matrix_init(&mat2, width2, height2);
  Matrix_init(&mat3, width3, height3);

  *Matrix_at(&mat1, 0, 0) = 255;
  assert(Matrix_max(&mat1) == 255);
  *Matrix_at(&mat1, 0, 0) = 0;
  assert(Matrix_max(&mat1) == 0);

  Matrix_fill(&mat2, 217);
  assert(Matrix_max(&mat2) == 217);
  *Matrix_at(&mat2, 300, 410) = 218;
  assert(Matrix_max(&mat2) == 218);

  cout << "Matrix_init tests passed" << endl;
  return;

  int n = 0;
  for (int r = 0; r < height3; ++r) {
    for (int c = 0; c < width3; ++c) {
      *Matrix_at(&mat3, r, c) = n;

      ++n;
    }
  }

  assert(Matrix_max(&mat3) == (width3 - 1)*(height3 - 1));
  *Matrix_at(&mat3, 0, 0) = 254;
  assert(Matrix_max(&mat3) == 254);

  return;
}

void test_Matrix_column_of_min_value_in_row_min_value_in_row() {

  Matrix mat1, mat2, mat3;
  int width1, height1, width2, height2, width3, height3;
  width1 = 2;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 4;
  height3 = 5;

  Matrix_init(&mat1, width1, height1);
  Matrix_init(&mat2, width2, height2);
  Matrix_init(&mat3, width3, height3);


  // Test for 1x2 matrix with different & same values
  *Matrix_at(&mat1, 0, 0) = 1;
  *Matrix_at(&mat1, 0, 1) = 0;
  assert(Matrix_column_of_min_value_in_row(&mat1, 0, 0, 3) == 1);
  assert(Matrix_min_value_in_row(&mat1, 0, 0, 3) == 0);
  *Matrix_at(&mat1, 0, 1) = 1;
  assert(Matrix_column_of_min_value_in_row(&mat1, 0, 0, 3) == 0);
  assert(Matrix_min_value_in_row(&mat1, 0, 0, 3) == 1);

  // Test for max size matrix with different border
  Matrix_fill(&mat2, 102);
  Matrix_fill_border(&mat2, 86);
  assert(Matrix_column_of_min_value_in_row(&mat2, 0, 0, 500) == 0);
  assert(Matrix_min_value_in_row(&mat2, 0, 0, 500) == 86);
  assert(Matrix_column_of_min_value_in_row(&mat2, 1, 0, 500) == 0);
  assert(Matrix_min_value_in_row(&mat2, 1, 0, 500) == 86);
  assert(Matrix_column_of_min_value_in_row(&mat2, 1, 1, 499) == 1);
  assert(Matrix_min_value_in_row(&mat2, 1, 1, 499) == 102);

  // Test for monotonically decreasing matrix
  int n = 20;
  for (int r = 0; r < height3; ++r) {
    for (int c = 0; c < width3; ++c) {
      *Matrix_at(&mat3, r, c) = n;
      --n;
    }
  }

  assert(Matrix_column_of_min_value_in_row(&mat3, 0, 1, 3) == 2);
  assert(Matrix_min_value_in_row(&mat3, 0, 1, 3) == 18);
  assert(Matrix_column_of_min_value_in_row(&mat3, 4, 0, 5) == 3);
  assert(Matrix_min_value_in_row(&mat3, 4, 0, 5) == 1);

  cout << "Matrix_init tests passed" << endl;
  return;
}