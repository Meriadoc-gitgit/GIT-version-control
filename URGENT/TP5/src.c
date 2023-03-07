#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

#include "src.h"

int hashFile(char* src, char *dst) {
  char res[200];
  sprintf(res,"sha256sum %s > %s",src,dst);
  return system(res);
}


char* sha256file(char* file) {
  char* src = strdup(file);
  int filedes = -1, count = 0;
  
  errno = 0;

  filedes = mkstemp(file);
  unlink(file);
  
  if (filedes<1) {
    printf("Echec de creation de file temporaire [%s]\n",strerror(errno));
    return NULL;
  } 
  else printf("File temporaire [%s] cree\n",file);

  errno = 0;

  hashFile(src, file);
  /* Read the data */
  char buffer[256];
  FILE* f = fopen(file,"r");
  if (!f) {
    printf("Erreur lors de l'ouverture\n");
    return NULL;
  }
  char *res = fgets(buffer, 256, f);
  fclose(f);

  return res;
}
List* listdir(char* root_dir) {
  List* L = initList();
  DIR* dp = opendir(root_dir);
  struct dirent* ep;
  if (dp) {
    while((ep = readdir(dp))) 
      insertFirst(L,buildCell(ep->d_name));
  }
  return L;
}
int file_exists(char* file) {
  char cwd[PATH_MAX];
  if (!getcwd(cwd,sizeof(cwd))) {
    perror("getcwd() error\n");
    return 1;
  }
  List* L = listdir(cwd);
  return searchList(L,file)!=NULL;
}
void cp(char* to, char* from) {
  if (!file_exists(from)) {
    printf("Fichier demande n'existe pas\n");
    return;
  }
  char res[200];
  sprintf(res,"%s > %s",from,to);
  system(res);
  return;
}
char* hashToPath(char* hash) {
  char res[(int)strlen(hash)+1];
  for (int i=0;i<2;i++) 
    res[i] = hash[i];
  res[2] = '/';
  for (int i=2;i<(int)strlen(hash);i++)
    res[i+1] = hash[i];

  char* str = res,*r=strdup(res);
  //strcpy(r,str);
  return r;
}
/* Check later */
void blobFile(char* file) {
  system("mkdir INSTANT");
  char res[200];
  sprintf(res,"%s > file.tmp",file);
  system(res);
  return;
}