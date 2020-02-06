#include <cassert>
#include "Matrix.h"

using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
void Matrix_init(Matrix* mat, int width, int height) {

  mat->width = width;
  mat->height = height;
  

  return;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {

  os << mat->width << " " << mat->height << std::endl;

  for(int i = 0; i < mat->width * mat->height; ++i)
  {

    os << mat->data[i] << " ";
    
    if((i + 1) % mat->width == 0)
    {
      os << std::endl;
    }
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  double dis = ptr - &(mat->data[0]); //calculate memory space between ptr and first element of the matrix
  int row = (int)(dis / mat->width);
  return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  int dis = ptr - &(mat->data[0]);
  int column = (dis) % mat->width;
  return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  int pos = row * (mat->width) + column;
  int* ptr = &(mat->data[0]) + pos;
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  int pos = row * (mat->width) + column;
  const int* ptr = &(mat->data[0]) + pos;
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for(int i = 0; i < mat->width * mat->height; ++i)
  {
    mat->data[i] = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  // Fill out top
  for(int i = 0; i < mat->width; ++i)
  {
    mat->data[i] = value;
  }
  // Fill out sides
  for(int j = 1; j < mat->height; ++j)
  {
    mat->data[j * mat->width] = value;
    mat->data[j * mat->width - 1] = value;
  }
  for(int k = 0; k < mat->width; ++k)
  {
    mat->data[(mat->height - 1) * mat->width + 1 + k] = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max = mat->data[0];
  for(int i = 1; i < mat->width * mat->height; ++i)
  {
    if(mat->data[i] > max)
    {
      max = mat->data[i];
    } 
  }
  return max;
}

// REQUIES: mat points to a valid Matrix
//          0 <= row && row < Matrix_height(mat)
//          0 <= column_start && column_end <= Matrix_width(mat)
//          column_start < column_end
// EFFECTS: Returns the column of the element with the minimal value
//          in a particular region. The region is defined as elements
//          in the given row and between column_start (inclusive) and
//          column_end (exclusive).
//          If multiple elements are minimal, returns the column of
//          the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  int pos_start = row * mat->width + column_start;
  int pos_end = row * mat->width + column_end;
  int min = mat->data[pos_start];
  int min_column = column_start;
  for (int i = pos_start; i < pos_end; ++i)
  {
    if (mat->data[i] < min)
    {
      min = mat->data[i];
      min_column = i - row * mat->width;
    }
  }
  return min_column;
}

// REQUIES: mat points to a valid Matrix
//          0 <= row && row < Matrix_height(mat)
//          0 <= column_start && column_end <= Matrix_width(mat)
//          column_start < column_end
// EFFECTS: Returns the minimal value in a particular region. The region
//          is defined as elements in the given row and between
//          column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  int pos_start = row * mat->width + column_start;
  int pos_end = row * mat->width + column_end;
  int min = mat->data[0 + pos_start];
  for (int i = pos_start; i < pos_end; ++i)
  {
    if (mat->data[0 + i] < min)
    {
      min = mat->data[0 + i];
    }
  }
  return min;
}
