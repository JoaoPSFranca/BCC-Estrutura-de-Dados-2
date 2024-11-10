#ifndef BLOCK_H
#define BLOCK_H

#define BLOCK_SIZE 4096

typedef struct sBlock {
    int address;
    int status; // 0 free | 1 busy 
    char data[BLOCK_SIZE];
} Block;

typedef struct sFreeBlock {
    Block *block;
    struct sFreeBlock *next;
} FreeBlock;

#endif