#include <assert.h>
#include "list.h"
#include <stdlib.h>

typedef struct _node {
    int *diagonal, diagonalLength;
    link next;
} node;                                                                                                                 // the list

static int *vectorDup(int *diagonal) {
    int *x;                                                                                                             // the vector
    int i;                                                                                                              // the index

    x = (int *) malloc(NUMBEROFELEMENT * sizeof(int));
    assert(x != NULL);
    for (i = 0; i < NUMBEROFELEMENT; ++i) {                                                                            // cycle on the vector
        x[i] = diagonal[i];
    }
    return x;
}
static link newNode(int *diagonal, int diagonalLength, link next) {
    link x;                                                                                                             // the auxiliary node

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                                                                                                     // if that checks if the node is allocated
        x->diagonal = vectorDup(diagonal);
        x->diagonalLength = diagonalLength;
        x->next = next;
    }
    return x;
}
int *LISTdiagonal(link x) {
    return x->diagonal;
}
int LISTdiagonalLength(link x) {
    return x->diagonalLength;
}
void LISTfree(link *head) {
    link x, p;                                                                                                          // the auxiliary nodes

    for(x = *head, p = NULL; x != NULL; x = p) {                                                                        // cycle on the list
        p = x->next;
        free(x->diagonal);
        free(x);
    }
}
void LISTinsertHeadPointers(link *head, int *diagonal, int diagonalLength) {
    *head = newNode(diagonal, diagonalLength, *head);
}
link LISTnext(link x) {
    return x->next;
}