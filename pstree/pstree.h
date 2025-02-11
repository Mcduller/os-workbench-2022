#ifndef PSTREE_H
#define PSTREE_H

#include <dirent.h>
#include "type.h"

int is_pid(struct dirent *dp);
char *get_status_path(struct dirent *dp);
struct PsBaseNode *get_base_node(char *stat_path);
struct PsNodeVector *get_all_ps();

#endif