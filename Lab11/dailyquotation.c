#include <assert.h>
#include "dailyquotation.h"
#include <stdio.h>
#include <stdlib.h>

static int KEYcompare(Date x, Date y) {
    if(x.year > y.year) {                                                                                               // if that checks if x is greater then y
        return 1;
    } else if(x.year == y.year) {                                                                                       // if that checks if x is equal to y
        if(x.month > y.month) {                                                                                         // if that checks if x is greater then y
            return 1;
        } else if(x.month == y.month) {                                                                                 // if that checks if x is equal to y
            if(x.day > y.day) {                                                                                         // if that checks if x is greater then y
                return 1;
            } else if(x.day == y.day) {                                                                                 // if that checks if x is equal to y
                return 0;
            }
        }
    }
    return -1;
}
void ITEMfree(dailyQuotation x) {
    free(x.value);
    free(x.transaction);
}
dailyQuotation ITEMnew(int length, Date data) {
    dailyQuotation x;                                                                                                   // the auxiliary daily quotation

    x.transaction = (int *) malloc(length * sizeof(int));
    assert(x.transaction != NULL);
    x.value = (float *) malloc(length * sizeof(float));
    assert(x.value != NULL);
    x.numberOfTransaction = 0;
    x.key = data;
    return x;
}
dailyQuotation ITEMsetvoid() {
    dailyQuotation x;                                                                                                   // the auxiliary daily quotation

    x.numberOfTransaction = x.key.year = x.key.month = x.key.day = 0;
    x.value = NULL;
    x.transaction = NULL;
    return x;
}
void ITEMshow(dailyQuotation x) {
    int i;                                                                                                              // the index

    printf("Date: %d/%d/%d\n", x.key.year, x.key.month, x.key.day);
    for(i = 0; i < x.numberOfTransaction; ++i) {
        printf("\tValue: %.2f Quantity: %d\n", x.value[i], x.transaction[i]);
    }
}
int KEYeq(Date x, Date y) {
    if(KEYcompare(x, y) == 0) {                                                                                         // if that checks if x is equal to y
        return 1;
    }
    return FALSE;
}
Date KEYget(dailyQuotation x) {
    return x.key;
}
int KEYgreater(Date x, Date y) {
    if(KEYcompare(x, y) == 1) {                                                                                       // if that checks if x is greater then y
        return 1;
    }
    return FALSE;
}
int KEYless(Date x, Date y) {
    if(KEYcompare(x, y) == -1) {                                                                                      // if that checks if x is less then y
        return 1;
    }
    return FALSE;
}