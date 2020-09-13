#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astStructure.h"

root **treeFromFile(char* name, int *cantidad){
  FILE *fp;
  int altura, arboles, index;
  int anterior = 0;
  char texto[20];
  node* nodo;
  index = -1;
  fp = fopen(name, "r");
  fscanf(fp, "%d", &arboles);
  *cantidad = arboles;
  root **arrTree = malloc(sizeof(root)*arboles);
  while(fscanf(fp, "%d %s", &altura, texto) != -1){
      if(altura == -1 && !strcmp(texto, "EOF")){
          index++;
          arrTree[index] = initRoot();
          continue;
      }
      nodo = initNode(texto);
      if(arrTree[index]->begin == NULL){
          addToRoot(arrTree[index], nodo);
          continue;
      }
      else{
          if(anterior == altura){
              addNode(arrTree[index], nodo);
          }
          else if(altura-anterior < 0){
              for(int i = 0; i<anterior-altura; i++){
                  moveToParent(arrTree[index]);
              }
              addNode(arrTree[index], nodo);
          }
          else{
              addChild(arrTree[index], nodo);
          }
          anterior = altura;
      }
  }
  fclose(fp);
  return arrTree;
}

int faltantes(node* nodo){
      if(nodo == NULL){
        return 1;
      }
      return faltantes(nodo->next) + faltantes(nodo->child);
}

int identicalTrees(node* nodo1, node* nodo2){
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
        return identicalTrees(nodo1->next,nodo2->next) + identicalTrees(nodo1->child,nodo2->child) + 1;
    }
    else{
        return identicalTrees(nodo1->next,nodo2->next) + identicalTrees(nodo1->child,nodo2->child);
    }

}

int main(){
  int arboles = 0;
  root **trees;
  trees = treeFromFile("todoExample.txt", &arboles);
  rewindTree(trees[0]);
  printTree(trees[0], 0);
  printf("\n");
  rewindTree(trees[1]);
  printTree(trees[1], 0);
  printf("%d\n", identicalTrees(trees[0]->begin, trees[2]->begin));
  return 0;
}
