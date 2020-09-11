#include <stdio.h>
#include <stdlib.h>
#include "astStructure.h"

node *initNode(char* text){
    node *nodo = malloc(sizeof(node));
    if(nodo){
      nodo->word = text;
      nodo->block = 0;
      nodo->child = NULL;
      nodo->parent = NULL;
      nodo->back = NULL;
      nodo->next = NULL;
    }
    return nodo;
}

root *initRoot(node *nodo){
    root *tree = malloc(sizeof(root));
    tree->nodes = 1;
    tree->begin = nodo;
    tree->current = nodo;
    return tree;
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
    tree->current->next = nodo;
    nodo->back = tree->current;
    tree->current = tree->current->next;
    tree->nodes++;

    return 0;
}

void printTree(root *tree, int aux){
    if(tree->current->next == NULL && tree->current->child == NULL){
      return;
    }
    if(tree->current->child != NULL){
      moveToChild(tree);
      aux = 1;
      printf(" -> %s %d", tree->current->word, tree->current->block);
      printTree(tree, aux);
      moveToParent(tree);
      aux = 0;
    }
    if(tree->current->next != NULL){
      nextNode(tree);
      if(aux == 1){
          printf(" -> %s %d", tree->current->word, tree->current->block);
      }
      else{
          printf("\n-> %s %d", tree->current->word, tree->current->block);
      }
      printTree(tree, aux);
      backNode(tree);
    }
}
