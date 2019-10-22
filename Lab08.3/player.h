#ifndef LAB08_3_PLAYER_H
#define LAB08_3_PLAYER_H

#include "inventory.h"

#define FALSE 0

typedef struct equip *Equipment;                                                                                        // the equipment of the player
typedef struct pg *Player;                                                                                              // the node of the list
typedef struct nodo *link;                                                                                              // the node of the list
typedef struct l *List;                                                                                                 // the node of the list

void addEquipment(link x, Inventory inventario);
void addPlayer(List lista);
link head(List lista);
void insertInTail(link *head, link *tail, Player gamer);
link newNode(link next, Player gamer);
link next(link x);
void printPlayers(List lista, FILE *filePointer);
char *playerCode(link x);
char *playerName(link x);
List readPlayers();
void removeNode(link *x);
void removePlayer(List lista);
void removeEquipment(link x);
link searchPlayer(link head, char *code);
statistics stats(link x);

#endif //LAB08_3_PLAYER_H