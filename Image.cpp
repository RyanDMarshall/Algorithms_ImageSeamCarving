#include <cassert>
#include <string>
#include <iostream>
#include "Image.h"
#include "Matrix.h"

using namespace std;

// REQUIRES: img points to an Image
//           0 < width <= MAX_MATRIX_WIDTH
//           0 < height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
void Image_init(Image* img, int width, int height) {


  img->width = width;
  img->height = height;

  Matrix_init(&(img->red_channel), width, height);
  Matrix_init(&(img->blue_channel), width, height);
  Matrix_init(&(img->green_channel), width, height);


  return;
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.

// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
    
  string file_type;
  int width;
  int height;
  int max_RGB;
  
  is >> file_type >> width >> height >> max_RGB;

  if (width > MAX_MATRIX_WIDTH || height > MAX_MATRIX_HEIGHT)
  {
    cout << "Input image exceeds maximum size" << endl;
    exit(EXIT_FAILURE);
  }

  int red, green, blue;
  int i = 0;

  while (i < (height * width)) {

    is >> red >> green >> blue;

    if (red > MAX_INTENSITY || green > MAX_INTENSITY || blue > MAX_INTENSITY)
    {
      cout << "Pixel exceeds max intensity" << endl;
      exit(EXIT_FAILURE);
    }

    img->red_channel.data[i] = red;
    img->green_channel.data[i] = green;
    img->blue_channel.data[i] = blue;

    ++i;
  }



  Image_init(img, width, height);

  return;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {

  os << "P3" << endl << img->width << ' ' << img->height
      << endl << "255" << endl;

  for (int i = 0; i < img->width * img->height; i++) {
      os << img->red_channel.data[i] << " " << img->green_channel.data[i] << " " 
      << img->blue_channel.data[i] << " ";
      if((i + 1) % img->width == 0)
      {
        os << endl;
      }
  }
  return;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {

  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {

  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {

  Pixel pix;
  int r = *Matrix_at(&(img->red_channel), row, column);
  int g = *Matrix_at(&(img->green_channel), row, column);
  int b = *Matrix_at(&(img->blue_channel), row, column);
  pix.r = r;
  pix.g = g;
  pix.b = b;
  return pix;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {

  *Matrix_at(&(img->red_channel), row, column) = color.r;
  *Matrix_at(&(img->green_channel), row, column) = color.g;
  *Matrix_at(&(img->blue_channel), row, column) = color.b;
  
  return;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {

  for (int i = 0; i < (img->red_channel.width * img->red_channel.height); ++i)
  {
    img->red_channel.data[i] = color.r;
    img->green_channel.data[i] = color.g;
    img->blue_channel.data[i] = color.b;
  }

  return;
}
