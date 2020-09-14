#include "../../obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//En este caso los Obj son los roots de los arboles

#define db(p) (DB.nums[p])

#define LARGO 200


//Estructura de arbol
typedef struct node {
    char word[20];
    struct node *child;
    struct node *parent;
    struct node *next;
    struct node *back;
}node;

typedef struct root {
    int nodes;
    node *begin;
    node *current;
}root;

node *initNode(char* text){
    node *nodo = malloc(sizeof(node));
    strcpy(nodo->word, text);
    nodo->child = NULL;
    nodo->parent = NULL;
    nodo->back = NULL;
    nodo->next = NULL;
    return nodo;
}

root *initRoot(){
    root *tree = malloc(sizeof(root));
    tree->nodes = 0;
    tree->begin = NULL;
    tree->current = NULL;
    return tree;
}

void addToRoot(root *tree, node *nodo){
    if(tree->begin != NULL){
        return;
    }
    tree->nodes = 1;
    tree->begin = nodo;
    tree->current = nodo;
}

void rewindTree(root *tree){
    tree->current = tree->begin;
}

int nextNode(root *tree){
    if(tree->current->next == NULL){
        return -1;
    }
    tree->current = tree->current->next;
    return 0;
}


int backNode(root *tree){
    if(tree->current->back == NULL){
        return -1;
    }
    tree->current = tree->current->back;
    return 0;
}

int moveToChild(root *tree){
    if(tree->current->child == NULL){
        return -1;
    }
    tree->current = tree->current->child;
    return 0;
}

int moveToParent(root *tree){
  if(tree->current->parent == NULL){
      return -1;
  }
  tree->current = tree->current->parent;
  return 0;
}

int addChild(root *tree, node *nodo){
    if(tree->current->child != NULL){
      return -1;
    }
    tree->current->child = nodo;
    nodo->parent = tree->current;
    tree->current = tree->current->child;
    tree->nodes++;
    return 0;
}

int addNode(root *tree, node *nodo){
    if(tree->current->next != NULL){
      return -1;
    }
    if(tree->current->parent != NULL){
      nodo->parent = tree->current->parent;
    }
    tree->current->next = nodo;
    nodo->back = tree->current;
    tree->current = tree->current->next;
    tree->nodes++;

    return 0;
}

void printTree(root *tree, int altura){
    while(tree->current->next != NULL){
      for(int i = 0; i< altura; i++){
        printf("|\t");
      }
      printf("-> %s\n",tree->current->word);
      if(tree->current->child != NULL){
         moveToChild(tree);
         printTree(tree, altura+1);
         moveToParent(tree);
      }
      nextNode(tree);
    }
    for(int i = 0; i< altura; i++){
      printf("|\t");
    }
    printf("-> %s\n", tree->current->word);
    if(tree->current->child != NULL){
       moveToChild(tree);
       printTree(tree, altura+1);
       moveToParent(tree);
    }
    nextNode(tree);
}

void freeTree(node *nodo){
    if(nodo == NULL){
      return;
    }

    freeTree(nodo->next);
    freeTree(nodo->child);

    free(nodo);
}

//

static int never = 1;

typedef struct sAstDB{
    root **nums;
    int nnums;
} astDB;

static astDB DB;

