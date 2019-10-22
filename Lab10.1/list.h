#ifndef LAB10_1_LIST_H
#define LAB10_1_LIST_H

#define NUMBEROFELEMENT 5

typedef struct _node *link;                                                                                             // the list

int *LISTdiagonal(link x);
int LISTdiagonalLength(link x);
void LISTfree(link *head);
void LISTinsertHeadPointers(link *head, int *diagonal, int diagonalLength);
link LISTnext(link x);

#endif //LAB10_1_LIST_H