#ifndef _SRC
#define _SRC

#include "cell.h"

int hashFile(char* src, char *dst);
char* sha256file(char* file);

List* listdir(char* root_dir);
int file_exists(char* file);
void cp(char* to, char* from);

#endif