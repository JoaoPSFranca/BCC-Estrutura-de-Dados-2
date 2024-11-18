/* Caso esteja utilizando o Compile Run no vscode:
    acesse a propriedade:
        @ext:danielpinto8zz6.c-cpp-compile-run C-cpp-compile-run: Output-location 
    apague o campo caso esteja por padrão no output, deixe em .. */


/*
    Criar verificação se o arquivo existe na hora de dar o cd
*/

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

    *root = generateRoot(freeInodes, freeBlocks);
    
    createDirectory("c"); // root directory 
    printf("Bash 0.5 [versao 2.7.2]\n\n");
}

void format(char comand[]){
    for (unsigned int i = 0; i < strlen(comand); i++)
        comand[i] = tolower(comand[i]);
}

void format_path(char path[]){
    unsigned int i = strlen(path) - 1;
    
    while (path[i] != '/' && i > 0){
        i--;
        path[i] = '\0';
    }
    
    path[i] = '\0';
}

void bash(FreeBlock **freeBlocks, FreeINode **freeInodes, Directory **root){
    
    char 
        comand[10] = "", 
        argument[MAX_FILENAME], 
        entry[MAX_FILENAME * 2], 
        path[100],
        complete_path[100];
    int 
        TLInodes = 0,
        TLBlocks = 0;

    printf("amo o jorg\n");
    INode inodes[MAX_I_NODE]; // Used INodes
    Directory *actualDirectory = *root;
    Block blocks[MAX_BLOCKS]; // Used Blocks
    
    path[0] = '\0';

    while (strcmp(comand, "exit")) {
        printf("c:/%s>", path);

        fgets(entry, 50, stdin);
        sscanf(entry, "%s %s", comand, argument);

        comand[strcspn(comand, "\n")] = '\0'; 

        format(comand);

        if (!strcmp(comand, "mkdir")) {
            function_mkdir(path, argument, freeInodes, freeBlocks, inodes, actualDirectory, blocks, &TLInodes, &TLBlocks);
        } else if (!strcmp(comand, "cd")) {
            if (path[0] != '\0')
                snprintf(complete_path, sizeof(complete_path), "c/%s/%s", path, argument);
            else
                snprintf(complete_path, sizeof(complete_path), "c/%s", argument);

            printf("%s\n", complete_path);

            if (!strcmp(argument, ".."))
                format_path(path);
            else if (!strcmp(argument, "/"))
                path[0] = '\0';
            else if (verifyDirectory(complete_path)){
                if (path[0] != '\0'){
                    path[strlen(path)] = '/';

                    while (path[strlen(path)-1] != '/')
                        path[strlen(path)-1] = '\0';
                }

                strcat(path, argument);
            } else 
                printf("O sistema nao pode encontrar o caminho especificado. \n\n");
        } else if (!strcmp(comand, "ls")) {
            
        } else if (!strcmp(comand, "cat")) {
            
        } else if (!strcmp(comand, "rm")) {
            
        } else if (!strcmp(comand, "rmdir")) {
            
        } else if (!strcmp(comand, "mv")) {
            
        } else if (!strcmp(comand, "run")) {
            
        } else if (!strcmp(comand, "cls") || !strcmp(comand, "clear")){
            system("cls");
        } else if (strcmp(comand, "exit")) {
            printf("%s comando nao reconhecido. \n\n", comand);
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