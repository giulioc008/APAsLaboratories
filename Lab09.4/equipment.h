#ifndef LAB09_4_EQUIPMENT_H
#define LAB09_4_EQUIPMENT_H

#include "inventory.h"

typedef struct equip *Equipment;                                                                                        // the equipment of the player

void addEquipmentPlayer(Equipment x, Inventory inventario);
int *equip(Equipment x);
int equipmentElement(Equipment x, int i);
int equipmentLength(Equipment x);
Equipment equipmentMalloc();
int isUsed(Equipment x);
void removeEquipmentPlayer(Equipment x, Inventory inventario);

#endif //LAB09_4_EQUIPMENT_H