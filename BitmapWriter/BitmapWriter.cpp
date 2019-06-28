// CLASS INCLUDES
#include "BitmapWriter.h"

#include <stdio.h>

BitmapWriter::BitmapWriter() {}

BitmapWriter::~BitmapWriter() {}

void BitmapWriter::GenerateBitmapImage(unsigned char* image, int height,
                                       int width, const char* image_file_name) {
  unsigned char padding[3] = {0, 0, 0};
  int padding_size = (4 - (width * bytes_per_pixel) % 4) % 4;

  unsigned char* file_header =
      CreateBitmapFileHeader(height, width, padding_size);
  unsigned char* info_header = CreateBitmapInfoHeader(height, width);

  FILE* image_file;
  fopen_s(&image_file, image_file_name, "wb");

  if (image_file == nullptr) return;

  fwrite(file_header, 1, file_header_size, image_file);
  fwrite(info_header, 1, info_header_size, image_file);

  int i;
  for (i = 0; i < height; i++) {
    fwrite(image + (i * width * bytes_per_pixel), bytes_per_pixel, width,
           image_file);
    fwrite(padding, 1, padding_size, image_file);
  }

  fclose(image_file);
}

unsigned char* BitmapWriter::CreateBitmapFileHeader(int height, int width,
                                                    int padding_size) {
  int file_size = file_header_size + info_header_size +
                  (bytes_per_pixel * width + padding_size) * height;

  static unsigned char file_header[] = {
      0, 0,        /// signature
      0, 0, 0, 0,  /// image file size in bytes
      0, 0, 0, 0,  /// reserved
      0, 0, 0, 0,  /// start of pixel array
  };

  file_header[0] = (unsigned char)('B');
  file_header[1] = (unsigned char)('M');
  file_header[2] = (unsigned char)(file_size);
  file_header[3] = (unsigned char)(file_size >> 8);
  file_header[4] = (unsigned char)(file_size >> 16);
  file_header[5] = (unsigned char)(file_size >> 24);
  file_header[10] = (unsigned char)(file_header_size + info_header_size);

  return file_header;
}

unsigned char* BitmapWriter::CreateBitmapInfoHeader(int height, int width) {
  static unsigned char info_header[] = {
      0, 0, 0, 0,  /// header size
      0, 0, 0, 0,  /// image width
      0, 0, 0, 0,  /// image height
      0, 0,        /// number of color planes
      0, 0,        /// bits per pixel
      0, 0, 0, 0,  /// compression
      0, 0, 0, 0,  /// image size
      0, 0, 0, 0,  /// horizontal resolution
      0, 0, 0, 0,  /// vertical resolution
      0, 0, 0, 0,  /// colors in color table
      0, 0, 0, 0,  /// important color count
  };

  info_header[0] = (unsigned char)(info_header_size);
  info_header[4] = (unsigned char)(width);
  info_header[5] = (unsigned char)(width >> 8);
  info_header[6] = (unsigned char)(width >> 16);
  info_header[7] = (unsigned char)(width >> 24);
  info_header[8] = (unsigned char)(height);
  info_header[9] = (unsigned char)(height >> 8);
  info_header[10] = (unsigned char)(height >> 16);
  info_header[11] = (unsigned char)(height >> 24);
  info_header[12] = (unsigned char)(1);
  info_header[14] = (unsigned char)(bytes_per_pixel * 8);

  return info_header;
}