#ifndef LAB08_3_PLAYER_H
#define LAB08_3_PLAYER_H

#include "equipment.h"

typedef struct pg {
    char code[6 + 1], *name, *class;
    Equipment equip;
    statistics stats;
} player, *Player;                                                                                                               // the players

char *playerCode(Player x);
char *playerName(Player x);
statistics stats(Player x, Inventory inventario);

#endif //LAB08_3_PLAYER_H