#include <assert.h>
#include "item.h"
#include <stdlib.h>
#include <string.h>

typedef struct _item {
    Key computerId, networkId;
} item;                                                                                                                 // the item

void ITEMfree(Item x) {
    free(x->computerId);
    free(x->networkId);
    free(x);
}
Item ITEMinit(Key computerId, Key networkId) {
    Item x;                                                                                                             // the item

    x = (Item) malloc(sizeof(item));
    assert(x != NULL);
    x->computerId = strdup(computerId);
    assert(x->computerId != NULL);
    x->networkId = strdup(networkId);
    assert(x->networkId != NULL);
    return x;
}
Key ITEMnetwork(Item x) {
    return x->networkId;
}
int KEYcompare(Key x, Key y) {
    return stricmp(x, y);
}
Key KEYget(Item x) {
    return x->computerId;
}