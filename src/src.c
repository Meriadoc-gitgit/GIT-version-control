#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#include "bash.h"
#include "src.h"

/* Part 1 - Manipulation de Cell et List */
int sizeList(List* L) {
  //Usage: calculer la taille d'une liste
  int cpt = 0;
  while (*L) {
    cpt++; //incrementer cpt a chaque tour de boucle
    *L = (*L)->next;
  }
  return cpt;
}
List* initList() { //OK
  //Usage: Initialiser une liste vide
  List* rst = (List*)malloc(sizeof(List));
  *rst = NULL;
  return rst;
}
Cell* buildCell(char* ch) {//OK
  //Usage: allouer + retourner une cellule de la liste
  Cell* rst = (Cell*)malloc(sizeof(Cell));
  rst->data = strdup(ch); //dupliquer ch dans rst->data
  rst->next = NULL;
  return rst;
}
void insertFirst(List* L,Cell* C) {//OK
  //Usage: ajouter un élément en tête d'une liste
  C->next = *L; 
  *L = C;
  return;
}
char* ctos(Cell* C) {//OK
  //Usage: retourne le chaine de caractères qu'elle représente
  if (C==NULL) return "";
  return C->data;
}
char* ltos(List* L) {//OK
  //Usage: transforme une liste en une chaine de caractere de format: chain1|chaine2|... (utilisant fonction ctos)
  if (*L==NULL) 
    return "";  
  char* ch = malloc(INT_MAX*sizeof(char)); //allouer la chaine utilisee pour concatener les elements de List avec la taille maximale possible afin d'eviter les fuites de memoire et faute de segmentation
  while(*L) {
    strcat(ch,(*L)->data); //Concatener les elements de List dans ch
    *L = (*L)->next;
    if (*L) strcat(ch,"|"); //Si on arrive au dernier element, on n'ajoute plus '|' dans ch
  }
  return ch;
}
Cell* listGet(List* L,int i) {//OK
  //Usage: renvoie le i-ième élément d'une liste
  if (*L==NULL) return NULL;
  Cell* tmp = *L;//au cas ou L est une liste non vide, on initialise un Cell* tmp afin de faciliser le retour de la fonction 
  while(i>0) {//boucle jusqu'a ce que i=0
    tmp = tmp->next; 
    i--; //diminuer i a chaque tour de boucle
  }
  if (i==0) return tmp; //retourne le i-ieme element
  else return NULL;
}
Cell* searchList(List* L,char* str) {//OK
  //Usage: recherche un élément dans une liste à partir de son contenu
  Cell* tmp = *L;
  while(tmp && strcmp(tmp->data,str)!=0) //si l'element tmp n'est pas vide et sa chaine representant est different de la chaine prise en parametre
    tmp = tmp->next;
  return tmp; //si on a trouve l'element ayant la chaine representant similaire a celle en entree + cet element doit etre non vide
  //Au cas ou la chaine demandee n'est pas trouve dans L, tmp est automatique NULL apres le parcours et la fonction renvoie NULL
}
List* stol(char* s) {//ok
  //Usage: transformer une chaine de caractères représentant une liste en une liste chainée
  char str[(int)strlen(s)*sizeof(char)]; //initialiser ce variable afin de ne pas detruire la chaine prise en entree
  sprintf(str,"%s",s);
  const char* delim = "|"; //caractere delimitant de la chaine 
  char* ptr = strtok(str,delim); //separer la partie avant | de la chaine fournie
  List* L = initList();

  while (ptr!=NULL) {
    insertFirst(L,buildCell(ptr)); //inserer chaque element separe grace a strtok dans L
    ptr = strtok(NULL,delim); //continuer la separation avec la chaine apres la separation de l'element precedent et '|'
  }
  return L;
}
void ltof(List* L,char* path) {//ok
  //Usage: écrire une liste dans un fichier
  if (*L==NULL) { //verifier si L est une liste vide
    printf("WARNING: The given List is empty\n");
    return;
  }
  FILE *f = fopen(path,"w");
  if (!f) { //verifier si le FILE est bien ouvert ou n'est actuellement pas vide
    printf("WARNING: Unable to open %s\n",path);
    return;
  }
  //Au cas ou tous les tests precedents ont bien eu lieu
  Cell *C = *L;
  while(C) {
    fprintf(f,"%s\n",C->data); //ecrire element par element de L dans le fichier path
    C = C->next;
  }
  fclose(f); //fermer le fichier path apres l'ecriture
  return;
}
List* ftol(char* path) {//ok
  //Usage: lire une liste enregistrée dans un fichier
  if (!file_exists(path)) { //verifier l'existence du fichier path dans l'environement 
    printf("WARNING: The given file %s not found\n",path);
    return NULL;
  }
  FILE *f = fopen(path,"r");
  if (!f) { //verifier si le FILE est bien ouvert ou n'est actuellement pas vide
    printf("WARNING: The given file %s is empty\n",path);
    return NULL;
  }
  //Au cas ou tous les tests precedents ont bien eu lieu
  List* L = initList(); //Initialiser la liste L pour l'enregistrement des variables
  char buffer[256]; 
  while(fgets(buffer, 256, f)) { //lecture ligne par ligne du fichier path
    insertFirst(L,buildCell(buffer));//inserer les lignes lus du fichier path dans la liste L
  }
  fclose(f); //fermer le fichier path apres la lecture
  return L;
}



