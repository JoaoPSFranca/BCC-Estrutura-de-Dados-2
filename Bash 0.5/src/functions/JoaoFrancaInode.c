#include <conio.h>
#include "../lib/JoaoFrancaInode.h"
#include "../lib/JoaoFrancaDirectory.h"

void generateInodes(FreeINode **freeInodes) {
    FILE *archive;
    FreeINode *aux = *freeInodes;
    
    archive = fopen("src/Resources/INodes.dat", "wb");
    
    if(archive != NULL){
        for (unsigned int i = 0; i < MAX_I_NODE; i++){
            INode *inode = malloc(sizeof(INode));

            inode->id = i;
            inode->type = ((i % 2) ==  0) ? 'd' : 'r';
            inode->status = 0;
            inode->size = 0;
            inode->block_count = 0;

            fwrite(inode, sizeof(INode), 1, archive);

            aux->inode = inode; 

            if (i < MAX_I_NODE - 1) {
                aux->next = malloc(sizeof(FreeINode));
                aux = aux->next;
            } else{
                aux->next = NULL;
            }
        }

        fclose(archive);
    } else
        printf("Error opening INode file. \n");
}

INode *verifyINodeFree(FreeINode **freeInodes, char type) {
    FreeINode *aux = *freeInodes;
    int flag = 1;

    while (flag && aux != NULL){
        if (aux->inode->type == type && aux->inode->status == 0)
            flag = 0;
        else
            aux = aux->next;
    }

    if (aux == NULL)
        return NULL;
    
    return aux->inode;
}

void alterINodeDat(INode *inode) {
    FILE *archive;
    archive = fopen("src/Resources/INodes.dat", "rb+");

    if (archive != NULL) {
        INode aux;
        int flag = 1;
        int resp = 1;

        while (flag && resp) {
            resp = fread(&aux, sizeof(INode), 1, archive);

            if (aux.id == inode->id) {
                fseek(archive, -sizeof(INode), SEEK_CUR);
                fwrite(inode, sizeof(INode), 1, archive);
                flag = 0;   
            }
        }

        if (flag == 1)
            printf("Error: INode not found. ");
        
        fclose(archive);
    } else
        printf("Error opening INode file. \n");
}

void enterINodeFree(FreeINode **freeINode, INode *inode) {
    inode->status = 0;

    FreeINode *aux = *freeINode;

    while (aux != NULL)
        aux = aux->next;
    
    FreeINode *newFreeINode = malloc(sizeof(FreeINode));

    newFreeINode->inode = inode;
    newFreeINode->next = NULL;
    aux = newFreeINode;

    alterINodeDat(inode);
}

void removeINodeFree(FreeINode **freeInodes, INode *inode) { 
    if ((*freeInodes)->inode->id == inode->id) {
        (*freeInodes) = (*freeInodes)->next;
    } else {
        FreeINode *aux = *freeInodes;
        FreeINode *aux2 = NULL;
        int flag = 1;

        while (flag && aux != NULL){
            if(aux->inode->id == inode->id)
                flag = 0;
            else {
                aux2 = aux;
                aux = aux->next;
            }
        }

        if (aux != NULL){
            if (aux2 == NULL)
                freeInodes = &aux;    
            else
                aux2->next = aux->next;
            
            aux->inode->status = 1;

            inode->size = inode->block_count * BLOCK_SIZE;
            alterINodeDat(aux->inode);
        }
        else
            printf("INode not found. ");
    }
}

int readINodeDat(FreeINode **fi) {
    FILE *archive;
    archive = fopen("src/Resources/INodes.dat", "rb");

    if (archive != NULL) {
        *fi = NULL;
        FreeINode *aux = NULL;
        int resp = 1;
        
        while(resp){
            INode *inode = malloc(sizeof(INode));
            resp = fread(inode, sizeof(INode), 1, archive);

            if (inode->status == 0 && resp) {
                FreeINode *newNode = malloc(sizeof(FreeINode));
                newNode->inode = inode;
                newNode->next = NULL;

                if (*fi == NULL) 
                    *fi = newNode;
                else
                    aux->next = newNode;

                aux = newNode;
            } else 
                free(inode);
        }
        
        if (aux != NULL)
            aux->next = NULL;

        fclose(archive);
        return 1;   
    } else {
        printf("Error opening INode file to read. \n");
        return 0;
    }
}

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
            } else {
                printf("%c", entry);
                block->data[i++] = entry;
            }
            

            if (i == (BLOCK_SIZE - 1))
                full = 1;
        } 
    }

    block->data[i] = "";
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

    printf("\n");
    
    for (i = 0; i < inode->block_count; i++) {
        Block block = inode->blocks[i];

        for (j = 0; j < strlen(block.data); j++)
            printf("%c", block.data[j]);
    }

    printf("\n");
}
