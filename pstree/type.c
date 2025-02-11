#include <stdio.h>
#include <assert.h>

typedef struct PsNode
{
  /* data */
  char name[100];
  struct PsNode * child;
  struct PsNode * parent;
}PsNode;