/* Part 2 */
/* MANIPULATION DE WORKFILE */
WorkFile* createWorkFile(char* name) {//ok
  //Usage: créer un WorkFile + l'initialiser
  WorkFile* wf = (WorkFile*)malloc(sizeof(WorkFile));//allouer un WorkFile
  //Initialiser les caracteristiques d'un fichier: name, hash et mode
  wf->name = strdup(name);//dupliquer la chaine name fournie en parametre dans wf->name
  wf->hash = NULL; //initiliser hash à NULL
  wf->mode = 0; //initiliser mode à 0
  return wf;
}
char* wfts(WorkFile* wf) {//ok
  //Usage: convertir un WorkFile en chaine de caractàres contenant les différents champs séparés par des tabulations (caractères '\t')
  if (!wf) { //verifier si le WorkFile est une structure vide
    printf("WARNING: Empty WorkFile\n");
    return NULL;
  }
  char* desc = (char*)malloc(1000*sizeof(char)); //allouer la chaine qui va prochainement contenir les caracteristiques de ce WorkFile
  sprintf(desc,"%s\t%s\t%d",wf->name,wf->hash,wf->mode); //concatener les caracteristiques du WorkFile separees par des tabulation '\t'
  return desc;
}
WorkFile* stwf(char* ch) {//ok
  //Usage: convertir une chaine de caractères représentant un WorkFile en un WorkFile
  char str[(int)strlen(ch)*sizeof(char)]; //allouer ce variable afin de manipuler la chaine prise en entree sans la detruire
  sprintf(str,"%s",ch);
  char name[100], hash[100]; 
  int mode; //initialiser les 3 caracteristiques d'un WorkFile
  sscanf(ch,"%s %s %d",name,hash,&mode); //scanner les caracteristiques d'un WorkFile de la chaine fournie + les enregistrer dans les variables recemment initialises
  WorkFile* wf = createWorkFile(name); //creer un WorkFile
  wf->hash = strdup(hash); //modifier les caracteristiques du WorkFile recemment cree
  wf->mode = mode;
  return wf;
}


