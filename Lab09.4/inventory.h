#ifndef LAB08_3_INVENTORY_H
#define LAB08_3_INVENTORY_H

#include "object.h"
#include <stdio.h>

typedef struct inv *Inventory;                                                                                          // the inventory

object inventoryElement(Inventory inventario, int i);
int inventoryLength(Inventory inventario);
void printInventory(Inventory inventario, FILE *filePointer);
Inventory readInventory();
object search(Inventory inventario, char *name);

#endif //LAB08_3_INVENTORY_H