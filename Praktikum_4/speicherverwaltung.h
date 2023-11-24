#ifndef SPEICHERVERWALTUNG_H
#define SPEICHERVERWALTUNG_H

#include <stddef.h>

#define MEM_POOL_SIZE 2000
#define MAGIC_INT 0xacdcacdc

typedef struct memblock {
    size_t size;
    struct memblock *next;
    unsigned short id;
} memblock;

extern char mempool[MEM_POOL_SIZE];
extern memblock *freemem;

int cm_init(void);
void *cm_malloc(size_t size);
void cm_free(void *ptr);

#endif 
