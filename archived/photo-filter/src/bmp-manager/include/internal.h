#ifndef _BMP_MANAGER__INTERNAL_H_
#define _BMP_MANAGER__INTERNAL_H_

#include <stdint.h>

struct _BMP_MANAGER__BMP_FILE_HEADER
{
  uint16_t signature;
  uint32_t file_size;
  uint32_t reserved;
  uint32_t data_offset;
};

struct _BMP_MANAGER__BMP_FILE_INFO_HEADER
{
  uint32_t size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bits_per_pixel;
  uint32_t compression;
  uint32_t image_size;
  uint32_t x_pixels_per_meter;
  uint32_t y_pixels_per_meter;
  uint32_t colors_used;
  uint32_t important_colors;
};

struct _BMP_MANAGER__BMP_FILE_COLOR
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t reserved;
};

struct _BMP_MANAGER__BMP_FILE_STRUCTURE
{
  struct _BMP_MANAGER__BMP_FILE_HEADER header;
  struct _BMP_MANAGER__BMP_FILE_INFO_HEADER info_header;
  struct _BMP_MANAGER__BMP_FILE_COLOR *color_table;
  uint8_t *pixel_data;
};

#endif // _BMP_MANAGER__INTERNAL_H_