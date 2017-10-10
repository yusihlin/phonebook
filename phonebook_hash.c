#include <stdlib.h>
#include <string.h>
#include "phonebook_hash.h"

entry **newlink=NULL;
entry **newlinkHead=NULL;

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

entry *findName(char lastName[], entry *pHead)
{
    unsigned int n = BKDRHash(lastName) % TABLE_SIZE; 
    pHead = *(newlinkHead+n);
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if(newlink == NULL) {
        newlink = (entry **)malloc(TABLE_SIZE*sizeof(entry *));
        newlinkHead = (entry **)malloc(TABLE_SIZE*sizeof(entry *));
    }
    unsigned int n = BKDRHash(lastName) % TABLE_SIZE;
    e = *(newlink+n);
    if(*(newlinkHead+n) == NULL) {
        e = (entry *) malloc(sizeof(entry));
        *(newlinkHead+n) = e;
    }
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    *(newlink+n) = e;
    return e;
}


