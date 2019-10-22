#include <assert.h>
#include "inventory.h"
#include <stdlib.h>
#include <string.h>

typedef struct inv {
    int numberOfElement;
    Object listOfElement;
} inventory;                                                                                                            // the inventory

object inventoryElement(Inventory inventario, int i) {
    return inventario->listOfElement[i];
}
int inventoryLength(Inventory inventario) {
    return inventario->numberOfElement;
}
void printInventory(Inventory inventario, FILE *filePointer) {
    int i;                                                                                                              // the index

    for (i = 0; i < inventario->numberOfElement; i++) {
        print(inventoryElement(inventario, i), filePointer);
    }
}
Inventory readInventory() {
    char buffer[50 + 1];                                                                                                // the buffer
    FILE *filePointer;                                                                                                  // the file
    int i;                                                                                                              // the index
    Inventory inventario;                                                                                               // the inventory

    inventario = (Inventory) malloc(sizeof(inventory));
    filePointer = fopen("inventario.txt", "r");
    fscanf(filePointer, "%d", &inventario->numberOfElement);                                                            // reading the file
    inventario->listOfElement = (Object) malloc(inventario->numberOfElement * sizeof(object));
    for (i = 0; i < inventario->numberOfElement; i++) {                                                                 // cycle on the object
        fscanf(filePointer, "%s", buffer);
        inventario->listOfElement[i].name = strdup(buffer);
        assert(inventario->listOfElement[i].name != NULL);
        fscanf(filePointer, "%s %d %d %d %d %d %d", buffer, &inventario->listOfElement[i].stats.healtPoints, &inventario->listOfElement[i].stats.mp, &inventario->listOfElement[i].stats.attack, &inventario->listOfElement[i].stats.defense, &inventario->listOfElement[i].stats.mag, &inventario->listOfElement[i].stats.spr);
        inventario->listOfElement[i].type = strdup(buffer);
        assert(inventario->listOfElement[i].type != NULL);
    }
    fclose(filePointer);
    return inventario;
}
object search(Inventory inventario, char *name) {
    int i;                                                                                                              // the index
    object x;                                                                                                           // the index

    x.name = x.type = strdup("");
    assert(x.name != NULL && x.type != NULL);
    x.stats.healtPoints = x.stats.mp = x.stats.attack = x.stats.defense = x.stats.mag = x.stats.spr = 0;
    for (i = 0; i < inventario->numberOfElement; i++) {
        if(stricmp(objectName(inventoryElement(inventario, i)), name) == 0) {
            return inventoryElement(inventario, i);
        }
    }
    return x;
}