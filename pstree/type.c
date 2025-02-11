#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct PsBaseNode *create_base_node(int pid, int ppid, const char *name)
{
  struct PsBaseNode *node = (struct PsBaseNode *)malloc(sizeof(struct PsBaseNode));
  node->pid = pid;
  node->ppid = ppid;
  node->name = strdup(name);
  if (node->name == NULL)
  {
    free(node); // 如果strdup失败，释放之前分配的内存
    return NULL;
  }
  return node;
}

struct PsNodeVector *creat_ps_vec()
{
  struct PsNodeVector *psvec = malloc(sizeof(struct PsNodeVector));
  psvec->capacity = 16;
  psvec->size = 0;
  psvec->data = malloc(sizeof(struct PsBaseNode *) * psvec->capacity);
  return psvec;
}

void ps_vec_push(struct PsNodeVector *vec, struct PsBaseNode *node)
{
  if (vec->size >= vec->capacity)
  {
    vec->capacity *= 2;
    vec->data = realloc(vec->data, sizeof(struct PsBaseNode *) * vec->capacity);
  }
  vec->data[vec->size++] = node;
}
