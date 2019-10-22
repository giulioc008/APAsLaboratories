#include <assert.h>
#include "player.h"
#include <stdlib.h>
#include <string.h>

#define CLOSE -1

typedef enum {
    new,
    erase,
    edit,
    stat,
    finish,
    error
} menu;                                                                                                                 // the principal menu
typedef enum {
    add,
    extract,
    back,
    quit,
    fail
} editMenu;                                                                                                             // the submenu relative to the editing of the equipment of the player

editMenu readEditMenuCommand();
menu readMenuCommand();
int selectionEditMenu(link head, Inventory inventario, editMenu command);
int selectionMenu(List lista, Inventory inventario, menu command);

int main() {
    int flag;                                                                                                           // the flag
    Inventory inventario;                                                                                               // the inventory
    List lista;                                                                                                         // the list
    menu command;                                                                                                       // the command relative to the principal menu

    lista = readPlayers();
    fprintf(stdout, "Players:\n");
    printPlayers(lista, stdout);
    fprintf(stdout, "\n\nInventory:\n");
    inventario = readInventory();
    printInventory(inventario, stdout);
    fprintf(stdout, "\n");
    for(flag = 1; flag != FALSE && flag != CLOSE; ) {
        command = readMenuCommand();
        flag = selectionMenu(lista, inventario, command);
    }
    return 0;
}

editMenu readEditMenuCommand() {
    char string[35 + 2];                                                                                                // string that read the command
    char table[4][35 + 1] = {"Add an object to the equipment",                                                          // matrix that contains the string of the command
                             "Remove an object from the equipment",
                             "Return",
                             "Exit"};
    int j;                                                                                                              // index used for cycling on the table
    editMenu index;                                                                                                     // index used for cycling on the submenu

    fprintf(stdout, "\tChoose the operation.\n\tThe possibilities are:\n");
    for(j = 0; j < 4; j++) {                                                                                            // cycle on the table
        fprintf(stdout, "\t\t%s\n", table[j]);
    }
    fprintf(stdout, "\tCommand: ");
    fgets(string, 35 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = add, j = 0; index < fail && j < 4 && stricmp(string, table[j]) != 0; index++, j++);                     // cycle on the table and the submenu
    return index;
}
menu readMenuCommand() {
    char string[19 + 2];                                                                                                // string that read the command
    char table[5][19 + 1] = {"Add a player",                                                                            // matrix that contains the string of the command
                             "Remove a player",
                             "Edit the equipment",
                             "View the statistics",
                             "Exit"};
    int j;                                                                                                              // index used for cycling on the table
    menu index;                                                                                                         // index used for cycling on the menu

    fprintf(stdout, "Choose the operation.\nThe possibilities are:\n");
    for(j = 0; j < 5; j++) {                                                                                            // cycle on the table
        fprintf(stdout, "\t%s\n", table[j]);
    }
    fprintf(stdout, "Command: ");
    fgets(string, 19 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = new, j = 0; index < error && j < 5 && stricmp(string, table[j]) != 0; index++, j++);                    // cycle on the table and the menu
    return index;
}
int selectionEditMenu(link head, Inventory inventario, editMenu command) {
    char string[50 + 1];                                                                                                // string that read the code of the player
    link x;                                                                                                             // the auxiliary node

    switch(command){                                                                                                    // switch that regulates the operation
        case add:
            fprintf(stdout, "\tInsert the code of the player: ");
            fgets(string, 50 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            x = searchPlayer(head, string);
            if(x != NULL) {                                                                                             // if that checks if the search has product an output
                addEquipment(x, inventario);
            } else {
                if(stricmp(playerCode(head), string) == 0) {                                                            // if that checks the particular case (the node to search is the head)
                    addEquipment(head, inventario);
                } else {
                    fprintf(stdout, "\tTheplayer doesn't exists\n");
                }
            }
            break;
        case extract:
            fprintf(stdout, "\tInsert the code of the player: ");
            fgets(string, 50 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            x = searchPlayer(head, string);
            if(x != NULL) {                                                                                             // if that checks if the search has product an output
                removeEquipment(x);
            } else {
                if(stricmp(playerCode(head), string) == 0) {                                                            // if that checks the particular case (the node to search is the head)
                    removeEquipment(head);
                } else {
                    fprintf(stdout, "\tTheplayer doesn't exists\n");
                }
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
    char string[50 + 1];                                                                                                // string that read the code of the player
    editMenu editCommand;                                                                                               // the command relative to the submenu relative to the editing of the equipment of the player
    int flag;                                                                                                           // the flag
    link x;                                                                                                             // the auxiliary node
    statistics s;                                                                                                       // the statistics of the player

    switch(command){                                                                                                    // switch that regulates the operation
        case new:
            addPlayer(lista);
            break;
        case erase:
            removePlayer(lista);
            break;
        case edit:
            for(flag = 1; flag != FALSE && flag != CLOSE;) {                                                            // loop
                editCommand = readEditMenuCommand();
                flag = selectionEditMenu(head(lista), inventario, editCommand);
            }
            if(flag == CLOSE) {                                                                                         // if that checks the flag
                return flag;
            }
            break;
        case stat:
            fprintf(stdout, "Insert the code of the player: ");
            fgets(string, 50 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            x = searchPlayer(head(lista), string);
            if(x != NULL) {                                                                                             // if that checks if the search has product an output
                s = stats(next(x));
                fprintf(stdout, "The statistics of the player %s are:\n\tHealt Points: %d\n\tMP: %d\n\tAttack: %d\n\tDefense: %d\n\tMag: %d\n\tSpr: %d\n", playerName(next(x)), s.healtPoints, s.mp, s.attack, s.defense, s.mag, s.spr);
            } else {
                if(stricmp(playerCode(head(lista)), string) == 0) {                                                     // if that checks the particular case (the node to search is the head)
                    s = stats(head(lista));
                    fprintf(stdout, "The statistics of the player %s are:\n\tHealt Points: %d\n\tMP: %d\n\tAttack: %d\n\tDefense: %d\n\tMag: %d\n\tSpr: %d\n", playerName(head(lista)), s.healtPoints, s.mp, s.attack, s.defense, s.mag, s.spr);
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