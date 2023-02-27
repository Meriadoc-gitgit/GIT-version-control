#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"
#include "src.h"

int main(void) {
  List* L = initList();
  Cell* C = buildCell("test");

  insertFirst(L,C);
  //insertFirst(L,C);

  //printf("tmp0:%s\n",ltos(L));

  Cell* c1 = buildCell("hihi");
  printf("%s\n",ctos(c1));

  ltof(L,"dst.txt");

  List* L2 = stol("chain1|chain2|chain3");

  //printf("%s\n",ltos(L2));
  List* L3 = ftol("src.txt");
  char* tmp = ltos(L3);
  printf("\ntmp:%s\n",tmp);

  int hash = hashFile("src.txt","dst.txt");
  printf("%d\n",hash);



  return 0;
}