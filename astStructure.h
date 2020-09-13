#ifndef AST_TREE
#define AST_TREE

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

node *initNode(char* text);

root *initRoot();

void addToRoot(root *tree, node *nodo);

void rewindTree(root *tree);

int nextNode(root *tree);

int backNode(root *tree);

int moveToChild(root *tree);

int moveToParent(root *tree);

int addChild(root *tree, node *nodo);

int addNode(root *tree, node *nodo);

void printTree(root *tree, int altura);

void freeTree(node *nodo);

#endif
