/* This file is lecture notes from CS 3650, Fall 2018 */
/* Author: Nat Tuck */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "svec.h"

svec*
make_svec()
{
    svec* sv = malloc(sizeof(svec));
    sv->capacity = 2;
    sv->data = malloc(sv->capacity * sizeof(char*));
    sv->size = 0;
    // TODO: correctly allocate and initialize data structure
    memset(sv->data,0,2*sizeof(char*));
    return sv;
}

void
free_svec(svec* sv)
{
    // TODO: free all allocated data
    for(long ii=0;ii<sv->size;ii++){
        free(sv->data[ii]);
    }
    free(sv->data);
    free(sv);
}

char*
svec_get(svec* sv, int ii)
{
    assert(ii >= 0 && ii < sv->size);
    return sv->data[ii];
}

void
svec_put(svec* sv, int ii, char* item)
{
    assert(ii >= 0 && ii < sv->size);
    sv->data[ii] = strdup(item);
    // TODO: insert item into slot ii
    // Consider ownership of string in collection.
}

void
svec_push_back(svec* sv, char* item)
{
    // TODO: expand vector if backing erray
    // is not big enough
    if(sv->capacity == sv->size){
        char** data = realloc(sv->data, sizeof(char*) * sv->capacity * 2);
        if(data){
            sv->data = data;
            sv->capacity = sv->capacity * 2;
        }
    }
    svec_put(sv, sv->size++, item);
    //sv->data[sv->size] = strdup(item);
    //sv->data[sv->size++] = item;
}

void
svec_swap(svec* sv, int ii, int jj)
{
    // TODO: Swap the items in slots ii and jj
    char* temp = sv->data[ii];
    sv->data[ii] = sv->data[jj];
    sv->data[jj] = temp;
}
