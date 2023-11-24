#include "speicherverwaltung.h"
#include <stdio.h>
#define true 1
#define false 0
char mempool[MEM_POOL_SIZE];
memblock *freemem = NULL;

int cm_init(void){
 static int initialisiert = false;
 
 if(initialisiert == true ){
    return 0;
 }
 
freemem = (memblock*) mempool;
if (!freemem) {
        perror("beim Ausführen der Funktion trat ein Fehler auf");
        return -1;
    }
freemem->size = MEM_Pool_SIZE - sizeof(memblock);
freemem->next = NULL;
freemem->id = 0;

initialisiert = true;
return 1;
}

void *cm_malloc(size_t size){
  if(size == 0){
    return NULL;
  }

  memblock *current = freemem;
  memblock *previous= NULL;

  while(current != NULL){
        
        if(current->size >= size){

            if(current->size >= size + sizeof(memblock)){

                memblock *newBlock = (memblock*)(char*)current +sizeof(memblock)+size;
                newBlock->size = current->size - size - sizeof(memblock);
                newBlock->next = current->next;
                newBlock->id = 0;

                current->size = size;
                current->next = (memblock*)MAGIC_INT;

                if(previous){
                    previous->next = newBlock;
                }
                else{
                    freemem = newBlock;
                }
            }
            else{
                if(previous){
                    previous->next = current->next;
                }
                else{
                    freemem = current->next;
                }
                current->next = (memblock*)MAGIC_INT;
            }
            return (char*)current + sizeof(memblock);
        }
        previous = current;
        current = current->next;
  }
return NULL;
}

void vm_free(void *ptr){
    if (ptr == NULL) {
        return; 
    }
    memblock *block = (memblock *)((char *)ptr - sizeof(memblock));

    if (block->next != (memblock *)MAGIC_INT) {
        return; 
    }
    block->next = freemem;
    block->id = 0; 
    freemem = block;
}