//Hace un Obj a partir de un string de arbol.
root *makeTreeString(char* texto){
    root* tree = initRoot();
    int altura, anterior, index;
    altura = 0;
    anterior = 0;
    index = 0;
    node* nodo;
    char word[20];
    for(int i = 0; i < strlen(texto); i++){
        if(texto[i] == ','){
            nodo = initNode(word);
            if(tree->begin == NULL){
                addToRoot(tree, nodo);
                index = 0;
                memset(word, 0, 20);
                continue;
            }
            if(altura == anterior){
                addNode(tree, nodo);
            }
            else if(altura-anterior < 0){
                for(int j = 0; j < anterior-altura; j++){
                    moveToParent(tree);
                }
                addNode(tree, nodo);
            }
            else{
                addChild(tree, nodo);
            }
            anterior = altura;
            index = 0;
            memset(word, 0, 20);
        }
        else if(texto[i] == '('){
            nodo = initNode(word);
            if(altura == anterior){
                addNode(tree, nodo);
            }
            else if(altura-anterior < 0){
                for(int j = 0; j < anterior-altura; j++){
                    moveToParent(tree);
                }
                addNode(tree, nodo);
            }
            else{
                addChild(tree, nodo);
            }
            anterior = altura;
            altura++;
            index = 0;
            memset(word, 0, 20);
        }
        else if(texto[i] == ')'){
            if(texto[i-1] == ')'){
              altura--;
              continue;
            }
            nodo = initNode(word);
            if(altura == anterior){
                addNode(tree, nodo);
            }
            else if(altura-anterior < 0){
                for(int j = 0; j < anterior-altura; j++){
                    moveToParent(tree);
                }
                addNode(tree, nodo);
            }
            else{
                addChild(tree, nodo);
            }

            anterior = altura;
            altura--;
            index = 0;
            memset(word, 0, 20);
        }
        else{
            word[index] = texto[i];
            index++;
        }
    }
    return tree;
}

int faltantes(node* nodo){
      if(nodo == NULL){
        return 1;
      }
      return faltantes(nodo->next) + faltantes(nodo->child);
}

int ted(node* nodo1, node* nodo2){
    if(nodo1 == NULL || nodo2 == NULL){
        if(nodo1 == NULL && nodo2 == NULL){
            return 0;
        }
        else if(nodo2 == NULL){
            return faltantes(nodo1)-1;
        }
        else{
            return faltantes(nodo2)-1;
        }
    }
    if(strcmp(nodo1->word, nodo2->word)){
        return ted(nodo1->next,nodo2->next) + ted(nodo1->child,nodo2->child) + 1;
    }
    else{
        return ted(nodo1->next,nodo2->next) + ted(nodo1->child,nodo2->child);
    }
}



// Funciones solicitadas por el header

/*
Calcula la distancia entre un arbol y otro.
Se proponen 3 tipos de distancias:
ted: Que verifica el insert, delete y el modify.
levenshteinModificated: Al igual que el anterior pero que en modify verifique el levenshtein
de los strings que contiene, asi tener una distancia mas comparativa.
LCS: Este solo tiene insert y delete. Para casos de modify tiene que eliminar y agregar otra vez.

Al sumar, tratar de dejar un valor constante al 1, de tal manera que si cada regla tiene peso distinto.
*/

//Muestra la forma del arbol en consola
void printobj (Obj obj){
    root *tree = db(obj);
    rewindTree(tree);
    printTree(tree, 0);
    printf("\n");
}

Tdist distanceInter (Obj o1, Obj o2){
    return ted(db(o1)->begin,db(o2)->begin);
    //return LCS(db(o1),db(o2));
    //return levenshteinModificated(db(o1),db(o2));
}

//Dado un archivo, crea los arboles que existen y los deja en DB
int openDB (char *name){
  FILE *fp;
  int index;
  char texto[LARGO];

  closeDB();

  fp = fopen(name, "r");
  fgets(texto, sizeof(int), fp);
  DB.nnums = atoi(texto);
  //Sujeto a Prueba
  memset(texto, 0, LARGO);
  //
  index = 0;
  DB.nums = malloc(sizeof(root)*(DB.nnums+1));
  while(fgets(texto, LARGO, fp)) {
    root * tree = makeTreeString(texto);
    DB.nums[index] = tree;
    index++;
  }
  fclose(fp);
  return DB.nnums;
}

//Libera toda la memoria solicitada con malloc, desde los nodos, el root y la db
void closeDB (void){
    if (never){
        DB.nums = NULL;
        never = 0;
    }
    if (DB.nums == NULL){
        return;
    }
    for(int i = 0; i < DB.nnums; i++){
        freeTree(DB.nums[i]->begin);
        free(DB.nums[i]);
    }
    free(DB.nums);
    DB.nums = NULL;
}

Obj parseobj (char *p){
    db(NewObj) = makeTreeString(p);
    return NewObj;
}
