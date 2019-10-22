#ifndef LAB10_3_SIMBOLTABLE_H
#define LAB10_3_SIMBOLTABLE_H

#include "item.h"

typedef struct _st *ST;

void STfree(ST symbolTable);
ST STinit(int length);
int STinsert(ST symbolTable, Key computerId, Key networkId);
int STlength(ST symbolTable);
void STorder(ST symbolTable);
void STrealloc(ST symbolTable);
Key STsearchByIndex(ST symbolTable, int i);
int STsearchByName(ST symbolTable, Key name);

#endif //LAB10_3_SIMBOLTABLE_H