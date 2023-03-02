#ifndef _CELL_H
#define _CELL_H

// Possible d'ajouter '#include "src.h"' au lieu de recopier tous les fonctions de src.h dans cell.h

typedef struct cell {
  char* data;
  struct cell* next;
} Cell;

typedef Cell* List;

List* initList();
Cell* buildCell(char* ch);
void insertFirst(List *L, Cell *C);
char* ctos(Cell* c);
char* ltos(List* L);
Cell* listGet(List *L, int i); 
Cell* searchList(List* L, char* str);
List* stol(char* s); 
void ltof(List* L, char* path);
List* ftol(char* path);

List* listdir(char* root_dir);//renvoie
//une liste contenant le noms des fichiers et repertoires qui s’y trouvent

int file_exists(char *file);
void cp(char *to, char *from);
char* hashToPath(char* hash);
void blobFile(char* file);

#endif