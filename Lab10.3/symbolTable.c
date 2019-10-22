#include <assert.h>
#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _st {
    Item *vector;
    int length;
} st;                                                                                                                   // the symbol table

static void merge(Item *vector, Item *auxiliary, int l, int r, int q) {
    int i;                                                                                                              // the index of the left subvector
    int j;                                                                                                              // the index of the right subvector
    int k;                                                                                                              // the index

    for(i = k = l, j = q + 1; k <= r; k++) {                                                                            // cycling on the vector
        if(i > q) {                                                                                                     // if that checks if the left subvector is empty
            auxiliary[k] = vector[j++];
        } else if(j > r) {                                                                                              // if that checks if the right subvector is empty
            auxiliary[k] = vector[i++];
        } else if (KEYcompare(KEYget(vector[i]), KEYget(vector[j])) <= 0) {                                             // switch that checks if the left element is less, equal or greater then the right element
            auxiliary[k] = vector[i++];
        } else {
            auxiliary[k] = vector[j++];
        }
    }
    for(k = l; k <= r; k++) {                                                                                           // cycling on the vector
        vector[k] = auxiliary[k];
    }
}
static void mergeSortR(Item *vector, Item *auxiliary, int l, int r) {
    int q;                                                                                                              // the index of the middle element

    if(r <= l) {                                                                                                        // if that checks the terminal case
        return;
    }
    q = (l + r) / 2;
    mergeSortR(vector, auxiliary, l, q);
    mergeSortR(vector, auxiliary, q + 1, r);
    merge(vector, auxiliary, l, r, q);
}
static int linearSearchByName(ST symbolTable, Key name) {
    int i;                                                                                                              // the index

    for(i = 0; i < symbolTable->length ; i++) {                                                                         // cycle on the vector
        if(KEYcompare(KEYget(symbolTable->vector[i]), name) == 0) {                                                     // if that checks if the i-th element of the vector is equal to the searched element
            return i;
        }
    }
    return -1;
}
void STfree(ST symbolTable) {
    int i;                                                                                                              // the index

    for (i = 0; i < symbolTable->length; ++i) {                                                                         // cycle on the vector
        ITEMfree(symbolTable->vector[i]);
    }
    free(symbolTable->vector);
    free(symbolTable);
}
ST STinit(int length) {
    ST symbolTable;                                                                                                     // the symbol table

    symbolTable = (ST) malloc(sizeof(st));
    assert(symbolTable != NULL);
    symbolTable->length = 0;
    symbolTable->vector = (Item *) malloc(length * sizeof(Item));
    assert(symbolTable->vector != NULL);
    return symbolTable;
}
int STinsert(ST symbolTable, Key computerId, Key networkId) {
    int i;                                                                                                              // the index

    i = -1;
    if(symbolTable->length != 0) {
        i = linearSearchByName(symbolTable, computerId);
    }
    if(i == -1) {                                                                                                       // if that checks if the vertex is already insert
        symbolTable->vector[symbolTable->length++] = ITEMinit(computerId, networkId);
        return symbolTable->length - 1;
    }
    return -1;
}
int STlength(ST symbolTable) {
    return symbolTable->length;
}
void STorder(ST symbolTable) {
    int l, r;                                                                                                           // the extreme of the vector
    Item *auxiliary;                                                                                                    // the auxiliary vector

    l = 0;
    r = symbolTable->length - 1;
    auxiliary = (Item *) malloc(symbolTable->length * sizeof(Item));
    assert(auxiliary != NULL);
    mergeSortR(symbolTable->vector, auxiliary, l, r);
}
void STrealloc(ST symbolTable) {
    symbolTable->vector = (Item *) realloc(symbolTable->vector, symbolTable->length * sizeof(Item));
    assert(symbolTable->vector != NULL);
}
Key STsearchByIndex(ST symbolTable, int i) {
    return KEYget(symbolTable->vector[i]);
}
int STsearchByName(ST symbolTable, Key name) {
    int l, r;                                                                                                           // the extreme of the vector
    int m;                                                                                                              // the index of the middle element

    for(l = 0, r = symbolTable->length - 1; l <= r;) {
        m = l + (r - l) / 2;
        if(KEYcompare(KEYget(symbolTable->vector[m]), name) == 0) {
            return m;
        } else if(KEYcompare(KEYget(symbolTable->vector[m]), name) < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}