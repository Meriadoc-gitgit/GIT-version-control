#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"
#include "src.h"

int main(void) {
  List* L = initList();
  Cell* C = buildCell("test");

  insertFirst(L,C);
  insertFirst(L,buildCell("test2"));


  

  char* tmp = ltos(L);
  printf("tmp:%s\n",tmp);
  

  //int hash = hashFile("src.txt","dst.txt");
  //printf("%d\n",hash);
  return 0;
}