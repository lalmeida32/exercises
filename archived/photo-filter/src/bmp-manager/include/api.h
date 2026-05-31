#ifndef _BMP_MANAGER__API_H_
#define _BMP_MANAGER__API_H_

#include <stdio.h>

#define BMP_MANAGER__ERROR_CODE__SUCCESS 0

typedef struct _BMP_MANAGER__BMP_FILE_STRUCTURE BMP_MANAGER__BMP_FILE_STRUCTURE;

BMP_MANAGER__BMP_FILE_STRUCTURE *bmp_manager__create_bmp_file_structure();
void bmp_manager__free_bmp_file_structure(BMP_MANAGER__BMP_FILE_STRUCTURE **bmp_file_structure_p);

void bmp_manager__read_from_file(BMP_MANAGER__BMP_FILE_STRUCTURE *bmp_file_structure, FILE *fp);

#endif // _BMP_MANAGER__API_H_