#include <stdio.h>
#include <assert.h>

typedef struct PsNode
{
  /* data */
  char name[100];
  struct PsNode * child;
  struct PsNode * parent;
}PsNode;

void insert(PsNode * node,char name)
{
    PsNode* newNode=(PsNode*)malloc(sizeof(PsNode));
    *newNode->name=name;

    
    return 0;
}