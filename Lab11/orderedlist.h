#ifndef LAB11_1_ORDEREDLIST_H
#define LAB11_1_ORDEREDLIST_H

#include "title.h"

typedef struct _node *link;                                                                                             // the node of the list

link LISTdeleteHead(link head);
link LISTdeleteKey(link head, char *k);
link LISTdeleteKeyRecursive(link x, char *k);
title LISTextractHeadPointer(link *head);
title LISTextractKeyPointer(link *head, char *k);
void LISTfree(link *head);
void LISTinsertHeadPointer(link *head, title val);
void LISTinsertTailFast(link *head, link *tail, title val);
link LISTreverse(link x, link *tail);
title LISTsearch(link head, char *k);
void LISTshow(link head);
void LISTsort(link *head);
link SortLISTDelete(link head, char *k);
link SortLISTInsert(link head, title val);
title SortLISTSearch(link head, char *k);

#endif //LAB11_1_ORDEREDLIST_H