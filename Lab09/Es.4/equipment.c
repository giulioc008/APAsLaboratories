#include <assert.h>
#include "equipment.h"
#include <stdlib.h>
#include <string.h>

typedef struct equip {
    int use, length;
    int equipment[8];
} equipment;                                                                                                            // the equipment of the player

void addEquipmentPlayer(Equipment x, Inventory inventario) {
    int i;                                                                                                              // the index

    if(x->use == FALSE){                                                                                   // if that checks if the equipment is already used
        x->use = 1;
    }
    fprintf(stdout, "\tInsert the index of the object to add.\n\tThe possibilities are:\n");
    for (i = 0; i < inventoryLength(inventario); i++) {                                                                 // cycle on the inventory
        fprintf(stdout, "\t\t%d.\t%s\n", i + 1, objectName(inventoryElement(inventario, i)));
    }
    fprintf(stdout, "\tCommand: ");
    fscanf(stdin, "%d", &i);
    x->equipment[x->length++] = --i;
}
int *equip(Equipment x) {
    return x->equipment;
}
int equipmentElement(Equipment x, int i) {
    return x->equipment[i];
}
int equipmentLength(Equipment x) {
    return x->length;
}
Equipment equipmentMalloc() {
    Equipment equip;

    equip = (Equipment) malloc(sizeof(equipment));
    assert(equip != NULL);
    equip->use = FALSE;
    equip->length = 0;
    return equip;
}
int isUsed(Equipment x) {
    return x->use;
}
void removeEquipmentPlayer(Equipment x, Inventory inventario) {
    int i;                                                                                                              // the indexes

    switch(x->length) {                                                                                                 // switch that regulates the erasing of the object
        case 0:
            break;
        case 1:
            x->use = FALSE;
            free(x->equipment);
            x->length--;
            break;
        default:
            fprintf(stdout, "\tInsert the index of the object to remove.\n\tThe possibilities are:\n");
            for (i = 0; i < x->length; i++) {                                                                           // cycle on the equipment
                fprintf(stdout, "\t\t%d.\t%s\n", i + 1, objectName(inventoryElement(inventario, x->equipment[i])));
            }
            fprintf(stdout, "\tCommand: ");
            fscanf(stdin, "%d", &i);
            x->equipment[--i] = x->equipment[--x->length];
            break;
    }
}