WorkTree* initWorkTree() {//ok
  //Usage: allouer un WorkTree de taille fixée (donnée par une constante du programme) + l'initialiser
  WorkTree* wt = (WorkTree*)malloc(sizeof(WorkTree)); //allouer un WorkTree
  wt->size = MAX_INPUT; //initialiser la taille du tableau WorkFile de WorkTree a MAX_INPUT (dont le constant de ce programme)
  wt->n = 0; //initialiser le nombre d'element present dans ce tableau a 0 (car aucun element ainsi insere)
  wt->tab = (WorkFile*)malloc(wt->size*sizeof(WorkFile)); //allouer le tableau WorkFile que contient ce WorkTree
  return wt;
}
int inWorkTree(WorkTree* wt,char* name) {//ok
  //Usage: vérifie la présence d'un fichier ou répertoire dans un WorkTree
  if (!wt) { //Verifier si le WorkTree fourni est vide
    printf("WARNING: Empty WorkTree\n"); return -1;
  }
  for (int i=0;i<wt->n;i++) { //parcourir le tableau de WorkTree
    if (strcmp(wt->tab[i].name,name)==0) //comparer le nom des WorkFile du tableau avec la variable name fournie en entree
      return i; //retourne la position du fichier demande (s'il existe dans ce tableau)
  }
  return -1;
}
int appendWorkTree(WorkTree* wt,char* name,char* hash,int mode) {//ok
  //Usage: ajoute un fichier ou répertoire au WorkTree (s'il n'existe pas déjà)
  if (inWorkTree(wt,name)==-1 && wt->n<wt->size) { //verifier l'existence de fichier name dans le WorkTree fourni en entree + si le tableau de WorkTree a encore de place disponible
    wt->tab[wt->n].name = strdup(name);
    wt->tab[wt->n].mode = mode;
    if (hash) wt->tab[wt->n].hash = strdup(hash); //si la variable hash est fourni en entree, on met a jour celle du WorkFile lors de l'ajout
    else wt->tab[wt->n].hash = "";
    wt->n++; //incremente le nombre d'element present dans le tableau WorkTree de 1
    return 0;
  }
  return -1;
}
char* wtts(WorkTree* wt) {//ok
  //Usage: convertit un WorkTree en une chaine de caractères composée des représentations des WorkFile separées par un saut de ligne (caractère '\n')
  if (wt->n==0) return "WARNING: Empty WorkTree\n"; //si le WorkTree ne contient aucun element
  char *command = (char*)malloc(INT_MAX*sizeof(char)); //allouer ce variable afin de contenir tous les nom de fichier du WorkTree
  char* w = NULL;
  for (int i=0;i<wt->n;i++) {
    w = wfts(&(wt->tab[i]));
    strcat(command,w); //concatener les noms et '\n' de WorkFile du WorkTree dans command 
    strcat(command,"\n");
  }
  return command; //retourner la description des WorkFile du WorkTree
}
WorkTree* stwt(char* ch) {//ok
  //Usage: convertit une chaine de caractères représentant un WorkTree en un WorkTree
  int pos = 0; 
  int n_pos = 0; 
  int sep = '\n';
  char* ptr;
  char* result = malloc(sizeof(char)*10000); //allouer ce variable afin de contenir les caracteristiques du WorkFile au fur a mesure
  WorkTree* wt = initWorkTree(); //initialiser un WorkTree
  while (pos<strlen(ch)) {
    ptr = strchr(ch+pos,sep);
    if (ptr==NULL)
      n_pos = strlen(ch)+1;
    else 
      n_pos = ptr - ch + 1;
    
    memcpy(result, ch+pos, n_pos-pos-1);
    result[n_pos-pos-1] = '\0';
    pos = n_pos;
    WorkFile* wf = stwf(result);
    appendWorkTree(wt, wf->name, wf->hash, wf->mode); //ajouter un WorkFile dans le WorkTree de retour
  }
  return wt;
}
int wttf(WorkTree* wt,char* file) {//ok 
  //Usage: écrit dans le fichier file la chaine de caractères représentant un WorkTree
  FILE* f = fopen(file,"w");
  if (!f) { //verifier si le fichier file a ete bien ouvert
    printf("WARNING: Unable to open %s\n",file); 
    return -1;
  }
  fprintf(f,"%s",wtts(wt)); //ecrire la description du WorkTree fourni en entree dans le fichier file
  fclose(f); //fermer le fichier
  return 0;
}
WorkTree* ftwt(char* file) {//ok
  //Usage: construit un WorkTree à partir d'un fichier qui contient sa représentation en chaine de caractères
  FILE* f = fopen(file,"r");
  if (!f) { //verifier si le fichier file a ete bien ouvert
    printf("WARNING: The file %s is empty\n",file);
    return NULL;
  }
  WorkTree* wt = initWorkTree(); //initialiser un WorkTree dont on a retourner prochainement
  char buffer[256]; //allouer un buffer pour enregistrer ligne par ligne lors de la lecture du fichier file
  char name[26], hash[256]; //allouer les variables representant les caracteristiques d'un WorkFile
  int mode;
  while (fgets(buffer,256,f)) {
    sscanf(buffer,"%s\t%s\t%d",name,hash,&mode);//scanner les caracteristiques d'un WorkFile dans les variables ainsi alloues
    appendWorkTree(wt,name,hash,mode); //ajouter ce WorkFile dans WorkTree
  }
  fclose(f);
  return wt;
}



