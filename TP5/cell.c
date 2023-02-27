#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"

List* initList() {
  List* rst = (List*)malloc(sizeof(List));
  return rst;
}
Cell* buildCell(char* ch) {
  Cell* rst = (Cell*)malloc(sizeof(Cell));
  rst->data = strdup(ch);
  rst->next = NULL;
  return rst;
}
void insertFirst(List* L,Cell* C) {
  C->next = *L;
  *L = C;
  return;
}
char* ctos(Cell* C) {
  return C->data;
}
char* ltos(List* L) {
  if ((*L)==NULL) {
    printf("Liste *L est NULL\n");
    return NULL;
  }
  char delim = '|';
  int total = 0;

  Cell* C = *L;

  while((*L)!=NULL) {
    total += (int)strlen(ctos(*L));
    total++;
    (*L) = (*L)->next;
  }

  printf("total char for rst:%d\n",total);

  char rst[total], *tmp;
  int temp = 0;

  while(C) {
    //if ((int)strlen(rst)==total) break;
    tmp = ctos(C);
    for (int i=0;i<(int)strlen(tmp);i++) {
      if (i+temp+1==total) break;
      rst[i+temp] = tmp[i];
    }
    
    temp += (int)strlen(tmp)+1;
    rst[temp-1] = delim;
  
    C = C->next;
  }
  rst[total] = '\0';
  char* res = rst,*r;
  strcpy(r,res);
  return r;
}
Cell* listGet(List* L,int i) {
  Cell* tmp = *L;
  while(i>1) {
    tmp = tmp->next;
    i--;
  }
  if (i==1) return tmp;
  else return NULL;
}
Cell* searchList(List* L,char* str) {
  Cell* tmp = *L;
  while(tmp) {
    if (strcmp(tmp->data,str)==0) return tmp;
    tmp = tmp->next;
  }
  return NULL;
}
List* stol(char* s) {
  char str[(int)strlen(s)];
  for(int i=0;i<(int)strlen(s);i++)
    str[i] = s[i];
  int init_size = (int)strlen(str);
  const char* delim = "|";

  char* ptr = strtok(str,delim);
  List* L = initList();

  while (ptr!=NULL) {
    insertFirst(L,buildCell(ptr));
    ptr = strtok(NULL,delim);
  }
  printf("stol:ok\n");
  return L;
}
void ltof(List* L,char* path) {
  FILE *f = fopen(path,"w");
  if (!f) {
    printf("Erreur lors de l'ouverture\n");
    return;
  }
  
  while((*L)) {
    fprintf(f,"%s\n",(*L)->data);
    *L = (*L)->next;
  }
  fclose(f);
  return;
}
List* ftol(char* path) {
  FILE *f = fopen(path,"r");
  if (!f) {
    printf("Erreur lors de l'ouverture\n");
    return NULL;
  }

  List* L = initList();

  char buffer[256];
  char *res = fgets(buffer, 256, f);
  char data[26];
  
  while(res!=NULL) {
    sscanf(buffer,"%s",data);
    res = fgets(buffer, 256, f);
    insertFirst(L,buildCell(data));
  }
  fclose(f);
  printf("ftol:ok\n");
  return L;
}