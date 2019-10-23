#include <assert.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    link next;
    player gamer;
} node;                                                                                                                 // the node of the list
typedef struct l {
    int numberOfPalyers;
    link head, tail;
} list;                                                                                                                 // the list

void addEquipment(link x, Inventory inventario) {
    addEquipmentPlayer(x->gamer.equip, inventario);
}
void addPlayer(List lista) {
    char string[50 + 1];                                                                                                // string that read the code of the player
    player x;                                                                                                           // the auxiliary player

    fprintf(stdout, "Insert the data of the player to add\n\tCode: ");
    fgets(x.code, 6 + 2, stdin);
    x.code[strlen(x.code) - 1] = '\0';
    fprintf(stdout, "\n\tName: ");
    fgets(string, 50 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    x.name = strdup(string);
    assert(x.name != NULL);
    fprintf(stdout, "\n\tClass: ");
    fgets(string, 50 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    x.class = strdup(string);
    assert(x.class != NULL);
    fprintf(stdout, "\n\tStatistics with the format <healt points> <mp> <attack> <defense> <mag> <spr>: ");
    fscanf(stdin, "%d %d %d %d %d %d", &x.stats.healtPoints, &x.stats.mp, &x.stats.attack, &x.stats.defense, &x.stats.mag, &x.stats.spr);
    assert(x.stats.healtPoints > 0 && x.stats.mp > 0 && x.stats.attack > 0 && x.stats.defense > 0 && x.stats.mag > 0 && x.stats.spr > 0);
    x.equip = equipmentMalloc();
    insertInTail(&lista->head, &lista->tail, x);
    lista->numberOfPalyers++;
}
Player gamer(link x) {
    return &x->gamer;
}
link head(List lista) {
    return lista->head;
}
void insertInTail(link *head, link *tail, player gamer) {
    if(*head == NULL){                                                                                                  // if that checks if the list is empty
        *head = *tail = newNode(NULL, gamer);
    } else {
        (*tail)->next = newNode(NULL, gamer);
        *tail = (*tail)->next;
    }
}
link newNode(link next, player gamer) {
    link x;                                                                                                             // the auxiliary node

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                                                                                                     // if that checks if the node is allocated
        x->next = next;
        x->gamer = gamer;
    }
    return x;
}
link next(link x) {
    return x->next;
}
void printPlayers(List lista, FILE *filePointer, Inventory inventario) {
    int i;                                                                                                              // the index
    link x;                                                                                                             // the auxiliary nodes

    for (x = lista->head; x != NULL; x = x->next) {                                                                     // cycle on the list
        fprintf(filePointer, "%s %s %s %d %d %d %d %d %d\n", x->gamer.code, x->gamer.name, x->gamer.class, x->gamer.stats.healtPoints, x->gamer.stats.mp, x->gamer.stats.attack, x->gamer.stats.defense, x->gamer.stats.mag, x->gamer.stats.spr);
        if(isUsed(x->gamer.equip) != FALSE) {
            fprintf(filePointer, "Equipment:\n");
            for (i = 0; i < equipmentLength(x->gamer.equip); i++) {
                fprintf(filePointer, "\t");
                print(inventoryElement(inventario, equipmentElement(x->gamer.equip, i)), filePointer);
            }
        }
    }
}
List readPlayers() {
    char buffer[50 + 1];                                                                                                // the buffer
    FILE *filePointer;                                                                                                  // the file
    List lista;                                                                                                         // the list
    player x;                                                                                                           // the auxiliary player

    lista = (List) malloc(sizeof(list));
    assert(lista != NULL);
    lista->head = lista->tail = NULL;
    lista->numberOfPalyers = 0;
    filePointer = fopen("pg.txt", "r");
    for (; feof(filePointer) == FALSE;) {                                                                               // cycle on the players
        fscanf(filePointer, "%s %s", x.code, buffer);
        x.name = strdup(buffer);
        assert(x.name != NULL);
        fscanf(filePointer, "%s %d %d %d %d %d %d", buffer, &x.stats.healtPoints, &x.stats.mp, &x.stats.attack, &x.stats.defense, &x.stats.mag, &x.stats.spr);
        assert(x.stats.healtPoints > 0 && x.stats.mp > 0 && x.stats.attack > 0 && x.stats.defense > 0 && x.stats.mag > 0 && x.stats.spr > 0);
        x.class = strdup(buffer);
        assert(x.class != NULL);
        x.equip = equipmentMalloc();
        insertInTail(&lista->head, &lista->tail, x);
        lista->numberOfPalyers++;
    }
    fclose(filePointer);
    return lista;
}
void removeEquipment(link x, Inventory inventario) {
    removeEquipmentPlayer(x->gamer.equip, inventario);
}
void removeNode(link *x) {
    link y;                                                                                                             // the auxiliary node

    y = (*x)->next;
    (*x)->next = (*x)->next->next;
    free(y);
}
void removePlayer(List lista) {
    char string[50 + 1];                                                                                                // string that read the code of the player
    link x;                                                                                                             // the auxiliary node

    fprintf(stdout, "Insert the code of the player: ");
    fgets(string, 50 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    x = searchPlayer(lista->head, string);
    if(x != NULL) {                                                                                                     // if that checks if the search has product an output
        removeNode(&x);
        lista->numberOfPalyers--;
    } else {
        if(stricmp(head(lista)->gamer.code, string) == 0) {                                                             // if that checks the particular case (the node to search is the head)
            x = head(lista);
            lista->head = head(lista)->next;
            free(x);
            lista->numberOfPalyers--;
        } else {
            fprintf(stdout, "The player doesn't exists\n");
        }
    }

}
link searchPlayer(link head, char *code) {
    link x, p;                                                                                                          // the auxiliary nodes

    for (p = head, x = head->next; x != NULL; p = x, x = x->next) {                                                     // cycle on the list
        if(stricmp(x->gamer.code, code) == 0){                                                                          // if that checks if the code of the player is equal to the coe to search
            return p;
        }
    }
    return NULL;
}