#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include "src.h"
#include "bash.h"

int main(void) {
  printf("Files dans l'ensemble du projet:\n%s\n",ltos(listdir("/users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main")));

  List* master = listdir("/users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main/src");
  WorkTree* wt = initWorkTree();
  while(*master) {
    appendWorkTree(wt,(*master)->data,sha256file((*master)->data),getChmod((*master)->data));
    *master = (*master)->next;
  }

  //blobFile("src.c");
  
  //printf("blobwt test on wt: %s\n",blobWorkTree(wt));
  //printf("savewt test on wt: %s\n",saveWorkTree(wt,"/users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main/src"));
  
  printf("test isFile sur src.c %d\n",isFile("/users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main/src/src.c"));

  system("rm -f /users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main/test/*");

  //restoreWorkTree(wt,"/users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main/test");
  
  cp("/users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main/src/file_test.txt","/users/Etu1/21110221/Documents/C/DATASTRUCT/GIT-version-control-main/src/src.txt");

  printf("all fucking ok\n");
  myGitCommit("test","test");

  return 0;
}