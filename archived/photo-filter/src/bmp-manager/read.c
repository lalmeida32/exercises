#include <errno.h>
#include <stdio.h>

#include "include/api.h"
#include "include/internal.h"

void bmp_manager__read_from_file(BMP_MANAGER__BMP_FILE_STRUCTURE *bmp_file_structure, FILE *fp)
{
  printf("%c%c\n", bmp_file_structure->header.signature >> 8, bmp_file_structure->header.signature & 255);
  fread(&bmp_file_structure->header.signature, sizeof(uint16_t), 1, fp);
  printf("%c%c\n", bmp_file_structure->header.signature >> 8, bmp_file_structure->header.signature & 255);
}