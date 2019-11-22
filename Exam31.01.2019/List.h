#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct _list *list;

list LISTinit();
void LISTinsertTail(list List, int val);
int LISTextractHead(list head);
void LISTfree(list List);
void LISTshow(list List);
void splice(list L1, list L2, int start, int num);

#endif // LIST_H_INCLUDED