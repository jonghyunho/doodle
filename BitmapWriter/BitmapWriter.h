#pragma once

class BitmapWriter {
 public:
  BitmapWriter();
  virtual ~BitmapWriter();

  void GenerateBitmapImage(unsigned char* image, int height, int width,
                           const char* image_file_name);

 protected:
  unsigned char* CreateBitmapFileHeader(int height, int width,
                                        int padding_size);
  unsigned char* CreateBitmapInfoHeader(int height, int width);

 private:
  const int bytes_per_pixel = 3;  /// red, green, blue
  const int file_header_size = 14;
  const int info_header_size = 40;
};
