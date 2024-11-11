#include "../lib/inode.h"

void generateInodes(FreeINode **freeInodes){
    FILE *archive;
    FreeINode *aux = *freeInodes;
    
    archive = fopen("src/Resources/INodes.dat", "wb");
    
    if(archive != NULL){
        for (unsigned int i = 0; i < MAX_I_NODE; i++){
            INode *inode = malloc(sizeof(INode));

            inode->id = i;
            inode->type = ((i % 2) ==  0) ? 'd' : 'r';

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
        printf("Error opening file\n");
}

INode *verifyINodeFree_Directory(FreeINode **freeInodes){
    FreeINode *aux = *freeInodes;

    while (aux->inode->type != 'd' && aux != NULL)
        aux = aux->next;
    
    if (aux == NULL)
        return NULL;
    
    return aux->inode;
}

void removeINodeFree(FreeINode **freeInodes, INode *inode){
    if ((*freeInodes)->inode->id == inode->id) {
        (*freeInodes) = (*freeInodes)->next;
    } else {
        FreeINode *aux = *freeInodes;
        FreeINode *aux2 = NULL;
    
        while (aux->inode->id != inode->id && aux != NULL){
            aux2 = aux;
            aux = aux->next;
        }

        if (aux != NULL)
            aux2->next = aux->next;
        else
            printf("INode nao encontrado. ");
    }
}

