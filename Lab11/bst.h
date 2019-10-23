#ifndef LAB11_1_BST_H
#define LAB11_1_BST_H

#include "dailyquotation.h"

typedef struct _bst *Bst;                                                                                               // the bst

int BSTcount(Bst bst);
void BSTdelete(Bst bst, Date x);
dailyQuotation BSTfollowing(Bst bst, Date x);
void BSTfree(Bst bst);
int BSTisEmpty(Bst bst);
Bst BSTinit();
void BSTinsertLeafIterative(Bst bst, dailyQuotation x);
void BSTinsertLeafRecursive(Bst bst, dailyQuotation x);
void BSTinsertRoot(Bst bst, dailyQuotation x);
dailyQuotation BSTmaximum(Bst bst);
dailyQuotation BSTminimum(Bst bst);
dailyQuotation BSTprevious(Bst bst, Date x);
dailyQuotation BSTsearch(Bst bst, Date x);
dailyQuotation BSTselect(Bst bst, int x);
void BSTsortInOrder(Bst bst);
void BSTsortPostOrder(Bst bst);
void BSTsortPreOrder(Bst bst);

#endif //LAB11_1_BST_H