/* Part 3 - GESTION DES COMMITS */
/* FONCTION DE BASE */
kvp* createKeyVal(char* key,char* val) {//ok
  //Usage: allouer + initialiser un élément
  kvp* kv = (kvp*)malloc(sizeof(kvp)); //allouer un kvp*
  kv->key = strdup(key); //dupliquer la chaine key en entree dans kv->key
  kv->value = strdup(val); //dupliquer la chaine val en entree dans kv->val
  return kv;
}
void freeKeyVal(kvp* kv) {//ok
  //Usage: libérer la memoire associé à un élément
  free(kv->key); //liberer la chaine associee a la clef d'un element de type kvp
  free(kv->value); //liberer la chaine associee a la valeur de la clef d'un element de type kvp
  free(kv); //desallouer l'espace memoire associe a cet element kvp fourni en entree
  return;
}
char* kvts(kvp* k) {//ok
  //Usage: convertir un élément en une chaine de caractères de la forme (cle:val)
  char* buff = (char*)malloc(MAX_INPUT*sizeof(char));//allouer ce variable afin d'enregistrer prochainement le couple (key,val) de l'element de type kvp pris en entree
  sprintf(buff,"%s:%s",k->key,k->value); //scanner ce couple (key,val) mentionne dans buff
  return buff;
}
kvp* stkv(char* str) {//ok
  //Usage: permet de faire la conversion inverse
  char *key, *val; //declarer 2 variables representant le couple (key,val) 
  key = strtok(str,":\n"); //particulariser la chaine enregistrant le couple (key,val) + les enregistrer dans les 2 variables qui les representent
  val = strtok(NULL,":\n");
  return createKeyVal(key,val); //creer l'element kvp a partir des chaines (key,val) particularisees
}
Commit* initCommit() {//ok
  //Usage: allouer et initialiser un Commit de taille fixée (donnée par une constante du programme)
  Commit* c = (Commit*)malloc(sizeof(Commit)); //allouer un element de type Commit
  c->n = 0; //initialiser le nombre l'element du tableau de Commit a 0 (aucune couple (key,val) ajoute)
  c->size = MAX_INPUT; //initialiser la taille du tableau des couples (key,val) de Commit a MAX_INPUT (constant du programme)
  c->T = (kvp**)malloc(c->size*sizeof(kvp*)); //allouer le tableau des kvp du commit
  for (int i=0;i<c->size;i++)
    c->T[i] = NULL; //initialiser chaque element de ce tableau a NULL
  return c;
}
/* HASH FUNCTION */
int hash(char* str) {
  //Fonction de hachage utilisee a fur a mesure dans ce projet, a expliquer plusieurs dans le rapport de ce choix
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) 
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}
void commitSet(Commit* c,char* key,char* value) {//ok
  
  int h = hash(key)%c->size;
  if (h<0) h = -h;
  while (c->T[h]) 
    h = h+1;
  c->T[h] = createKeyVal(key,value);
  c->n++;
  return;
}
Commit* createCommit(char* hash) {//ok
  Commit* c = initCommit();
  commitSet(c,"tree",hash);
  //c->n++;
  return c;
}
char* commitGet(Commit* c,char* key) {//ok
  for(int i=0;i<c->size;i++) {
    if (c->T[i] && strcmp(c->T[i]->key,key)==0) {
      return c->T[i]->value;
    }
  }
  return NULL;
}
char* cts(Commit* c) {//ok
  char* desc = (char*)malloc(INT_MAX*sizeof(char));
  char* w = NULL;
  for (int i=0;i<MAX_INPUT;i++) {
    if (c->T[i]) {
      w = kvts(c->T[i]);
      printf("%s\n",desc);
      strcat(desc,w); strcat(desc,"\n");
    }
  }
  return desc;
}
Commit* stc(char* file) {//ok
  char str[(int)strlen(file)]; 
  sprintf(str,"%s",file);
  char* desc = str;
  char* ptr; 
  kvp* k; 
  Commit* c = initCommit();
  while((ptr = strtok_r(desc, "\n", &desc))) {
    k = stkv(ptr);
    commitSet(c,k->key,k->value);
  }
  return c;
}
void ctf(Commit* c,char* file) {//ok
  FILE* f = fopen(file,"w");
  if (!f) {
    printf("ctf: Erreur lors de l'ouverture\n");
    return;
  }
  fprintf(f,"%s",cts(c));
  fclose(f); 
  return;
}
Commit* ftc(char* file) {//ok
  Commit* c = initCommit();
  FILE* f = fopen(file,"r");
  if (!f) {
    printf("ftc: Erreur lors de l'ouverture de fichier\n");
    return NULL;
  }
  char buffer[256]; 
  kvp* k;
  while (fgets(buffer,256,f)) {
    k = stkv(buffer);
    commitSet(c,k->key,k->value);
    //fgets(buffer,256,f);
  }
  fclose(f);
  return c;
}



