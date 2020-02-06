#include "Image.h"
#include "test_helpers.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;


// This is the public Image test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Image module.
// It will only really tell you if your code compiles and you remembered to
// write the functions. It is not to be trusted. It tells the truth, but not
// the whole truth. It might put you in a blender. You get the point.
// You must write your own comprehensive unit tests in Image_tests.cpp!


int main() {
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Image img;
  Image_init(&img, 3, 4);

  assert(Image_width(&img) == 3);
  assert(Image_height(&img) == 4);
  Image_fill(&img, red);
  assert(Pixel_equal(Image_get_pixel(&img, 2, 2), red));

  Image_set_pixel(&img, 0, 0, green);
  assert(Pixel_equal(Image_get_pixel(&img, 0, 0), green));

  // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  stringstream ss_input(input);
  Image_init(&img, ss_input);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  stringstream ss_output;
  Image_print(&img, ss_output);
  string actual = ss_output.str();
  cout << actual << endl;
  assert(actual == output_correct);

  Matrix mat;
  Matrix_init(&mat, 6, 1);
  for(int c = 0; c < 6; ++c){
    *Matrix_at(&mat, 0, c) = c;
  }

  cout << "Image_public_test PASS" << endl;
}
