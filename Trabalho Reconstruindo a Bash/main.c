#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_I_NODE 30
#define MAX_BLOCKS 60
#define BLOCK_SIZE 8

typedef struct sBlock{
    int address;
    int status;
} Block;

typedef struct sINode{
    int id;
    char type;
    char name[256];
    int size;
    Block blocks[15];
} INode;

typedef struct sFreeBlock{
    Block *block;
    struct sFreeBlock *back;
    struct sFreeBlock *next;
} FreeBlock;

void generateBlocks(FreeBlock *fb){
    for (unsigned int i = 0; i < MAX_BLOCKS; i++){
        FILE *archive;
        char name_archive[70];

        snprintf(name_archive, sizeof(name_archive), "../Blocks/%02d.dat", i);

        archive = fopen(name_archive, "wb");

        if(archive != NULL){
            Block block;

            block.address = i;
            block.status = 0;

            fwrite(&block, sizeof(Block), 1, archive);
            
            fclose(archive);
        } else
            printf("Error opening file\n");
    }
}

void generateInodes(){
    FILE *archive;
    
    archive = fopen("../Resources/INodes.dat", "wb");
    
    if(archive != NULL){
        for (unsigned int i = 0; i < MAX_I_NODE; i++){
            INode inode;

            inode.id = i;
            inode.type = ((i % 2) ==  0) ? 'd' : 'r';

            fwrite(&inode, sizeof(INode), 1, archive);
        }

        fclose(archive);
    } else
        printf("Error opening file\n");
}

void format(char comand[]){
    for (unsigned int i = 0; i < strlen(comand); i++)
        comand[i] = tolower(comand[i]);
}

void format_directory(char directory[]){
    unsigned int i = strlen(directory) - 1;
    
    while (directory[i] != '\\' && i > 0)
        i--;
    
    directory[i] = '\0';
}

void bash(){
    char comand[10], argument[25], entry[50], directory[100];
    
    directory[0] = '\0';

    while (strcmp(comand, "exit")) {
        printf("c:\\%s>", directory);

        fgets(entry, 50, stdin);
        sscanf(entry, "%s %s", comand, argument);

        format(comand);

        if (!strcmp(comand, "mkdir")) {
            
        } else if (!strcmp(comand, "cd")) {
            if (!strcmp(argument, ".."))
                format_directory(directory);
            else {
                if (directory[0] != '\0')
                    directory[strlen(directory)] = '\\';
        
                strcat(directory, argument);
            }
        } else if (!strcmp(comand, "ls")) {
            
        } else if (!strcmp(comand, "cat")) {
            
        } else if (!strcmp(comand, "rm")) {
            
        } else if (!strcmp(comand, "rmdir")) {
            
        } else if (!strcmp(comand, "mv")) {
            
        } else if (!strcmp(comand, "run")) {
            
        } else if (strcmp(comand, "exit")) {
            printf("%s comando nao reconhecido. \n", comand);
        } 
        
    }
    
}

int main(){

    FreeBlock *freeBlock = NULL;

    // generateInodes();
    // generateBlocks(freeBlock);
    bash();


    return 0;
}