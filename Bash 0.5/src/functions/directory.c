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

void remove_dir(const char dirName[], const char path[]) {
    char completePath[MAX_FILENAME];

    if (path[0] != '\0')
        snprintf(completePath, sizeof(completePath), "rmdir c\\%s\\%s", path, dirName);
    else
        snprintf(completePath, sizeof(completePath), "rmdir c\\%s", dirName);

    if (system(completePath)) {
        printf("Erro ao executar o comando");
    } else {
        printf("Diretorio removido com sucesso: %s\n", completePath);
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
        dirList->next = NULL;

        if(parent->childs != NULL){
            DirectoryList *aux = parent->childs;

            while (aux->next != NULL)
                aux = aux->next;

            aux->next = dirList;
        } else
            parent->childs = dirList;
        
        INodeList *aux2 = parent->iNodeList;

        while (aux2->next != NULL)
            aux2 = aux2->next;

        aux2->next = inodeList;

        (parent->childs_cont)++;

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
        snprintf(dir_name, sizeof(dir_name), "c/%s/%s", path, argument);
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

void function_ls(char all[][2][MAX_FILENAME], Directory *currentDirectory, int *countDir, int *countReg){
    INodeList *aux = currentDirectory->iNodeList->next;

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

void function_rmdir(char dirName[], Directory *currentDirectory, char path[]){
    // Directory *previous = NULL;
    // DirectoryList *toRemove = currentDirectory->childs;

    // while (toRemove != NULL && strcmp(toRemove->directory->name, dirName)) {
    //     previous = toRemove;
    //     toRemove = toRemove->next;
    // }
    
    remove_dir(dirName, path);
}