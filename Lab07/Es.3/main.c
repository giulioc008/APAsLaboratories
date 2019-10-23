#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define CLOSE -1

typedef struct {
  int healtPoints, mp, attack, defense, mag, spr;
} statistics;               // the statistics
typedef struct {
    char *name, *type;
    statistics stats;
} object, *Object;          // the object
typedef struct {
    int numberOfElement;
    Object listOfElement;
} inventory, *Inventory;    // the inventory
typedef struct {
    int use, length;
    Object *equipment;
} equipment, *Equipment;    // the equipment of the player
typedef struct {
    char code[6 + 1], *name, *class;
    Equipment equip;
    statistics stats;
} player;                   // the players
typedef struct nodo node, *link;               // the node of the list
struct nodo {
    link next;
    player gamer;
};
typedef struct {
    int numberOfPalyers;
    link head, tail;
} list, *List;              // the list
typedef enum {
    new,
    erase,
    edit,
    stat,
    finish,
    error
} menu;                       // the principal menu
typedef enum {
    add,
    extract,
    back,
    quit,
    fail
} editMenu;                   // the submenu relative to the editing of the equipment of the player

void delete(link *x);
void insertInTail(link *head, link *tail, player gamer);
link newNode(link next, player gamer);
editMenu readEditMenuCommand();
menu readMenuCommand();
List readPlayer();
Inventory readInventory();
link search(link head, char *code);
int selectionEditMenu(link x, Inventory inventario, editMenu command);
int selectionMenu(List lista, Inventory inventario, menu command);
statistics stats(link x);

int main() {
    int flag;
    Inventory inventario;
    List lista;
    menu command;

    lista = readPlayer();
    inventario = readInventory();
    for(flag = 1; flag != FALSE && flag != CLOSE;) {
        command = readMenuCommand();
        flag = selectionMenu(lista, inventario, command);
    }
    return 0;
}

