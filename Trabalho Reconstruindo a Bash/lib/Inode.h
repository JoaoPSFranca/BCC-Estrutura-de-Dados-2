#ifndef INODE_H
#define INODE_H

#include "block.h"
#define MAX_FILENAME 256

typedef struct sINode {
    int id;
    char type;
    char name[MAX_FILENAME];
    long int size;
    int block_count;
    Block blocks[15];
} INode;

typedef struct sFreeINode {
    int id; 
    struct sFreeINode *next; 
} FreeINode;

typedef struct sINodeList {
    INode inode; 
    struct sINodeList *next; 
} INodeList;

#endif // INODE_H