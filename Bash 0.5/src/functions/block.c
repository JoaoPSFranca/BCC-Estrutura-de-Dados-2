#include "../lib/block.h"

void generateBlocks(FreeBlock **freeBlocks){
    *freeBlocks = malloc(sizeof(FreeBlock));
    FreeBlock *aux = *freeBlocks;

    for (unsigned int i = 0; i < MAX_BLOCKS; i++) {
        FILE *archive;
        char filename[70];

        snprintf(filename, sizeof(filename), "src/Blocks/%02d.dat", i + 1);

        archive = fopen(filename, "wb");

        if (archive != NULL) {
            Block *block = malloc(sizeof(Block));
            strcpy(block->address, filename);
            block->status = 0; // free block

            fwrite(block, sizeof(Block), 1, archive);
            fclose(archive);
            aux->block = block;

            if (i < MAX_BLOCKS - 1) {
                aux->next = malloc(sizeof(FreeBlock));
                aux = aux->next;
            } else {
                aux->next = NULL; 
            }
            free(block);
        } else {
            printf("Error opening file. \n");
        }
    }
}

Block *verifyBlockFree(FreeBlock **freeBlocks){
    FreeBlock *aux = *freeBlocks;

    while (aux->block->status != 0 && aux != NULL)
        aux = aux->next;
    
    if (aux == NULL)
        return NULL;
    
    return aux->block;
}

void removeBlockFree(FreeBlock **freeBlocks, Block *block){
    if (strcmp((*freeBlocks)->block->address, block->address) == 0) {
        (*freeBlocks) = (*freeBlocks)->next;
    } else {
        FreeBlock *aux = *freeBlocks;
        FreeBlock *aux2 = NULL;

        while (strcmp(aux->block->address, block->address) == 0 && aux != NULL) {
            aux2 = aux;
            aux = aux->next; 
        }

        if (aux != NULL)
            aux2->next = aux->next;
        else
            printf("Block not found. \n");
    }
}

