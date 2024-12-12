/* 
Caso esteja utilizando o Compile Run no vscode:
    acesse a propriedade:
        @ext:danielpinto8zz6.c-cpp-compile-run C-cpp-compile-run: Output-location 
    apague o campo caso esteja por padrão no output, deixe em .. 
De preferência rodar também em terminal externo
*/

/* 
    bug de dar backspace mais de uma vez
    Implementar o mv
    Implementar o run
*/ 

#include <string.h>
#include <ctype.h>

#include "functions/JoaoFrancaBlock.c"
#include "functions/JoaoFrancaInode.c"
#include "functions/JoaoFrancaDirectory.c"
#include "functions/JoaoFrancaFile.c"

void initFileSystem(FreeBlock **freeBlocks, FreeINode **freeInodes, Directory **root) {
    *root = NULL;
    // int flag = 0;

    if(!verifyDirectory("src/Blocks") && !verifyDirectory("src/Resources")) {
        // flag = 1;
        // flag = readINodeDat(freeInodes);
    //} else {
        createDirectory("src/Blocks");
        createDirectory("src/Resources");    
    }

    // if (!flag) {
        generateBlocks(freeBlocks);
        generateInodes(freeInodes);
    // } 
    // else {
    //     // readBlockDat(freeBlocks);
    //     // readDirectoryDat(root);
    // }
    
    // if (*root == NULL)
        *root = generateRoot(freeInodes, freeBlocks);
    
    printf("Bash 0.5 [versao 3.3.1]\n\n");
}

void format(char comand[]){
    for (unsigned int i = 0; i < strlen(comand); i++)
        comand[i] = tolower(comand[i]);
}

void format_path(char path[]){
    unsigned int i = strlen(path) - 1;
    
    while (path[i] != '/' && i > 0){
        path[i] = '\0';
        i--;
    }
    
    path[i] = '\0';
}

void print_ls(char all[][2][MAX_FILENAME], int countDir, int countReg){
    int i;
    
    for (i = 0; i < countDir; i++)
        printf("%s\t<dir>\n", all[i][0]);
    
    for (i = 0; i < countReg; i++)
        printf("%s\n", all[i][1]);
}

int validateArgument(char argument[], char comand[]){
    if(!strcmp(argument, "")) {
        if (!strcmp(comand, "cls") || !strcmp(comand, "clear") ||
            !strcmp(comand, "ls") || !strcmp(comand, "exit")) {
            return 1;
        } else
            return 0;
    } else 
        return 1;
}

int validateDirName(char argument[]){
    unsigned int i;
    int flag = 0;

    for (i = 0; i < strlen(argument); i++) {
        if (argument[i] == '\\' || argument[i] == '/'){
            flag = 1;
            i = strlen(argument);
        }
    }
    
    return flag;
}

int validateFileName(char fileName[]){
    unsigned int i;
    int flag = 0;

    for (i = 0; i < strlen(fileName); i++) {
        if (fileName[i] == '.')
            flag = 1;
    }

    return flag;
}

int verifyArgumentCat(char argument[]){
    unsigned int i;
    int flag = 0;

    for (i = 0; i < strlen(argument); i++)
        if (argument[i] == '>')
            flag = 1;

    return flag;
}

void bash(FreeBlock **freeBlocks, FreeINode **freeInodes, Directory **root){
    char 
        comand[10] = "", 
        argument[MAX_FILENAME + 7], 
        entry[MAX_FILENAME * 2], 
        path[100],
        fileName[MAX_FILENAME];

    Directory *currentDirectory = *root;
    
    path[0] = '\0';

    while (strcmp(comand, "exit")) {
        printf("c:/%s>", path);

        fgets(entry, sizeof(entry), stdin);
        sscanf(entry, "%s %[^\n]", comand, argument);

        comand[strcspn(comand, "\n")] = '\0'; 

        format(comand);
        if (!validateArgument(argument, comand))
            printf("Command missing argument. \n\n");
        else {
            if (!strcmp(comand, "mkdir")) {
                if (validateDirName(argument))
                    printf("Invalid charcter '/' or '\\'. \n\n");
                else
                    function_mkdir(argument, freeInodes, freeBlocks, currentDirectory);
            } else if (!strcmp(comand, "cd")) {
                if (!strcmp(argument, "..")){
                    if (path[0] != '\0'){
                        currentDirectory = currentDirectory->parent;
                        format_path(path);
                    } else
                        printf("Error: You are already in the root directory.\n\n");
                } else if (!strcmp(argument, "/")){
                    path[0] = '\0';
                    currentDirectory = *root;
                } else if (verifyDirFS(currentDirectory->iNodeList->next, argument)){
                    if (path[0] != '\0'){
                        path[strlen(path)] = '/';

                        while (path[strlen(path)-1] != '/')
                            path[strlen(path)-1] = '\0';
                    }

                    DirectoryList *aux = currentDirectory->childs;
                    while (strcmp(aux->directory->name, argument) && aux != NULL)
                        aux = aux->next;

                    if (aux == NULL || aux->directory == *root)
                        printf("Directory exists, but not found in current file system. \n\n");
                    else{
                        currentDirectory = aux->directory;
                        strcat(path, argument);
                    }
                } else if (strcmp(argument, "."))
                    printf("The system could not find the specified path. \n\n");
            } else if (!strcmp(comand, "ls")) {
                char all[MAX_I_NODE][2][FILENAME_MAX];
                int countReg, countDir;
                function_ls(all, currentDirectory, &countDir, &countReg);
                print_ls(all, countDir, countReg);
            } else if (!strcmp(comand, "cat")) {
                if (verifyArgumentCat(argument)) { // create file
                    sscanf(argument, "> %s", fileName);
                    
                    if (validateDirName(fileName))
                        printf("Invalid charcter '/' or '\\'. \n\n");
                    else if(!validateFileName(fileName))
                        printf("Missing file extension. \n\n");
                    else
                        function_cat_create(fileName, currentDirectory, freeInodes, freeBlocks);

                    // alterDirDat(currentDirectory);
                } else { // open file
                    sscanf(argument, "%s", fileName);

                    INode *inode = searchFile(&(currentDirectory->iNodeList), fileName);

                    if (inode == NULL)
                        printf("File not found. \n\n");
                    else
                        function_cat_show(inode);
                }
            } else if (!strcmp(comand, "rm")) {
                sscanf(argument, "%s", fileName);

                INode *inode = searchFile(&(currentDirectory->iNodeList), fileName);

                if (inode == NULL)
                    printf("File not found. \n\n");
                else
                    function_rm(inode, currentDirectory, freeBlocks, freeInodes);
            } else if (!strcmp(comand, "rmdir")) {
                function_rmdir(argument, currentDirectory, freeBlocks, freeInodes);
            } else if (!strcmp(comand, "mv")) {
                printf("Coming soon. Not implemented yet. \n\n");
            } else if (!strcmp(comand, "run")) {
                printf("Coming soon. Not implemented yet. \n\n");
            } else if (!strcmp(comand, "cls") || !strcmp(comand, "clear")){
                system("cls");
            } else if (strcmp(comand, "exit")) {
                printf("%s comand not recognized. \n\n", comand);
            } 
        }
        
        strcpy(argument, "");
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
