#ifndef LAB08_3_INVENTORY_H
#define LAB08_3_INVENTORY_H

#include <stdio.h>

typedef struct inv *Inventory;                                                                                          // the inventory
typedef struct ob *Object;                                                                                              // the object
typedef struct {
    int healtPoints, mp, attack, defense, mag, spr;
} statistics;                                                                                                           // the statistics

Object inventoryElement(Inventory inventario, int i);
int inventoryLength(Inventory inventario);
char *objectName(Object obj);
char *objectType(Object obj);
statistics objectStatistics(Object obj);
void print(Object obj, FILE *filePointer);
void printInventory(Inventory inventario, FILE *filePointer);
Inventory readInventory();
Object search(Inventory inventario, char *name);

#endif //LAB08_3_INVENTORY_H