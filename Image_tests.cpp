#include "Matrix.h"
#include "test_helpers.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

void test_image_init();
void test_image_height_width();
void test_image_print();
void test_image_fill_get_set_pixel();

int main() {
  
  test_image_init();
  test_image_print();
  test_image_height_width();
  test_image_fill_get_set_pixel();

  cout << "Image_tests PASS" << endl;
}

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
void test_image_init() {

  Image img1, img2;
  int width1, height1, width2, height2, width3, height3;

  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 200;
  height3 = 300;

  //Initialize images with edge case sizes
  Image_init(&img1, width1, height1);
  assert(Image_width(&img1) == 1 && Image_height(&img1) == 1);
  Image_init(&img1, width2, height2);
  assert(Image_width(&img1) == MAX_MATRIX_WIDTH && Image_height(&img1) == MAX_MATRIX_HEIGHT);

  //Reinitialize images with non-square size
  Image_init(&img1, width3, height3);
  assert(Image_width(&img1) == 200 && Image_height(&img1) == 300);

  // Testing Image_init using istream
  string input = "P3 2 1\t255 1 3 3\n3\n3 1 \n";
  stringstream ss_input(input);
  Image_init(&img2, ss_input);
  string output_correct = "P3\n2 1\n255\n1 3 3 3 3 1 \n";
  stringstream ss_output;
  Image_print(&img2, ss_output);
  string actual = ss_output.str();
  assert(actual == output_correct);

  cout << "Image_init tests PASS" << endl;
  return;
}

void test_image_print() {

  Image img, img2;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  stringstream s;
  Image_print(&img, s);

  // Correct output
  stringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  assert(s.str() == correct.str());

  // Test for large edge case
  Image_init(&img, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
  Image_fill(&img, white);
  ostringstream expected;
  expected << "P3\n" << (MAX_MATRIX_WIDTH) << ' ' << (MAX_MATRIX_HEIGHT) << '\n' << "255\n";
  for (int i = 0; i < (MAX_MATRIX_HEIGHT); ++i) {
    for (int j = 0; j < (MAX_MATRIX_WIDTH) * 3; ++j) {
      expected << "255 ";
    }
    expected << '\n';
  }
  ostringstream actual;
  Image_print(&img, actual);
  assert(expected.str() == actual.str());

  // Test when row =/= column
  Image_init(&img2, 2, 1);
  Image_set_pixel(&img2, 0, 0, red);
  Image_set_pixel(&img2, 0, 1, green);
  ostringstream expected2;
  expected2 << "P3\n"
            << "2 1\n255\n"
            << "255 0 0 0 255 0 \n";
  ostringstream actual2;
  Image_print(&img2, actual2);
  assert(expected2.str() == actual2.str());

  cout << "Image_print tests PASS" << endl;
  return;
}

void test_image_height_width() {
  Image img1;
  int width1, height1, width2, height2, width3, height3;

  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;
  width3 = 2;
  height3 = 1;

  // Test size for small edge case
  Image_init(&img1, width1, height1);
  assert(Image_width(&img1) == 1);
  assert(Image_height(&img1) == 1);

  // Test size for large edge case
  Image_init(&img1, width2, height2);
  assert(Image_width(&img1) == MAX_MATRIX_WIDTH);
  assert(Image_height(&img1) == MAX_MATRIX_HEIGHT);

  // Test size for irregular case
  Image_init(&img1, width3, height3);
  assert(Image_width(&img1) == 2);
  assert(Image_height(&img1) == 1);


  cout << "Image size tests PASS" << endl;
  return;
}

void test_image_fill_get_set_pixel() {

  const Pixel red = {255, 0, 0};
  const Pixel blue = {0, 0, 255};

  Image img1, img2;
  int width1, height1, width2, height2;

  width1 = 1;
  height1 = 1;
  width2 = MAX_MATRIX_WIDTH;
  height2 = MAX_MATRIX_HEIGHT;

  Image_init(&img1, width1, height1);
  Image_init(&img2, width2, height2);

  // Test 1x1 with re-initialization
  Image_set_pixel(&img1, 0, 0, red);
  assert(Pixel_equal(Image_get_pixel(&img1, 0, 0), red));
  Image_fill(&img1, blue);
  assert(Pixel_equal(Image_get_pixel(&img1, 0, 0), blue));

  // Test max size matrix with cool pattern
  Image_fill(&img2, red);
  for (int i = 0; i < Image_width(&img2); ++i) {
    for (int j = 0; j < Image_height(&img2); ++j) {
      if ((i == j) || (i == Image_width(&img2) - j - 1)) {
        Image_set_pixel(&img2, i, j, blue);
      }
    }
  }

  for (int i = 0; i < Image_width(&img2); ++i) {
    for (int j = 0; j < Image_height(&img2); ++j) {
      if ((i == j) || (i == Image_width(&img2) - j - 1)) {
        assert(Pixel_equal(Image_get_pixel(&img2, i, j), blue));
      } else {
        assert(Pixel_equal(Image_get_pixel(&img2, i, j), red));
      }
    }
  }

  cout << "Image fill tests PASS" << endl;

  return;
}
