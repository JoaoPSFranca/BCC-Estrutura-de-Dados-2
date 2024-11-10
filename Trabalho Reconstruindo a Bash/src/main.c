#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../lib/Block.h"
#include "../lib/Inode.h"
#include "../lib/Directory.h"

#define MAX_I_NODE 32
#define MAX_BLOCKS (MAX_I_NODE*15)
#define BLOCK_SIZE 4096
#define MAX_FILENAME 256

void generateBlocks(FreeBlock *fb){
    fb = malloc(sizeof(FreeBlock));
    FreeBlock *aux = fb;

    for (unsigned int i = 0; i < MAX_BLOCKS; i++){
        FILE *archive;
        char name_archive[70];

        snprintf(name_archive, sizeof(name_archive), "../Blocks/%02d.dat", i+1);

        archive = fopen(name_archive, "wb");

        if(archive != NULL){
            Block *block = malloc(sizeof(Block));

            block->address = i;
            block->status = 0;

            fwrite(block, sizeof(Block), 1, archive);
            
            fclose(archive);

            FreeBlock *aux2 = malloc(sizeof(FreeBlock)); 

            aux->block = block;
            aux->next = aux2;

            aux = aux2;
        } else
            printf("Error opening file\n");
    }
}

void generateInodes(){
    FILE *archive;
    
    archive = fopen("../Resources/INodes.dat", "wb");
    
    if(archive != NULL){
        for (unsigned int i = 0; i < MAX_I_NODE; i++){
            INode *inode = malloc(sizeof(INode));

            inode->id = i;
            inode->type = ((i % 2) ==  0) ? 'd' : 'r';

            fwrite(inode, sizeof(INode), 1, archive);
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
            printf("%s comando nao reconhecido. ", comand);
        } 
        
    }
    
}

int main(){

    // FreeBlock *freeBlock = NULL;

    // generateInodes();
    // generateBlocks(freeBlock);
    bash();


    return 0;
}