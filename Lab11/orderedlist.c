#include <assert.h>
#include "orderedlist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    title val;
    link next;
} node;

static link newNode(title val, link next) {
    link x;

    x = (link) malloc(sizeof(node));
    if(x != NULL) {
        x->val = val;
        x->next = next;
    }
    return x;
}
link LISTdeleteHead(link head) {
    link t;

    t = head;
    if(head != NULL) {
        head = head->next;
        free(t);
    }
    return head;
}
link LISTdeleteKey(link head, char *k) {
    link x, p;

    if(head != NULL) {
        for(x = head, p = NULL; x != NULL; p = x, x = x->next) {
            if(TITLEeq(TITLEget(x->val), k) != FALSE) {
                if(x == head) {
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
link LISTdeleteKeyRecursive(link x, char *k) {
    link t;

    if(x != NULL) {
        if(TITLEeq(TITLEget(x->val), k) != FALSE) {
            t = x->next;
            free(x);
            return t;
        }
        x->next = LISTdeleteKeyRecursive(x->next, k);
    }
    return x;
}
title LISTextractHeadPointer(link *head) {
    link t;
    title tmp;

    t = *head;
    if(t == NULL) {
        return TITLEsetvoid();
    }
    tmp = t->val;
    *head = t->next;
    free(t);
    return tmp;
}
title LISTextractKeyPointer(link *head, char *k) {
    link *x, t;
    title i;

    i = TITLEsetvoid();
    for(x = head; *x != NULL; x = &((*x)->next)) {
        if(TITLEeq(TITLEget((*x)->val),k) != FALSE) {
            t = *x;
            *x = (*x)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}
void LISTfree(link *head) {
    link x, p;

    for(x = *head, p = NULL; x != NULL; x = p) {
        p = x->next;
        TITLEfree(x->val);
        free(x);
    }
}
void LISTinsertHeadPointer(link *head, title val) {
    *head = newNode(val, *head);
}
void LISTinsertTailFast(link *head, link *tail, title val) {
    if(*head == NULL) {
        *head = *tail = newNode(val, NULL);
    } else {
        (*tail)->next = newNode(val, NULL);
        *tail = (*tail)->next;
    }
}
link LISTreverse(link x, link *tail) {
    link y;

    if(x->next->next != NULL) {
        y = LISTreverse(x->next, tail);
        (*tail)->next = y;
        *tail = (*tail)->next;
    }
    return x;
}
title LISTsearch(link head, char *k) {
    link x;

    for(x = head; x != NULL; x = x->next) {
        if(TITLEeq(TITLEget(x->val), k) != FALSE) {
            return x->val;
        }
    }
    return TITLEsetvoid();
}
void LISTshow(link head) {
    link x;

    for(x = head; x != NULL; x = x->next) {
        TITLEshow(x->val);
    }
}
void LISTsort(link *head) {
    link u, t, x;

    for(t = (*head)->next, (*head)->next = NULL; t != NULL; t = u) {
        u = t->next;
        if(TITLEgreater(TITLEget((*head)->val), TITLEget(t->val)) != FALSE) {
            t->next = *head;
            *head = t;
        } else {
            for(x = *head; x->next != NULL; x = x->next) {
                if(TITLEgreater(TITLEget(x->next->val), TITLEget(t->val)) != FALSE) {
                    break;
                }
            }
            t->next = x->next;
            x->next = t;
        }
    }
}
link SortLISTDelete(link head, char *k) {
    link x, p;

    if(head != NULL) {
        for(x = head, p = NULL; x != NULL && TITLEcompare(k, TITLEget(x->val)) >= 0; p = x, x = x->next) {
            if(TITLEeq(TITLEget(x->val), k) != FALSE) {
                if(x == head) {
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
link SortLISTInsert(link head, title val) {
    link x, p;
    char *k;

    k = TITLEget(val);
    if(head == NULL || TITLEgreater(TITLEget(head->val), k) != FALSE) {
        return newNode(val, head);
    }
    for(x = head->next, p = head; x != NULL && TITLEgreater(k, TITLEget(x->val) != FALSE); p = x, x = x->next);
    p->next = newNode(val, x);
    return head;
}
title SortLISTSearch(link head, char *k) {
    link x;

    for(x = head; x != NULL && TITLEcompare(k, TITLEget(x->val)) >= 0; x = x->next) {
        if(TITLEeq(TITLEget(x->val), k) != FALSE) {
            return x->val;
        }
    }
    return TITLEsetvoid();
}