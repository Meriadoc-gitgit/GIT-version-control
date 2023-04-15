
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "src.h"
#include "bash.h"

int main(void) {

  //Commit* c1 = createCommit(sha256file("src.c"));

  initRefs();
  
  initBranch();
  printf("check if branch master exists: %d\n",branchExists("master"));
  createBranch("Feature1");

  //printf("blobCommit de c1: %s\n", blobCommit(c1));
  //printf("hashToPath de c1: %s\n", hashToFile(blobCommit(c1)));

  //blobCommit(createCommit(sha256file("bash.c")));
  //createUpdateRef("Feature0",blobCommit(c1));
  List* master = listdir("/Users/vuhoangthuyduong/Documents/GitHub/GIT-version-control/src");
  WorkTree* wt = initWorkTree();
  WorkTree* wt1 = initWorkTree();
  while(*master) {
    appendWorkTree(wt,(*master)->data,sha256file((*master)->data),getChmod((*master)->data));
    appendWorkTree(wt1,(*master)->data,sha256file((*master)->data),getChmod((*master)->data));
    *master = (*master)->next;
  }
  List* conflicts = initList();
  WorkTree* wt2 = mergeWorkTree(wt,wt1,&conflicts);
  printf("conflicts mergeWT: %s\n",ltos(conflicts));
  printBranch("Feature0");

  List* L = branchList("Feature0");
  printf("%s\n",ltos(L));

  List* L1 = getAllCommits();
  printf("%s\n",ltos(L1));

  List* L2 = ftol("file_text.txt");
  printf("%s\n",ltos(L2));

  myGitAdd("src.c");
  myGitCommit("Feature0","test");

  return 0;
}