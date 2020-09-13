#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astStructure.h"

typedef int Obj;
#define NewObj 0

typedef struct sASTDB
   { root **nums;
     int nnums;
   } astDB;

static astDB DB;

#define db(p) (DB.nums + sizeof(root)*(root)p)

void printobj (Obj obj){
    printTree(obj, 0);
}

int main(int argc, char **argv) {


  printf("-0\n");
  return 0;
}
