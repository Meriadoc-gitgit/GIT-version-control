#ifndef _SRC
#define _SRC

typedef struct cell { 
  char* data;
  struct cell* next;
} Cell;
typedef Cell* List;

typedef struct {
  char* name;
  char* hash;
  int mode;
} WorkFile;
typedef struct {
  WorkFile* tab;
  int size;
  int n;
} WorkTree;

/* Part 1 - Manipulation de Cell et List */
List* initList();
Cell* buildCell(char* ch);
void insertFirst(List* L,Cell* C);
char* ctos(Cell* C);
char* ltos(List* L);
Cell* listGet(List* L,int i);
Cell* searchList(List* L,char* str);
List* stol(char* s);
void ltof(List* L,char* path);
List* ftol(char* path);



/* Part 2 */
/* MANIPULATION DE WORKFILE */
WorkFile* createWorkFile(char* name);
char* wfts(WorkFile* wf);
WorkFile* stwf(char* ch);
void libererWorkFile(WorkFile* wf);

/* MANIPULATION DE WORKTREE */
WorkTree* initWorkTree();
int inWorkTree(WorkTree* wt,char* name);
int appendWorkTree(WorkTree* wt,char* name,char* hash,int mode);
char* wtts(WorkTree* wt);
WorkTree* stwt(char* ch);
int wttf(WorkTree* wt,char* file);
WorkTree* ftwt(char* file);
void libererWorkTree(WorkTree* wt);

#endif