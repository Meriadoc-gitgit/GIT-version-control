#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "src.h"
#include "bash.h"

int main(void) {
  
  /* Instantiation */
  kvp* k1 = createKeyVal("Duong","hehehe");
  
  /* Affichage */
  printf("k1: %s\n", kvts(k1));
  printf("stkv test on k1: %s\n",kvts(stkv(kvts(k1))));

  /* Desallocation */
  freeKeyVal(k1);


  /* COMMIT test */
  Commit* c = initCommit();
  commitSet(c,"Duogn","hehehe");
  commitSet(c,"Duong","hehehe");

  printf("hash of duong: %lu\n",hash("Duong"));
  printf("hash of duogn: %lu\n",hash("Duogn"));

  for (int i=0;i<MAX_INPUT;i++) {
    if (c->T[i]) 
      printf("test commit %d: %s\n",i,kvts(c->T[i]));
  }

  Commit* c1 = createCommit("aieufbqebgfquoebgo");
  for(int i=hash("tree");i<MAX_INPUT;i++) {
    if (c1->T[i]) 
      printf("test commit %d: %s\n",i,kvts(c1->T[i]));
  }
  commitSet(c1,"lim","thai hong");
  commitSet(c1,"vu","hoang thuy duong");
  commitSet(c1,"diallo","lima");
  commitSet(c1,"truong","gia bao");

  char* val = commitGet(c,"lim");
  printf("val: %s\n",val);

  printf("\nDescription of c: \n%s\n",cts(c));
  printf("Description of c1: \n%s\n",cts(c1));

  char* cts_c1 = cts(c1);
  ctf(c,cts_c1);
  printf("\ntest ctf on c: \n%s\n",cts(c));
  for (int i=0;i<MAX_INPUT;i++) {
    if (c->T[i]) 
      printf("test commit %d: %s\n",i,kvts(c->T[i]));
  }
  return 0;
}