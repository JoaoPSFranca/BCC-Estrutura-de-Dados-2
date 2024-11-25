#include <sys/stat.h>

#include "../lib/directory.h"

int verifyDirectory(const char name[]) {
    struct stat st;

    if (stat(name, &st) == 0) {
        return S_ISDIR(st.st_mode);
    }

    return 0;
}

int createDirectory(const char name[]){
    if (!verifyDirectory(name))
        if (!mkdir(name, 755))
            return 1;

    return 0;
}

void printList(INodeList *inodelist){
    INodeList *aux = inodelist;
    
    while (aux != NULL) {
        printf("%s\n", aux->inode->name);
        aux = aux->next;
    }
}

Directory *addDirectory(INode *inode, Directory *parent){
    Directory *dir = malloc(sizeof(Directory));
    INodeList *inodeList = malloc(sizeof(INodeList));

    inodeList->inode = inode;
    inodeList->next = NULL;
    
    dir->inode = inode;
    dir->childs_cont = 0;
    dir->iNodeList = inodeList;
    strcpy(dir->name, inode->name);
    dir->parent = parent;
    dir->childs = NULL;

    if(parent != NULL){
        DirectoryList *dirList = malloc(sizeof(DirectoryList));

        dirList->directory = dir;
        dirList->next = parent->childs;
        parent->childs = dirList;
        
        INodeList *aux = parent->iNodeList;

        while (aux->next != NULL)
            aux = aux->next;

        aux->next = inodeList;
        return dir;
    }

    return dir;
}

Directory *generateRoot(FreeINode **freeInodes, FreeBlock **freeBlocks){
    INode *inode = verifyINodeFree_Directory(freeInodes);
    Block *block = verifyBlockFree(freeBlocks);
    INodeList *inodeList = malloc(sizeof(INodeList));

    inodeList->inode = inode;
    inodeList->next = NULL;

    removeINodeFree(freeInodes, inode);
    removeBlockFree(freeBlocks, block);

    inode->block_count = 1;
    inode->blocks[0] = *block;
    strcpy(inode->name, "c");
    inode->size = 0;

    Directory *root = malloc(sizeof(Directory));
    root->inode = inode;
    root->iNodeList = inodeList;

    strcpy(root->name, "c");
    root->parent = root;
    root->childs = NULL;

    return root;
}

void function_mkdir(char path[], char argument[], FreeINode **freeInodes, FreeBlock **freeBlocks, 
                    INode inodes[], Directory *parent, Block blocks[], int *TLInodes, int *TLBlocks) {
    char dir_name[MAX_FILENAME * 2];

    if (path[0] != '\0')
        snprintf(dir_name, sizeof(dir_name), "./c/%s/%s", path, argument);
    else
        snprintf(dir_name, sizeof(dir_name), "c/%s", argument);
    
    INode *inode = verifyINodeFree_Directory(freeInodes);

    if (inode == NULL)
        printf("No Free INode avaible. \n");
    else {
        Block *block = verifyBlockFree(freeBlocks);

        if (block == NULL) {
            printf("No Free Blocks avaible. \n");
        } else {
            if (!createDirectory(dir_name)) {
                printf("Error: Could not create the directory '%s'. \n\n", argument);
            } else {
                removeINodeFree(freeInodes, inode);   
                removeBlockFree(freeBlocks, block);

                inode->block_count = 1;
                inode->blocks[0] = *block;
                strcpy(inode->name, argument);
                inode->size = 0;

                inodes[(*TLInodes)++] = *inode;
                blocks[(*TLBlocks)++] = *block;

                addDirectory(inode, parent);
            }
        } 
    }
}

void function_ls(char all[][2][MAX_FILENAME], Directory *actualDirectory, int *countDir, int *countReg){
    INodeList *aux = actualDirectory->iNodeList->next;

    strcpy(all[0][0], ".");
    strcpy(all[1][0], "..");
    *countDir = 2;
    *countReg = 0;

    while(aux != NULL){
        if (aux->inode->type == 'r'){
            strcpy(all[*countReg][1], aux->inode->name); 
            (*countReg)++;
        } else {
            strcpy(all[*countDir][0], aux->inode->name); 
            (*countDir)++;
        }

        aux = aux->next;
    }
}