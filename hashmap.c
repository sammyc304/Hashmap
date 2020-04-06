
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// TODO: sudo apt install libbsd-dev
// This provides strlcpy
// See "man strlcpy"
#include <bsd/string.h>
#include <string.h>

#include "hashmap.h"

int
hash(char* key)
{
    // TODO: Produce an appropriate hash value.
    int ret_val = 0;
    for(long ii=0;ii<strlen(key);++ii){
        ret_val = ret_val * 67 + key[ii];
    }
    return ret_val;
}

hashmap*
make_hashmap_presize(int nn)
{
    hashmap* hh = calloc(1, sizeof(hashmap));
    // TODO: Allocate and initialize a hashmap with capacity 'nn'.
    // Double check "man calloc" to see what that function does.
    hh->size = 0;
    hh->capacity = nn;
    hh->data = calloc(hh->capacity, sizeof(hashmap_pair));
    return hh;
}

hashmap*
make_hashmap()
{
    return make_hashmap_presize(4);
}

void
free_hashmap(hashmap* hh)
{
    // TODO: Free all allocated data.
    free(hh->data);
    free(hh);
}

int
hashmap_has(hashmap* hh, char* kk)
{
    return hashmap_get(hh, kk) != -1;
}

int
hashmap_get(hashmap* hh, char* kk)
{
    // TODO: Return the value associated with the
    // key kk.
    // Note: return -1 for key not found.
    long index = hash(kk) % hh->capacity;
    for(long jj = 0;jj<hh->capacity;++jj){
        int ii = (index+jj)%hh->capacity;
        if(!hh->data[ii].used){
            return -1;
        }
        if(strcmp(hh->data[ii].key,kk) == 0){
            return hh->data[ii].val;
        }
    }
    return -1;
}

void
hashmap_grow(hashmap* hh){
    if(hh->size >= hh->capacity/2){
        long nn = hh->capacity;
        hashmap_pair* data = hh->data;
        hh->capacity = 2*nn;
        hh->data = calloc(hh->capacity, sizeof(hashmap_pair));
        hh->size = 0;
        for(long ii=0;ii<nn;++ii){
            if(data[ii].used){
                hashmap_put(hh, data[ii].key, data[ii].val);
            }
        }
        free(data);
    }
    return;
}

void
hashmap_put(hashmap* hh, char* kk, int vv)
{
    // TODO: Insert the value 'vv' into the hashmap
    // for the key 'kk', replacing any existing value
    // for that key.
    hashmap_grow(hh);
    long index = hash(kk) % hh->capacity;
    for(long ii = 0;ii<hh->capacity;++ii){
        int jj = (index + ii)%hh->capacity;
        if(strcmp(hh->data[jj].key,kk) == 0){
            hh->data[jj].val = vv;
            hh->data[jj].tomb = false;
            return;
        }
        if(!hh->data[jj].used){
            strcpy(hh->data[jj].key,kk);
            hh->data[jj].val = vv;
            hh->data[jj].used = true;
            hh->size++;
            return;
        }
    }
    return;
}

void
hashmap_del(hashmap* hh, char* kk)
{
    // TODO: Remove any value associated with
    // this key in the map.
    long index = hash(kk) % hh->capacity;
    for(long ii = 0;ii<hh->capacity;++ii){
        int jj = (index + ii)%hh->capacity;
        if(strcmp(hh->data[jj].key,kk) == 0){
            hh->data[jj].tomb = true;
            hh->size--;
            return;
        }
    }
    return;
}

hashmap_pair
hashmap_get_pair(hashmap* hh, int ii)
{
    // TODO: Get the {k,v} pair stored in index 'ii'.
    return hh->data[ii];
}

void
hashmap_dump(hashmap* hh)
{
    printf("== hashmap dump ==\n");
    // TODO: Print out all the keys and values currently
    // in the map, in storage order. Useful for debugging.
    puts("Index    Key    Value    Used    Tomb\n");
    for(long ii=0;ii<hh->capacity;ii++){
        hashmap_pair temp = hashmap_get_pair(hh,ii);
        printf("%ld        %s      %d        %d       %d\n",ii,temp.key,temp.val,temp.used,temp.tomb);
    }
    return;
}
