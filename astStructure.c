#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astStructure.h"

node *initNode(char* text){
    node *nodo = malloc(sizeof(node));
    if(nodo){
      strcpy(nodo->word, text);
      nodo->child = NULL;
      nodo->parent = NULL;
      nodo->back = NULL;
      nodo->next = NULL;
    }
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