void delete(link *x) {
    link y;                                         // the auxiliary node

    y = (*x)->next;
    (*x)->next = (*x)->next->next;
    free(y);
}
void insertInTail(link *head, link *tail, player gamer) {
    if(*head == NULL){                              // if that checks if the list is empty
        *head = *tail = newNode(NULL, gamer);
    } else {
        (*tail)->next = newNode(NULL, gamer);
        *tail = (*tail)->next;
    }
}
link newNode(link next, player gamer) {
    link x;                                 // the auxiliary node

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                         // if that checks if the node is allocated
        x->next = next;
        x->gamer = gamer;
    }
    return x;
}
editMenu readEditMenuCommand() {
    char string[35 + 2];                                                                                    // string that read the command
    char table[4][35 + 1] = {"Add an object to the equipment",                                              // matrix that contains the string of the command
                             "Remove an object from the equipment",
                             "Return",
                             "Exit"};
    int j;                                                                                                  // index used for cycling on the table
    editMenu index;                                                                                         // index used for cycling on the submenu

    fprintf(stdout, "\tChoose the operation.\n\tThe possibilities are:\n");
    for(j = 0; j < 4; j++) {                                                                                // cycle on the table
        fprintf(stdout, "\t\t%s\n", table[j]);
    }
    fprintf(stdout, "\tCommand: ");
    fgets(string, 35 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = add, j = 0; index < fail && j < 4 && stricmp(string, table[j]) != 0; index++, j++);         // cycle on the table and the submenu
    return index;
}
menu readMenuCommand() {
    char string[19 + 2];                                                                                    // string that read the command
    char table[5][19 + 1] = {"Add a player",                                                                // matrix that contains the string of the command
                             "Remove a player",
                             "Edit the equipment",
                             "View the statistics",
                             "Exit"};
    int j;                                                                                                  // index used for cycling on the table
    menu index;                                                                                             // index used for cycling on the menu

    fprintf(stdout, "Choose the operation.\nThe possibilities are:\n");
    for(j = 0; j < 5; j++) {                                                                                // cycle on the table
        fprintf(stdout, "\t%s\n", table[j]);
    }
    fprintf(stdout, "Command: ");
    fgets(string, 19 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = new, j = 0; index < error && j < 5 && stricmp(string, table[j]) != 0; index++, j++);        // cycle on the table and the menu
    return index;
}
List readPlayer() {
    char buffer[50 + 1];                                            // the buffer
    FILE *filePointer;                                              // the file
    List lista;                                                     // the list
    player x;                                                       // the auxiliary player

    lista = (List) malloc(sizeof(list));
    assert(lista != NULL);
    lista->head = lista->tail = NULL;
    lista->numberOfPalyers = 0;
    filePointer = fopen("pg.txt", "r");
    for (; feof(filePointer) == FALSE;) {                           // cycle on the players
        fscanf(filePointer, "%s %s", x.code, buffer);
        x.name = strdup(buffer);
        assert(x.name != NULL);
        fscanf(filePointer, "%s %d %d %d %d %d %d", buffer, &x.stats.healtPoints, &x.stats.mp, &x.stats.attack, &x.stats.defense, &x.stats.mag, &x.stats.spr);
        assert(x.stats.healtPoints > 0 && x.stats.mp > 0 && x.stats.attack > 0 && x.stats.defense > 0 && x.stats.mag > 0 && x.stats.spr > 0);
        x.class = strdup(buffer);
        assert(x.class != NULL);
        x.equip = (Equipment) malloc(sizeof(equipment));
        assert(x.equip != NULL);
        x.equip->use = FALSE;
        x.equip->length = 0;
        x.equip->equipment = NULL;
        insertInTail(&lista->head, &lista->tail, x);
        lista->numberOfPalyers++;
    }
    fclose(filePointer);
    return lista;
}
Inventory readInventory() {
    char buffer[50 + 1];                                                                        // the buffer
    FILE *filePointer;                                                                          // the file
    int i;                                                                                      // the index
    Inventory inventario;                                                                       // the inventory

    inventario = (Inventory) malloc(sizeof(inventory));
    filePointer = fopen("inventario.txt", "r");
    fscanf(filePointer, "%d", &inventario->numberOfElement);                                    // reading the file
    inventario->listOfElement = (Object) malloc(inventario->numberOfElement * sizeof(object));
    for (i = 0; i < inventario->numberOfElement; i++) {                                         // cycle on the object
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
link search(link head, char *code) {
    link x, p;                                                             // the auxiliary nodes

    for (p = head, x = head->next; x != NULL; p = x, x = x->next) {        // cycle on the list
        if(stricmp(x->gamer.code, code) == 0){                             // if that checks if the code of the player is equal to the coe to search
            return p;
        }
    }
    return NULL;
}
int selectionEditMenu(link x, Inventory inventario, editMenu command) {
    int i, j;                                                                                                   // the indexes

    switch(command){                                                                                            // switch that regulates the operation
        case add:
            if(x->gamer.equip->use == FALSE){                                                                   // if that checks if the equipment is already used
                x->gamer.equip->use = 1;
                x->gamer.equip->equipment = (Object *) malloc(8 * sizeof(Object));
                assert(x->gamer.equip->equipment != NULL);
            }
            fprintf(stdout, "\tInsert the index of the object to add.\n\tThe possibilities are:\n");
            for (i = 0; i < inventario->numberOfElement; i++) {                                                 // cycle on the inventory
                fprintf(stdout, "\t\t%d.\t%s %s %d %d %d %d %d %d\n", i + 1, inventario->listOfElement[i].name, inventario->listOfElement[i].type, inventario->listOfElement[i].stats.healtPoints, inventario->listOfElement[i].stats.mp, inventario->listOfElement[i].stats.attack, inventario->listOfElement[i].stats.defense, inventario->listOfElement[i].stats.mag, inventario->listOfElement[i].stats.spr);
            }
            fprintf(stdout, "\tCommand: ");
            fscanf(stdin, "%d", &i);
            x->gamer.equip->equipment[x->gamer.equip->length++] = &inventario->listOfElement[--i];
            break;
        case extract:
            switch(x->gamer.equip->length) {                                                                                         // switch that regulates the erasing of the object
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
                        fprintf(stdout, "\t\t%d.\t%s\n", i + 1, x->gamer.equip->equipment[i]->name);
                    }
                    fprintf(stdout, "\tCommand: ");
                    fscanf(stdin, "%d", &j);
                    for (i = --j; i < x->gamer.equip->length - 1; i++) {                                                        // cycle on the equipment
                        x->gamer.equip->equipment[i] = x->gamer.equip->equipment[i + 1];
                    }
                    x->gamer.equip->equipment[i] = NULL;
                    x->gamer.equip->length--;
                    break;
            }
            break;
        case back:
            return FALSE;
        case quit:
            return CLOSE;
        case fail:
            break;
        default:
            return FALSE;
    }
    return 1;
}
int selectionMenu(List lista, Inventory inventario, menu command) {
    char string[50 + 1];                                                                                    // string that read the code of the player
    editMenu editCommand;                                                                                   // the command relative to the submenu relative to the editing of the equipment of the player
    int flag;                                                                                               // the flag
    link x;                                                                                                 // the auxiliary node
    player y;                                                                                               // the auxiliary player
    statistics s;                                                                                           // the statistics of the player

    switch(command){                                                                                        // switch that regulates the operation
        case new:
            fprintf(stdout, "Insert the data of the player to add\n\tCode: ");
            fgets(y.code, 6 + 2, stdin);
            y.code[strlen(y.code) - 1] = '\0';
            fprintf(stdout, "\n\tName: ");
            fgets(string, 50 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            y.name = strdup(string);
            assert(y.name != NULL);
            fprintf(stdout, "\n\tClass: ");
            fgets(string, 50 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            y.class = strdup(string);
            assert(y.class != NULL);
            fprintf(stdout, "\n\tStatistics with the format <healt points> <mp> <attack> <defense> <mag> <spr>: ");
            fscanf(stdin, "%d %d %d %d %d %d", &y.stats.healtPoints, &y.stats.mp, &y.stats.attack, &y.stats.defense, &y.stats.mag, &y.stats.spr);
            assert(y.stats.healtPoints > 0 && y.stats.mp > 0 && y.stats.attack > 0 && y.stats.defense > 0 && y.stats.mag > 0 && y.stats.spr > 0);
            y.equip = (Equipment) malloc(sizeof(equipment));
            assert(y.equip != NULL);
            y.equip->use = FALSE;
            y.equip->equipment = NULL;
            y.equip->length = 0;
            insertInTail(&lista->head, &lista->tail, y);
            lista->numberOfPalyers++;
            break;
        case erase:
            fprintf(stdout, "Insert the code of the player: ");
            fgets(string, 50 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            x = search(lista->head, string);
            if(x != NULL) {                                                                                 // if that checks if the search has product an output
                delete(&x);
                lista->numberOfPalyers--;
            } else {
                if(stricmp(lista->head->gamer.code, string) == 0) {                                         // if that checks the particular case (the node to search is the head)
                    x = lista->head;
                    lista->head = lista->head->next;
                    free(x);
                    lista->numberOfPalyers--;
                } else {
                    fprintf(stdout, "Theplayer doesn't exists\n");
                }
            }
            break;
        case edit:
            for(flag = 1; flag != FALSE && flag != CLOSE;) {                                                // loop
                editCommand = readEditMenuCommand();
                if(editCommand == add || editCommand == extract) {                                          // if that checks the command
                    fprintf(stdout, "\tInsert the code of the player: ");
                    fgets(string, 50 + 2, stdin);
                    string[strlen(string) - 1] = '\0';
                    x = search(lista->head, string);
                    if (x != NULL) {                                                                        // if that checks if the search has product an output
                        flag = selectionEditMenu(x->next, inventario, editCommand);
                    } else if (stricmp(lista->head->gamer.code, string) == 0) {                             // if that checks the particular case (the node to search is the head)
                        flag = selectionEditMenu(lista->head, inventario, editCommand);
                    }
                } else {
                    flag = selectionEditMenu(NULL, inventario, editCommand);
                }
            }
            if(flag == CLOSE) {                                                                             // if that checks the flag
                return flag;
            }
            break;
        case stat:
            fprintf(stdout, "Insert the code of the player: ");
            fgets(string, 50 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            x = search(lista->head, string);
            if(x != NULL) {                                                                                 // if that checks if the search has product an output
                s = stats(x->next);
                fprintf(stdout, "The statistics of the player %s are:\n\tHealt Points: %d\n\tMP: %d\n\tAttack: %d\n\tDefense: %d\n\tMag: %d\n\tSpr: %d\n", x->next->gamer.name, s.healtPoints, s.mp, s.attack, s.defense, s.mag, s.spr);
            } else {
                if(stricmp(lista->head->gamer.code, string) == 0) {                                         // if that checks the particular case (the node to search is the head)
                    s = stats(lista->head);
                    fprintf(stdout, "The statistics of the player %s are:\n\tHealt Points: %d\n\tMP: %d\n\tAttack: %d\n\tDefense: %d\n\tMag: %d\n\tSpr: %d\n", lista->head->gamer.name, s.healtPoints, s.mp, s.attack, s.defense, s.mag, s.spr);
                } else {
                    fprintf(stdout, "Theplayer doesn't exists\n");
                }
            }
            break;
        case finish:
            return CLOSE;
        case error:
            break;
        default:
            return FALSE;
    }
    return 1;
}
statistics stats(link x) {
  int i;                                                                          // the index
  statistics stats;                                                               // the statistics of the player

  stats.healtPoints = x->gamer.stats.healtPoints;
  stats.mp = x->gamer.stats.mp;
  stats.attack = x->gamer.stats.attack;
  stats.defense = x->gamer.stats.defense;
  stats.mag = x->gamer.stats.mag;
  stats.spr = x->gamer.stats.spr;
  if(x->gamer.equip->use != FALSE) {                                              // if that checks if the player have an equipment
      for (i = 0; i < x->gamer.equip->length; i++) {                              // cycle on the equipment of the player
          stats.healtPoints += x->gamer.equip->equipment[i]->stats.healtPoints;
          stats.mp += x->gamer.equip->equipment[i]->stats.mp;
          stats.attack += x->gamer.equip->equipment[i]->stats.attack;
          stats.defense += x->gamer.equip->equipment[i]->stats.defense;
          stats.mag += x->gamer.equip->equipment[i]->stats.mag;
          stats.spr += x->gamer.equip->equipment[i]->stats.spr;
      }
  }
  if(stats.healtPoints < 1) {
    stats.healtPoints = 1;
  }
  if(stats.mp < 1) {
    stats.mp = 1;
  }
  if(stats.attack < 1) {
    stats.attack = 1;
  }
  if(stats.defense < 1) {
    stats.defense = 1;
  }
  if(stats.mag < 1) {
    stats.mag = 1;
  }
  if(stats.spr < 1) {
    stats.spr = 1;
  }
  return stats;
}