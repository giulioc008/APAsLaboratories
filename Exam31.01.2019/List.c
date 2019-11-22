#include <assert.h>
#include "List.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  _node node, *link;                                                                                      // the node of the list
struct _node {
    int n;
    link next;
};
typedef struct _list {
    link head;
} lista;                                                                                                                // the list

static link newNode(int n, link next) {
    link x;                                                                                                             // the new node

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                                                                                                     // if that checks if the node is allocated
        x->n = n;
        x->next = next;
    }
    return x;
}
list LISTinit() {
    list List;                                                                                                          // the new list

    List = (list) calloc(1, sizeof(lista));
    assert(List != NULL);
    return List;
}
void LISTinsertTail(list List, int val) {
    link x;                                                                                                             // the auxiliary node

    if(List->head == NULL) {                                                                                            // if that checks if the list is empty
        List->head = newNode(val, NULL);
        return;
    }
    for(x = List->head; x->next != NULL; x = x->next);                                                                        // cycle on the list
    x->next = newNode(val, NULL);
}
int LISTextractHead(list List) {
    link x;                                                                                                             // the auxiliary node
    int val;                                                                                                            // the auxiliary variables

    if(List->head == NULL) {                                                                                            // if that checks if the list is empty
        return -1;
    }
    x = List->head;
    List->head = x->next;
    val = x->n;
    free(x);
    return val;
}
void LISTfree(list List) {
    link x, p;                                                                                                          // the auxiliary nodes

    for(x = List->head, p = NULL; x != NULL; x = p) {                                                                   // cycle on the list
        p = x->next;
        free(x);
    }
}
void LISTshow(list List) {
    link x;                                                                                                             // the new node

    fprintf(stdout, "\t");
    for(x = List->head; x != NULL; x = x->next) {                                                                       // cycle on the list
        fprintf(stdout, "%d ", x->n);
    }
    fprintf(stdout, "\n");
}
void splice(list L1, list L2, int start, int num) {
    link x, y, z;                                                                                                       // the auxiliary nodes
    int i;                                                                                                              // the index
    int n;                                                                                                              // the index

    y = NULL;
    for(i = 0, x = L1->head; i != start && x != NULL; i++, x = x->next);                                                // cycle that determines where insert the sublist
    if(x == NULL && i != start) {                                                                                       // if that checks if the request is legal (start less or equal to the length of the list)
        fprintf(stdout, "\tERROR !!\n");
        return;
    }
    for(i = 0; i < num && L2->head != NULL; i++) {                                                                      // cycle that extracts from the head of the list L2 and inserts it in the sublist y
        z = y;
        n = LISTextractHead(L2);
        if(n == -1) {                                                                                                   // if that checks if the list L2 is empty
            break;
        }
        y = newNode(n, z);
    }
    z = x->next;
    x->next = y;
    for(; y->next != NULL; y = y->next);                                                                                // cycle that search the end of the sublist
    y->next = z;
}