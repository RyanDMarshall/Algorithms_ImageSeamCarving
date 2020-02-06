#include <cassert>
#include "processing.h"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched
  
  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched
  
  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {

  int energy_width = Image_width(img);
  int energy_height = Image_height(img);

  int energy_at_position = 0;

  Matrix_init(energy, energy_width, energy_height);
  Matrix_fill(energy, 0);

  for (int i = 1; i < energy_height - 1; ++i) { //row
    for (int j = 1; j < energy_width - 1; ++j) {
      int current = i * energy_width + j;
      energy_at_position = squared_difference(Image_get_pixel(img,i-1,j),Image_get_pixel(img,i+1,j)) +
                           squared_difference(Image_get_pixel(img,i,j-1),Image_get_pixel(img,i,j+1));

      energy->data[current] = energy_at_position;
    }
  }

  int non_border_max = Matrix_max(energy);
  Matrix_fill_border(energy, non_border_max);

  return;
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));
  // fill the 1 row (index 0)
  for (int i = 0; i < Matrix_width(cost); ++i) {
    cost->data[i] = energy->data[i];
  }
  for (int m = 1; m < Matrix_height(cost); ++m) { //row
    for (int n = 0; n < Matrix_width(cost); ++n) { //column
      int position = m * Matrix_width(cost) + n;
      if (n == 0) {
        cost->data[position] = energy->data[position] + Matrix_min_value_in_row(cost, m - 1, 0, 2);
      }
      else if (n == cost->width - 1) {
        cost->data[position] = energy->data[position] + Matrix_min_value_in_row(cost, m - 1, n - 1, n + 1);
      }
      else {
        cost->data[position] = energy->data[position] + Matrix_min_value_in_row(cost, m - 1, n - 1, n + 2);
      }
    }
  }
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, starting with the lowest
//           numbered row (top of image) and progressing to the highest
//           (bottom of image). While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  int search_col = 0;
  for (int i = Matrix_height(cost) - 1; i >= 0; --i) {
    if (i == Matrix_height(cost) - 1) {
      search_col = Matrix_column_of_min_value_in_row(cost, i, 0, Matrix_width(cost) - 1);
      seam[i] = search_col;
    }
    else if (search_col == 0) {
      search_col = Matrix_column_of_min_value_in_row(cost, i, 0, 2);
      seam[i] = search_col;
    }
    else if (search_col == Matrix_width(cost) - 1) {
      search_col = Matrix_column_of_min_value_in_row(cost, i, search_col - 1, search_col + 1);
      seam[i] = search_col;
    }
    else {
      search_col = Matrix_column_of_min_value_in_row(cost, i, search_col - 1, search_col + 2);
      seam[i] = search_col;
    }
  }
}


// REQUIRES: img points to a valid Image
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
void remove_vertical_seam(Image *img, const int seam[]) {

  int img_height = Image_height(img);
  int img_width = Image_width(img);
  int img_seamless_width = img_width - 1;

  Image img_seamless;
  Image_init(&img_seamless, img_seamless_width, img_height);

  for (int i = 0; i < img_height; ++i) {
    for (int j = 0; j < img_width; ++j) {
      if (j < seam[i]) {
        Image_set_pixel(&img_seamless, i, j, Image_get_pixel(img,i,j));
      }
      else if (j > seam[i]) {
        Image_set_pixel(&img_seamless, i, j - 1, Image_get_pixel(img,i,j));
      }
    }
  }

  Image_init(img, img_seamless_width, img_height);
  *img = img_seamless;

  return;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
void seam_carve_width(Image *img, int newWidth) {
  Matrix energy, cost;
  int seam[MAX_MATRIX_HEIGHT];
  int width = Image_width(img);
  for (int i = 0; i < width - newWidth; ++i) {
    compute_energy_matrix(img, &energy);
    compute_vertical_cost_matrix(&energy, &cost);
    find_minimal_vertical_seam(&cost, seam);
    remove_vertical_seam(img, seam);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth <= Image_width(img)
//           0 < newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}

