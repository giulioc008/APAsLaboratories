#ifndef LAB09_4_OBJECT_H
#define LAB09_4_OBJECT_H

#include <stdio.h>

#define FALSE 0

typedef struct st {
    int healtPoints, mp, attack, defense, mag, spr;
} statistics;                                                                                                           // the statistics
typedef struct ob {
    char *name, *type;
    statistics stats;
} object, *Object;                                                                                                      // the object

char *objectName(object obj);
char *objectType(object obj);
statistics objectStatistics(object obj);
void print(object obj, FILE *filePointer);

#endif //LAB09_4_OBJECT_H
