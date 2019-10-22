#include "player.h"

char *playerCode(Player x) {
    return x->code;
}
char *playerName(Player x) {
    return x->name;
}
statistics stats(Player x, Inventory inventario) {
    int i;                                                                                                              // the index
    statistics stats;                                                                                                   // the statistics of the player

    stats.healtPoints = x->stats.healtPoints;
    stats.mp = x->stats.mp;
    stats.attack = x->stats.attack;
    stats.defense = x->stats.defense;
    stats.mag = x->stats.mag;
    stats.spr = x->stats.spr;
    if (isUsed(x->equip) != FALSE) {                                                                                    // if that checks if the player have an equipment
        for (i = 0; i < equipmentLength(x->equip); i++) {                                                               // cycle on the equipment of the player
            stats.healtPoints += objectStatistics(inventoryElement(inventario, equip(x->equip)[i])).healtPoints;
            stats.mp += objectStatistics(inventoryElement(inventario, equip(x->equip)[i])).mp;
            stats.attack += objectStatistics(inventoryElement(inventario, equip(x->equip)[i])).attack;
            stats.defense += objectStatistics(inventoryElement(inventario, equip(x->equip)[i])).defense;
            stats.mag += objectStatistics(inventoryElement(inventario, equip(x->equip)[i])).mag;
            stats.spr += objectStatistics(inventoryElement(inventario, equip(x->equip)[i])).spr;
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