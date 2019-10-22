#ifndef LAB10_3_ITEM_H
#define LAB10_3_ITEM_H

typedef char *Key;
typedef struct _item *Item;

void ITEMfree(Item x);
Item ITEMinit(Key computerId, Key networkId);
Key ITEMnetwork(Item x);
int KEYcompare(Key x, Key y);
Key KEYget(Item x);

#endif //LAB10_3_ITEM_H