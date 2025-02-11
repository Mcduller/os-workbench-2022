#ifndef PS_TYPE_H
#define PS_TYPE_H

struct PsBaseNode {
    int pid;
    int ppid;
    char* name;
};

struct PsTreeNode {
    struct PsBaseNode *base;
    struct child_list *child;
    struct PsTreeNode *parent;  // 修正：使用PsTreeNode而不是PsNode
};

struct child_list {
    struct PsTreeNode *child;   // 修正：使用PsTreeNode而不是PsNode
    struct child_list *next;
};

struct PsNodeVector {
    struct PsBaseNode **data;
    int size;      // 当前元素个数
    int capacity;  // 当前容量
};


#endif