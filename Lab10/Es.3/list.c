#include "list.h"
#include <stdlib.h>

#define FALSE 0

typedef struct _node {
    int vertexW, weight;
    link next;
} node;                                                                                                                 // the node of the list

static link newNode(int vertexW, int weight, link next) {
    link x;                                                                                                             // the auxiliary node

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                                                                                                     // if that checks if the node is allocated
        x->vertexW = vertexW;
        x->weight = weight;
        x->next = next;
    }
    return x;
}
link LISTdelete(link head, int vertex) {
    link x, p;                                                                                                          // the auxiliary nodes

    if(head != NULL) {                                                                                                  // if that checks if the list is empty
        for(x = head, p = NULL; x != NULL; p = x, x = x->next) {                                                        // cycle on the list
            if(x->vertexW == vertex) {                                                                                  // if that checks if the node is correct
                if(x == head) {                                                                                         // if that checks if the node is the head of the list
                    head = x->next;
                } else {
                    p->next = x->next;
                }
                free(x);
                break;
            }
        }
    }
    return head;
}
void LISTfree(link *head) {
    link x, p;                                                                                                          // the auxiliary nodes

    for(x = *head, p = NULL; x != NULL; x = p) {                                                                        // cycle on the list
        p = x->next;
        free(x);
    }
}
void LISTinsertHeadPointer(link *head, int vertexW, int weight) {
    *head = newNode(vertexW, weight, *head);
}
int LISTsearch(link head, int vertexW) {
    link x;                                                                                                             // the auxiliary node

    for(x = head; x != NULL; x = x->next) {                                                                             // cycle on the list
        if(x->vertexW == vertexW) {                                                                                     // if that checks if there are the edge
            return 1;
        }
    }
    return FALSE;
}