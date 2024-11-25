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

        return dir;
    }

    return dir;
}

Directory *generateRoot(FreeINode **freeInodes, FreeBlock **freeBlocks){
    INode *inode = verifyINodeFree_Directory(freeInodes);
    Block *block = verifyBlockFree(freeBlocks);

    removeINodeFree(freeInodes, inode);
    removeBlockFree(freeBlocks, block);

    inode->block_count = 1;
    inode->blocks[0] = *block;
    strcpy(inode->name, "c");
    inode->size = 0;

    Directory *root = malloc(sizeof(Directory));
    root->inode = inode;
    root->iNodeList = NULL;
    strcpy(root->name, "c");
    root->parent = NULL;
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

// void function_ls(char all[][2][MAX_FILENAME], Directory *actualDirectory, int *count){
//     INodeList *aux = actualDirectory->iNodeList;
    


//     while(aux != NULL){
//         strcpy(all[*count][1], aux->inode->name);
//         (*count)++;
//         aux = aux->next;
//     }
// }