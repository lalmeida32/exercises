#include <errno.h>
#include <stdlib.h>

#include "include/api.h"
#include "include/internal.h"

BMP_MANAGER__BMP_FILE_STRUCTURE *bmp_manager__create_bmp_file_structure()
{
  BMP_MANAGER__BMP_FILE_STRUCTURE *bmp_file_structure =
      (BMP_MANAGER__BMP_FILE_STRUCTURE *)malloc(sizeof(BMP_MANAGER__BMP_FILE_STRUCTURE));

  if (bmp_file_structure == NULL)
    return NULL;

  bmp_file_structure->color_table = NULL;
  bmp_file_structure->pixel_data = NULL;

  errno = BMP_MANAGER__ERROR_CODE__SUCCESS;
  return bmp_file_structure;
}

void bmp_manager__free_bmp_file_structure(BMP_MANAGER__BMP_FILE_STRUCTURE **bmp_file_structure_p)
{
  if (bmp_file_structure_p == NULL)
  {
    errno = EFAULT;
    return;
  }

  BMP_MANAGER__BMP_FILE_STRUCTURE *bmp_file_structure = *bmp_file_structure_p;

  free(bmp_file_structure->color_table);
  free(bmp_file_structure->pixel_data);
  free(bmp_file_structure);
  *bmp_file_structure_p = NULL;

  errno = BMP_MANAGER__ERROR_CODE__SUCCESS;
}
