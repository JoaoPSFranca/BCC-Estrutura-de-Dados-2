#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "inode.h"

typedef struct sDirectory {
    INode inode;
    INodeList *inodelist;
    char name[MAX_FILENAME]; 
    struct sDirectory *parent; // ..
    struct sDirectory *childs; // sub directories
} Directory;

#endif 