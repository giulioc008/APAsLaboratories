#include <assert.h>
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

#define PREORDER 1
#define INORDER 2
#define POSTORDER 3

typedef struct _nodeB BSTnode, *BSTlink;                                                                                // the node of the bst
struct _nodeB {
    int N;
    dailyQuotation item;
    BSTlink parent, left, right;
};
typedef struct _bst {
    int N;
    BSTlink root;
} bst;                                                                                                                  // the bst

static BSTlink leftRotation(BSTlink h) {
    BSTlink x;                                                                                                            // the auxiliary node

    x = h->right;
    h->right = x->left;
    x->left->parent = h;
    x->left = h;
    x->parent = h->parent;
    h->parent = x;
    x->N = h->N;
    h->N = h->left->N + h->right->N + 1;
    return x;
}
static BSTlink newNode(dailyQuotation item, BSTlink parent, BSTlink left, BSTlink right, int N) {
    BSTlink x;                                                                                                            // the auxiliary node

    x = (BSTlink) malloc(sizeof(BSTnode));
    if(x != NULL) {                                                                                                     // if that checks if the node is allocated
        x->item = item;
        x->parent = parent;
        x->left = left;
        x->right = right;
        x->N = N;
    }
    return x;
}
static BSTlink rightRotation(BSTlink h) {
    BSTlink x;                                                                                                            // the auxiliary node

    x = h->left;
    h->left = x->right;
    x->right->parent = h;
    x->right = h;
    x->parent = h->parent;
    h->parent = x;
    x->N = h->N;
    h->N = h->right->N + h->left->N + 1;
    return x;
}
static BSTlink insertRoot(BSTlink h, dailyQuotation x) {
    if (h == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return newNode(x, NULL, NULL, NULL, 1);
    }
    if (KEYless(KEYget(x), KEYget(h->item)) != FALSE) {                                                                 // if that checks if x is less then h
        h->left = insertRoot(h->left, x);
        h = rightRotation(h);
    } else {
        h->right = insertRoot(h->right, x);
        h = leftRotation(h);
    }
    h->N++;
    return h;
}
static BSTlink partitionRecursive(BSTlink h, int k) {
    int x;                                                                                                              // the auxiliary variable

    if (h != NULL) {                                                                                                    // if that checks if h exists
        x = h->left == NULL ? 0 : h->left->N;
        if (x > k) {                                                                                                    // if that checks if x is greater then k
            h->left = partitionRecursive(h->left, k);
            h = rightRotation(h);
        }
        if (x < k) {                                                                                                    // if that checks if x is less then k
            h->right = partitionRecursive(h->right, k - x - 1);
            h = leftRotation(h);
        }
    }
    return h;
}
static BSTlink joinLeftRight(BSTlink a, BSTlink b) {
    if (b == NULL) {                                                                                                    // if that checks the terminal case (b is a leaf)
        return a;
    }
    b = partitionRecursive(b, 0);
    b->left = a;
    a->parent = b;
    b->N = a->N + b->right->N + 1;
    return b;
}
static BSTlink deleteRecursive(BSTlink x, Date k) {
    BSTlink y, p;                                                                                                       // the auxiliary nodes

    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return NULL;
    }
    if (KEYless(k, KEYget(x->item)) != FALSE) {                                                                         // if that checks if k is less then h
        x->left = deleteRecursive(x->left, k);
    } else if (KEYgreater(k, KEYget(x->item)) != FALSE) {                                                               // if that checks if k is greater then h
        x->right = deleteRecursive(x->right, k);
    }
    x->N--;
    if (KEYeq(k, KEYget(x->item)) != FALSE) {                                                                           // if that checks if k is equal to h
        y = x;
        p = x->parent;
        x = joinLeftRight(x->left, x->right);
        x->parent = p;
        free(y);
    }
    return x;
}
static BSTlink insertRecursive(BSTlink h, dailyQuotation x) {
    if (h == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return newNode(x, NULL, NULL, NULL, 1);
    }
    if (KEYless(KEYget(x), KEYget(h->item)) != FALSE) {                                                                 // if that checks if x is less then h
        h->left = insertRecursive(h->left, x);
        h->left->parent = h;
    } else {
        h->right = insertRecursive(h->right, x);
        h->right->parent = h;
    }
    h->N++;
    return h;
}
static dailyQuotation maximumRecursive(BSTlink x) {
    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return ITEMsetvoid();
    }
    if (x->right == NULL) {                                                                                             // if that checks the semi terminal case (h->right is a leaf)
        return x->item;
    }
    return maximumRecursive(x->right);
}
static dailyQuotation minimumRecursive(BSTlink x) {
    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return ITEMsetvoid();
    }
    if (x->left == NULL) {                                                                                              // if that checks then semi terminal case (h->right is a leaf)
        return x->item;
    }
    return minimumRecursive(x->left);
}
static dailyQuotation searchPrevious(BSTlink x, Date k) {
    BSTlink p;                                                                                                            // the previous node

    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return ITEMsetvoid();
    }
    if (KEYeq(k, KEYget(x->item)) != FALSE) {                                                                           // if that checks if k is equal to h
        if (x->left != NULL) {                                                                                          // if that checks the semi terminal case (h->left is a leaf)
            return maximumRecursive(x->left);
        } else {
            for (p = x->parent; p != NULL && x == p->left; x = p, p = p->parent);
            return p->item;
        }
    }
    if (KEYless(k, KEYget(x->item)) != FALSE) {                                                                         // if that checks if k is less then h
        return searchPrevious(x->left, k);
    }
    return searchPrevious(x->right, k);
}
static dailyQuotation searchRecursive(BSTlink x, Date k) {
    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return ITEMsetvoid();
    }
    if (KEYeq(k, KEYget(x->item)) != FALSE) {                                                                           // if that checks if k is equal to h
        return x->item;
    }
    if (KEYless(k, KEYget(x->item)) != FALSE) {                                                                         // if that checks if k is less then h
        return searchRecursive(x->left, k);
    } else {
        return searchRecursive(x->right, k);
    }
}
static dailyQuotation searchFollowing(BSTlink x, Date k) {
    BSTlink p;                                                                                                          // the previous node

    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return ITEMsetvoid();
    }
    if (KEYeq(k, KEYget(x->item)) != FALSE) {                                                                           // if that checks if k is equal to h
        if (x->right != NULL) {                                                                                         // if that checks the semi terminal case (h->right is a leaf)
            return minimumRecursive(x->right);
        } else {
            for (p = x->parent; p != NULL && x == p->right; x = p, p = p->parent);
            return p->item;
        }
    }
    if (KEYless(k, KEYget(x->item)) != FALSE) {                                                                         // if that checks if k is less then h
        return searchFollowing(x->left, k);
    }
    return searchFollowing(x->right, k);
}
static dailyQuotation selectRecursive(BSTlink h, int k) {
    int x;                                                                                                              // the auxiliary variable

    if (h == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return ITEMsetvoid();
    }
    if (h->left == NULL) {                                                                                              // if that checks the semi terminal case (->left is a leaf)
        x = 0;
    } else {
        x = h->left->N;
    }
    if (x > k) {                                                                                                        // if that checks if x is greater then k
        return selectRecursive(h->left, k);
    } else if (x < k) {                                                                                                 // if that checks if x is less then k
        return selectRecursive(h->right, k - x - 1);
    }
    return h->item;
}
static void sortOrderRecursive(BSTlink x, int strategy) {
    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return;
    }
    if (strategy == PREORDER) {                                                                                         // if that checks the strategy
        ITEMshow(x->item);
    }
    sortOrderRecursive(x->left, strategy);
    if (strategy == INORDER) {                                                                                          // if that checks the strategy
        ITEMshow(x->item);
    }
    sortOrderRecursive(x->right, strategy);
    if (strategy == POSTORDER) {                                                                                        // if that checks the strategy
        ITEMshow(x->item);
    }
}
static void freeRecursive(BSTlink x) {
    if (x == NULL) {                                                                                                    // if that checks the terminal case (h is a leaf)
        return;
    }
    freeRecursive(x->left);
    freeRecursive(x->right);
    ITEMfree(x->item);
    free(x->right);
    free(x->left);
    free(x->parent);
    free(x);
}
int BSTcount(Bst bst) {
    return bst->N;
}
void BSTdelete(Bst bst, Date x) {
    bst->root = deleteRecursive(bst->root, x);
    bst->N--;
}
dailyQuotation BSTfollowing(Bst bst, Date x) {
    return searchFollowing(bst->root, x);
}
void BSTfree(Bst bst) {
    freeRecursive(bst->root);
}
int BSTisEmpty(Bst bst) {
    if (BSTcount(bst) == 0) {
        return 1;
    }
    return 0;
}
Bst BSTinit() {
    Bst bst;

    bst = (Bst) calloc(1, sizeof(bst));
    assert(bst != NULL);
    return bst;
}
void BSTinsertLeafIterative(Bst bst, dailyQuotation x) {
    BSTlink h, p;                                                                                                         // the auxiliary nodes

    if (bst->root == NULL) {                                                                                            // if that checks if the bst is empty
        bst->root = newNode(x, NULL, NULL, NULL, 1);
        bst->N++;
        return;
    }
    for (p = bst->root, h = p; h != NULL;) {                                                                            // cycle on the bst
        p = h;
        h->N++;
        if (KEYless(KEYget(x), KEYget(h->item)) != FALSE) {                                                             // if that checks if x is less then h
            h = h->left;
        } else {
            h = h->right;
        }
    }
    h = newNode(x, p, NULL, NULL, 1);
    bst->N++;
    if (KEYless(KEYget(x), KEYget(h->item)) != FALSE) {                                                                 // if that checks if x is less then h
        p->left = h;
    } else {
        p->right = h;
    }
}
void BSTinsertLeafRecursive(Bst bst, dailyQuotation x) {
    bst->root = insertRecursive(bst->root, x);
    bst->N++;
}
void BSTinsertRoot(Bst bst, dailyQuotation x) {
    bst->root = insertRoot(bst->root, x);
    bst->N++;
}
dailyQuotation BSTmaximum(Bst bst) {
    return maximumRecursive(bst->root);
}
dailyQuotation BSTminimum(Bst bst) {
    return minimumRecursive(bst->root);
}
dailyQuotation BSTprevious(Bst bst, Date x) {
    return searchPrevious(bst->root, x);
}
dailyQuotation BSTsearch(Bst bst, Date x) {
    return searchRecursive(bst->root, x);
}
dailyQuotation BSTselect(Bst bst, int x) {
    return selectRecursive(bst->root, x);
}
void BSTsortInOrder(Bst bst) {
    sortOrderRecursive(bst->root, INORDER);
}
void BSTsortPostOrder(Bst bst) {
    sortOrderRecursive(bst->root, POSTORDER);
}
void BSTsortPreOrder(Bst bst) {
    sortOrderRecursive(bst->root, PREORDER);
}