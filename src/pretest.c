#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bash.h"
#include "src.h"

int main(void) {
  int chr = 100;
  unsigned char i = chr;
  printf("%lu\n",hash(&i));
  return 0;
}