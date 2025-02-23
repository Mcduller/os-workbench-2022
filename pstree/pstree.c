#include <stdio.h>
#include <assert.h>
#include "type.h"
#include "type.c"
#include <dirent.h>
#include "pstree.h"

struct PsNodeVector *get_all_ps()
{
  struct PsNodeVector *psvc = creat_ps_vec();
  DIR *dir;
  struct dirent *dp;
  dir = opendir("/proc");
  if (dir == NULL)
  {
    perror("Cannot open /proc directory");
    return NULL;
  }

  while ((dp = readdir(dir)) != NULL)
  {
    if (is_pid(dp))
    {
      char *stat_path;
      struct PsBaseNode *psBaseNode;

      stat_path = get_status_path(dp);
      if (stat_path)
      {
        psBaseNode = get_base_node(stat_path);
        ps_vec_push(psvc, psBaseNode);
      }
    }
  }
  closedir(dir);
  return psvc;
}

struct PsBaseNode *get_base_node(char *stat_path)
{
  FILE *fp = fopen(stat_path, "r");
  if (!fp)
    return NULL;

  int process_pid;
  char comm[256];
  int ppid;

  if (fscanf(fp, "%d (%[^)]) %*c %d", &process_pid, comm, &ppid) == 3)
  {
    fclose(fp);
    return create_base_node(process_pid, ppid, strdup(comm));
  }

  fclose(fp);
  return NULL;
}

char *get_status_path(struct dirent *dp)
{
  char *stat_path = (char *)malloc(256); // 使用合适的大小，这里用256作为示例
  if (stat_path == NULL)
  {
    return NULL; // 内存分配失败
  }

  // 使用已分配的内存
  snprintf(stat_path, 256, "/proc/%s/stat", dp->d_name);
  return stat_path;
}

int is_pid(struct dirent *dp)
{
  int is_pid = 1;
  for (int i = 0; dp->d_name[i] != '\0'; i++)
  {
    if (dp->d_name[i] < '0' || dp->d_name[i] > '9')
    {
      is_pid = 0;
      break;
    }
  }
  return is_pid;
}

int main(int argc, char *argv[])
{
  printf("hello1\n");
  // 获取所有进程信息
  struct PsNodeVector *processes = get_all_ps();
  if (!processes) {
    fprintf(stderr, "Failed to get process information\n");
    return 1;
  }

  // // 打印表头
  printf("\n%-8s %-8s %-30s\n", "PID", "PPID", "NAME");
  printf("----------------------------------------\n");

  // // 遍历并打印所有进程信息
  int error_count = 0;
  for (int i = 0; i < processes->size; i++) {
    struct PsBaseNode *proc = processes->data[i];
    if (proc) {
      printf("%-8d %-8d %-30s\n", 
             proc->pid,
             proc->ppid,
             proc->name ? proc->name : "(unknown)");
    } else {
      error_count++;
    }
  }

  // 打印统计信息
  // test commit
  printf("\nStatistics:\n");
  printf("Total processes: %d\n", processes->size);
  if (error_count > 0) {
    printf("Failed to read: %d\n", error_count);
  }

  // 清理内存
  for (int i = 0; i < processes->size; i++) {
    if (processes->data[i]) {
      free(processes->data[i]->name);  // 释放进程名
      free(processes->data[i]);        // 释放节点
    }
  }
  free(processes->data);  // 释放数组
  free(processes);        // 释放vector

  return 0;
}
