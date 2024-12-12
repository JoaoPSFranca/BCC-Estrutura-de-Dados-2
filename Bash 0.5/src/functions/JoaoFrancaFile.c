#include "../lib/JoaoFrancaDirectory.h"

INode *searchFile(INodeList **list, char fileName[MAX_FILENAME]) {
    int flag = 1;
    INodeList *aux = *list;

    while(aux != NULL && flag){
        if (!strcmp(aux->inode->name, fileName))
            flag = 0;
        else
            aux = aux->next;
    }

    if (flag)
        return NULL;
    else
        return aux->inode;
}

int readCatCreate(Block *block, INode *inode){
    int run = 1;
    int full = 0;
    int verify = 0;
    int i = 0;

    while (!full && run) {
        char entry = getch();
       
        if (entry == 04) 
            run = 0;
        else {
            if (!verify)
                verify = 1;
            
            if (entry == 13){
                printf("\n");
                block->data[i++] = '\n';
            } else if (entry == 8){
                if (i > 0) {
                    i--;
                    block->data[i] = '\0';
                    printf("\b \b");
                }
            } else if(entry > 31 && entry < 127) {
                printf("%c", entry);
                block->data[i++] = entry;
            }
            
            if (i == (BLOCK_SIZE - 1))
                full = 1;
        } 
    }

    block->data[i] = '\0';
    inode->blocks[(inode->block_count)++] = *block;

    if (inode->block_count == 15){
        printf("Your file reach the max size. ");
        run = 0;
    }

    return run;
}

void function_cat_create(char fileName[], Directory *dir, FreeINode **fi, FreeBlock **fb) {
    INode *inode = verifyINodeFree(fi, 'r');
    int flag = 1;

    if (inode == NULL)
        printf("No Free INode avaible. \n");
    else {
        while (flag) {
            Block *block = verifyBlockFree(fb);

            if (block == NULL) {
                printf("No Free Blocks avaible. \n");
                flag = 0;
            } else { 
                flag = readCatCreate(block, inode);
                removeBlockFree(fb, block);
            }   
        }
        printf("\n");

        strcpy(inode->name, fileName);

        removeINodeFree(fi, inode);
        INodeList *aux = dir->iNodeList;

        while (aux->next != NULL)
            aux = aux->next;

        INodeList *newNode = malloc(sizeof(INodeList));
        newNode->inode = inode;
        newNode->next = NULL;

        aux->next = newNode;
    }
}

void function_cat_show(INode *inode) {
    int i;
    unsigned int j;
    
    for (i = 0; i < inode->block_count; i++) {
        Block block = inode->blocks[i];

        for (j = 0; j < strlen(block.data); j++)
            printf("%c", block.data[j]);
    }

    printf("\n");
}

void function_rm(INode *inode, Directory *dir, FreeBlock **freeBlock, FreeINode **freeINode){
    int i;
    INodeList *prev = NULL;
    INodeList *aux = dir->iNodeList;

    while (aux != NULL && aux->inode->id != inode->id) {
        prev = aux;
        aux = aux->next;
    }

    if (aux == NULL)
        printf("INode not found. \n\n");
    else if (prev != NULL)
        prev->next = aux->next;

    // alterDirDat(dir);

    for (i = 0; i < inode->block_count; i++)
        enterFreeBlock(freeBlock, &(inode->blocks[i]));
    
    enterINodeFree(freeINode, inode);
}
