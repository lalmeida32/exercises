#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp-manager/include/api.h"

int main(void)
{
  BMP_MANAGER__BMP_FILE_STRUCTURE *bmp_file_structure = bmp_manager__create_bmp_file_structure();
  if (errno != BMP_MANAGER__ERROR_CODE__SUCCESS)
  {
    perror("Error creating BMP file structure");
    return EXIT_FAILURE;
  }

  bmp_manager__free_bmp_file_structure(&bmp_file_structure);
  if (errno != BMP_MANAGER__ERROR_CODE__SUCCESS)
  {
    perror("Error freeing BMP file structure");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}