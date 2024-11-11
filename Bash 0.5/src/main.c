/* Caso esteja utilizando o Compile Run no vscode:
    acesse a propriedade:
        @ext:danielpinto8zz6.c-cpp-compile-run C-cpp-compile-run: Output-location 
    apague o campo caso esteja por padrão no output, deixe em .. */

#include <string.h>
#include <ctype.h>

#include "functions/block.c"
#include "functions/inode.c"
#include "functions/directory.c"

void initFileSystem(FreeBlock **freeBlocks, FreeINode **freeInodes, Directory **root) {
    createDirectory("src/Blocks");
    createDirectory("src/Resources");

    generateBlocks(freeBlocks);
    generateInodes(freeInodes);

    (*root) = generateRoot(freeInodes, freeBlocks);

    createDirectory("c"); // root directory 
    printf("Bash 0.5 [versao 2.6]\n\n");
}

void format(char comand[]){
    for (unsigned int i = 0; i < strlen(comand); i++)
        comand[i] = tolower(comand[i]);
}

void format_path(char path[]){
    unsigned int i = strlen(path) - 1;
    
    while (path[i] != '/' && i > 0)
        i--;
    
    path[i] = '\0';
}

void bash(FreeBlock **freeBlocks, FreeINode **freeInodes, Directory **root){
    char 
        comand[10], 
        argument[MAX_FILENAME], 
        entry[MAX_FILENAME * 2], 
        path[100];

    int 
        TLInodes = 0,
        TLBlocks = 0;

    INode inodes[MAX_I_NODE]; // Used INodes
    Block blocks[MAX_BLOCKS]; // Used Blocks
    Directory *actualDirectory = *root;

    path[0] = '\0';

    while (strcmp(comand, "exit")) {
        printf("c:/%s>", path);

        fgets(entry, 50, stdin);
        sscanf(entry, "%s %s", comand, argument);

        format(comand);

        if (!strcmp(comand, "mkdir")) {
            function_mkdir(path, argument, freeInodes, freeBlocks, inodes, actualDirectory, blocks, &TLInodes, &TLBlocks);
        } else if (!strcmp(comand, "cd")) {
            if (!strcmp(argument, ".."))
                format_path(path);
            else {
                if (path[0] != '\0')
                    path[strlen(path)] = '/';
        
                strcat(path, argument);
            }
        } else if (!strcmp(comand, "ls")) {
            
        } else if (!strcmp(comand, "cat")) {
            
        } else if (!strcmp(comand, "rm")) {
            
        } else if (!strcmp(comand, "rmdir")) {
            
        } else if (!strcmp(comand, "mv")) {
            
        } else if (!strcmp(comand, "run")) {
            
        } else if (strcmp(comand, "exit")) {
            printf("%s comando nao reconhecido. ", comand);
        } 
        
    }
    
}

int main(){

    FreeBlock *freeBlocks = malloc(sizeof(FreeBlock));
    FreeINode *freeInodes = malloc(sizeof(FreeINode));
    Directory *root = NULL;
    
    initFileSystem(&freeBlocks, &freeInodes, &root);

    bash(&freeBlocks, &freeInodes, &root);


    return 0;
}