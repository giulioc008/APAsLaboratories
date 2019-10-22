#include <assert.h>
#include "player.h"
#include <stdlib.h>
#include <string.h>

typedef struct equip {
    int use, length;
    Object *equipment;
} equipment;                                                                                                            // the equipment of the player
typedef struct pg {
    char code[6 + 1], *name, *class;
    Equipment equip;
    statistics stats;
} player;                                                                                                               // the players
typedef struct nodo {
    link next;
    player gamer;
} node;                                                                                                                 // the node of the list
typedef struct l {
    int numberOfPalyers;
    link head, tail;
} list;                                                                                                                 // the list

void addEquipment(link x, Inventory inventario) {
    char string[50 + 1];                                                                                                // string that read the code of the player
    int i;                                                                                                              // the index

    if(x->gamer.equip->use == FALSE){                                                                                   // if that checks if the equipment is already used
        x->gamer.equip->use = 1;
        x->gamer.equip->equipment = (Object *) malloc(8 * sizeof(Object));
        assert(x->gamer.equip->equipment != NULL);
    }
    fprintf(stdout, "\tInsert the name of the object to add.\n\tThe possibilities are:\n");
    for (i = 0; i < inventoryLength(inventario); i++) {                                                                 // cycle on the inventory
        fprintf(stdout, "\t\t%s\n", objectName(inventoryElement(inventario, i)));
    }
    fprintf(stdout, "\tCommand: ");
    fgets(string, 50 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    x->gamer.equip->equipment[x->gamer.equip->length++] = search(inventario, string);
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
    x.equip = (Equipment) malloc(sizeof(equipment));
    assert(x.equip != NULL);
    x.equip->use = FALSE;
    x.equip->equipment = NULL;
    x.equip->length = 0;
    insertInTail(&lista->head, &lista->tail, &x);
    lista->numberOfPalyers++;
}
link head(List lista) {
    return lista->head;
}
void insertInTail(link *head, link *tail, Player gamer) {
    if(*head == NULL){                                                                                                  // if that checks if the list is empty
        *head = *tail = newNode(NULL, gamer);
    } else {
        (*tail)->next = newNode(NULL, gamer);
        *tail = (*tail)->next;
    }
}
link newNode(link next,Player gamer) {
    link x;                                                                                                             // the auxiliary node

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                                                                                                     // if that checks if the node is allocated
        x->next = next;
        x->gamer = *gamer;
    }
    return x;
}
link next(link x) {
    return x->next;
}
void printPlayers(List lista, FILE *filePointer) {
    int i;                                                                                                              // the index
    link x;                                                                                                             // the auxiliary nodes

    for (x = lista->head; x != NULL; x = x->next) {                                                                     // cycle on the list
        fprintf(filePointer, "%s %s %s %d %d %d %d %d %d\n", x->gamer.code, x->gamer.name, x->gamer.class, x->gamer.stats.healtPoints, x->gamer.stats.mp, x->gamer.stats.attack, x->gamer.stats.defense, x->gamer.stats.mag, x->gamer.stats.spr);
        if(x->gamer.equip->use != FALSE) {
            fprintf(filePointer, "Equipment:\n");
            for (i = 0; i < x->gamer.equip->length; i++) {
                fprintf(filePointer, "\t");
                print(x->gamer.equip->equipment[i], filePointer);
            }
        }
    }
}
char *playerCode(link x) {
    return x->gamer.code;
}
char *playerName(link x) {
    return x->gamer.name;
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
        fscanf(stdin, "%d %d %d %d %d %d", &x.stats.healtPoints, &x.stats.mp, &x.stats.attack, &x.stats.defense, &x.stats.mag, &x.stats.spr);
        assert(x.stats.healtPoints > 0 && x.stats.mp > 0 && x.stats.attack > 0 && x.stats.defense > 0 && x.stats.mag > 0 && x.stats.spr > 0);
        x.class = strdup(buffer);
        assert(x.class != NULL);
        x.equip = (Equipment) malloc(sizeof(equipment));
        assert(x.equip != NULL);
        x.equip->use = FALSE;
        x.equip->length = 0;
        x.equip->equipment = NULL;
        insertInTail(&lista->head, &lista->tail, &x);
        lista->numberOfPalyers++;
    }
    fclose(filePointer);
    return lista;
}
void removeEquipment(link x) {
    int i;                                                                                                           // the indexes

    switch(x->gamer.equip->length) {                                                                                    // switch that regulates the erasing of the object
        case 0:
            break;
        case 1:
            x->gamer.equip->use = FALSE;
            free(x->gamer.equip->equipment);
            x->gamer.equip->equipment = NULL;
            x->gamer.equip->length = 0;
            break;
        default:
            fprintf(stdout, "\tInsert the index of the object to remove.\n\tThe possibilities are:\n");
            for (i = 0; i < x->gamer.equip->length; i++) {                                                              // cycle on the equipment
                fprintf(stdout, "\t\t%d.\t%s\n", i + 1, objectName(x->gamer.equip->equipment[i]));
            }
            fprintf(stdout, "\tCommand: ");
            fscanf(stdin, "%d", &i);
            i--;
            x->gamer.equip->length--;
            x->gamer.equip->equipment[i] = x->gamer.equip->equipment[x->gamer.equip->length];
            x->gamer.equip->equipment[x->gamer.equip->length] = NULL;
            break;
    }
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
statistics stats(link x) {
    int i;                                                                                                              // the index
    statistics stats;                                                                                                   // the statistics of the player

    stats.healtPoints = x->gamer.stats.healtPoints;
    stats.mp = x->gamer.stats.mp;
    stats.attack = x->gamer.stats.attack;
    stats.defense = x->gamer.stats.defense;
    stats.mag = x->gamer.stats.mag;
    stats.spr = x->gamer.stats.spr;
    if (x->gamer.equip->use != FALSE) {                                                                                 // if that checks if the player have an equipment
        for (i = 0; i < x->gamer.equip->length; i++) {                                                                  // cycle on the equipment of the player
            stats.healtPoints += objectStatistics(x->gamer.equip->equipment[i]).healtPoints;
            stats.mp += objectStatistics(x->gamer.equip->equipment[i]).mp;
            stats.attack += objectStatistics(x->gamer.equip->equipment[i]).attack;
            stats.defense += objectStatistics(x->gamer.equip->equipment[i]).defense;
            stats.mag += objectStatistics(x->gamer.equip->equipment[i]).mag;
            stats.spr += objectStatistics(x->gamer.equip->equipment[i]).spr;
        }
    }
    if(stats.healtPoints < 1) {
        stats.healtPoints  = 1;
    }
    if(stats.mp < 1) {
        stats.mp  = 1;
    }
    if(stats.attack < 1) {
        stats.attack  = 1;
    }
    if(stats.defense < 1) {
        stats.defense  = 1;
    }
    if(stats.mag < 1) {
        stats.mag  = 1;
    }
    if(stats.spr < 1) {
        stats.spr  = 1;
    }

    return stats;
}