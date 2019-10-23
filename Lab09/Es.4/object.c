#include "object.h"

char *objectName(object obj) {
    return obj.name;
}
char *objectType(object obj) {
    return obj.type;
}
statistics objectStatistics(object obj) {
    return obj.stats;
}
void print(object obj, FILE *filePointer) {
    fprintf(filePointer, "%s %s %d %d %d %d %d %d\n", objectName(obj), objectType(obj), objectStatistics(obj).healtPoints, objectStatistics(obj).mp, objectStatistics(obj).attack, objectStatistics(obj).defense, objectStatistics(obj).mag, objectStatistics(obj).spr);
}