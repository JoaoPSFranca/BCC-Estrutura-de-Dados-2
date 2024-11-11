#include <sys/stat.h>

#include "../lib/directory.h"

int verifyDirectory(const char name[]){
    struct stat st;
    
    return (stat(name, &st) != 0 && S_ISDIR(st.st_mode));
}

int createDirectory(const char name[]){
    if (!verifyDirectory(name) || mkdir(name, 0755))
        return 0;

    return 1;
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

    DirectoryList *dirList = malloc(sizeof(DirectoryList));

    dirList->directory = dir;
    dirList->next = parent->childs;
    parent->childs = dirList;

    return dir;
}

Directory *generateRoot(FreeINode **freeInodes, FreeBlock **freeBlocks){
    INode *inode = verifyINodeFree_Directory(freeInodes);
    Block *block = verifyBlockFree(freeBlocks);

    removeINodeFree(freeInodes, inode);   
    removeBlockFree(freeBlocks, block);

    inode->block_count = 1;
    inode->blocks[0] = *block;
    strcpy(inode->name, "root");
    inode->size = 0;

    Directory *root = malloc(sizeof(Directory));
    root->inode = inode;
    root->iNodeList = NULL;
    strcpy(root->name, "root");
    root->parent = NULL;
    root->childs = NULL;

    return root;
}

void function_mkdir(char path[], char argument[], FreeINode **freeInodes, FreeBlock **freeBlocks, 
                    INode inodes[], Directory *parent, Block blocks[], int *TLInodes, int *TLBlocks) {
    char dir_name[MAX_FILENAME * 2];

    snprintf(dir_name, sizeof(dir_name), "c/%s%s", path, argument);
    
    INode *inode = verifyINodeFree_Directory(freeInodes);

    if (inode == NULL)
        printf("Nenhum INode disponivel. \n");
    else {
        Block *block = verifyBlockFree(freeBlocks);

        if (block == NULL) {
            printf("Nenhum Bloco disponivel. \n");
        } else {
            if (!createDirectory(dir_name)) {
                printf("Erro ao criar o diretorio %s. %s\n", argument, dir_name);
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