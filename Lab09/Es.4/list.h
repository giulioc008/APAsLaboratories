#ifndef LAB09_4_LIST_H
#define LAB09_4_LIST_H

#include "player.h"
#include <stdio.h>

typedef struct nodo *link;                                                                                              // the node of the list
typedef struct l *List;                                                                                                 // the node of the list

void addEquipment(link x, Inventory inventario);
void addPlayer(List lista);
Player gamer(link x);
link head(List lista);
void insertInTail(link *head, link *tail, player gamer);
link newNode(link next, player gamer);
link next(link x);
void printPlayers(List lista, FILE *filePointer, Inventory inventario);
List readPlayers();
void removeEquipment(link x, Inventory inventario);
void removeNode(link *x);
void removePlayer(List lista);
link searchPlayer(link head, char *code);

#endif //LAB09_4_LIST_H