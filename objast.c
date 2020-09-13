#include "../../obj.h"

#include <stdio.h>
#include <stdlib.h>
#include "astStructure.h"

//En este caso los Obj son los roots de los arboles

#define db(p) (DB.nums[p])

static int never = 1;

typedef struct sAstDB{
    root **nums;
    int nnums;
} astDB;

static astDB DB;

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
        return levenshtein(nodo1->next,nodo2->next) + identicalTrees(nodo1->child,nodo2->child) + 1;
    }
    else{
        return levenshtein(nodo1->next,nodo2->next) + identicalTrees(nodo1->child,nodo2->child);
    }
}



// Funciones solicitadas por el header

/*
Calcula la distancia entre un arbol y otro.
Se proponen 3 tipos de distancias:
levenshtein: Que verifica el insert, delete y el modify.
LCS: Este solo tiene insert y delete. Para casos de modify tiene que eliminar y agregar otra vez.
levenshteinModificated: Al igual que el anterior pero que en modify verifique el levenshtein
de los strings que contiene, asi tener una distancia mas comparativa.

Al sumar, tratar de dejar un valor constante al 1, de tal manera que si cada regla tiene peso distinto.
*/

int distanceInter (Obj o1, Obj o2){
    return ted(db(o1)->begin,db(o2)->begin);
    //return LCS(db(o1),db(o2));
    //return levenshteinModificated(db(o1),db(o2));
}

//Dado un archivo, crea los arboles que existen y los deja en DB
int openDB (char *name){
    FILE *fp;
    int altura, index;
    int anterior = 0;
    char texto[20];
    node* nodo;
    index = -1;

    //Tenemos que liberar antes de poder abrir, la libreria asi lo especifica
    closeDB();

    //Hace un arreglo de root que contienen los arboles, todo a partir del nombre del archivo
    fp = fopen(name, "r");
    fscanf(fp, "%d", &DB.nnums);
    DB.nums = malloc(sizeof(root)*DB.nnums);
    while(fscanf(fp, "%d %s", &altura, texto) != -1){
        if(altura == -1 && !strcmp(texto, "EOF")){
            index++;
            DB.nums[index] = initRoot();
            continue;
        }
        nodo = initNode(texto);
        if(DB.nums[index]->begin == NULL){
            addToRoot(DB.nums[index], nodo);
            continue;
        }
        else{
            if(anterior == altura){
                addNode(DB.nums[index], nodo);
            }
            else if(altura-anterior < 0){
                for(int i = 0; i<anterior-altura; i++){
                    moveToParent(DB.nums[index]);
                }
                addNode(DB.nums[index], nodo);
            }
            else{
                addChild(DB.nums[index], nodo);
            }
            anterior = altura;
        }
    }
    fclose(fp);
    for(int i = 0; i < DB.nnums; i++){
      rewindTree(DB.nums[i]);
    }
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
    //TODO: Aprender que hace esto xd
    return NewObj;
}

//Muestra la forma del arbol en consola
void printobj (Obj obj){
    rewindTree(obj);
    printTree(obj, 0);
    printf("\n");
}
