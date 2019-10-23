#ifndef LAB10_3_LIST_H
#define LAB10_3_LIST_H

typedef struct _node *link;

link LISTdelete(link head, int vertex);
void LISTfree(link *head);
void LISTinsertHeadPointer(link *head, int vertexW, int weight);
int LISTsearch(link head, int vertexW);

#endif //LAB10_3_LIST_H