/* Part 4 - GESTION D'UNE TIMELINE ARBORESCENTE */
/* FONCTION DE BASE */
void initBranch(void) {
  system("echo master > .current_branch");
  return;
}
int branchExists(char* branch) {
  return searchList(listdir(".refs"),branch)!=NULL;
}
void createBranch(char* branch) {
  createUpdateRef(branch,getRef("HEAD"));
  return;
}
char* getCurrentBranch(void) {
  FILE* f = fopen(".current_branch","r");
  char* buff = (char*)malloc(PATH_MAX);
  fgets(buff,PATH_MAX,f); 
  fclose(f); 
  return buff;
}
void printBranch(char* branch) {//ok
  char* c_hash = getRef(branch);
  char* hash = hashToPathCommit(c_hash);
  Commit* c = ftc(hash);

  if (commitGet(c,"predecessor")) {
    while(c) {
      if (commitGet(c,"message")) 
        printf("%s -> %s\n",c_hash,commitGet(c,"message"));
      else printf("%s\n",c_hash);
      c_hash = commitGet(c,"predecessor");
      c = ftc(hashToPathCommit(c_hash));
    }
  }
  else {
    if (commitGet(c,"message")) 
      printf("%s -> %s\n",c_hash,commitGet(c,"message"));
    else printf("%s\n",c_hash);
  }
  return;
}
List* branchList(char* branch) {//ok
  char* c_hash = getRef(branch);
  Commit* c = ftc(hashToPathCommit(c_hash));
  List* L = initList();
  while (c) {
    insertFirst(L,buildCell(c_hash));
    if (commitGet(c,"predecessor")) {
      c_hash = commitGet(c,"predecessor");
      c = ftc(hashToPathCommit(c_hash));
    }
    else c = NULL;
  }
  return L;
}
List* getAllCommits(void) {//ok
  List* L = initList();
  List* ref = listdir(".refs");
  for (Cell* ptr=*ref;ptr!=NULL;ptr=ptr->next) {
    if (ptr->data[0]=='.') continue;
    List* branch = branchList(ptr->data);
    while (*branch) {
      if (!searchList(L,(*branch)->data)) 
        insertFirst(L,buildCell((*branch)->data));
      *branch = (*branch)->next;
    }
  }
  return L;
}