#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

void print(void *pointer, int size, int bigEndian);

int main() {
    char string[3 + 1];                                                                                 // the command
    char *pointer;                                                                                      // the variables that checks the architecture of the computer
    double ad;                                                                                          // the number express in double
    float af;                                                                                           // the number express in float
    float exponent;                                                                                     // the exponent of the number
    int bigEndian;                                                                                      // the flag that rappresents the architecture of the computer
    int flag;                                                                                           // the flag that regulates the exit
    long double ald;                                                                                    // the number express in long double

    flag = 1;                                                                                           // 00000000 00000000 00000000 00000001
    pointer = (char *) &flag;                                                                           // 0 (00000000) if Big Endian, 1 (00000001) if Little Endian
    if(pointer[0] == 1) {                                                                               // if that checks the architecture of the computer
        bigEndian = FALSE;
    } else {
        bigEndian = 1;
    }
    for(flag = 0; flag == FALSE;) {                                                                     // loop
        if(stricmp(string, "No") == 0) {                                                                // if that checks the user's command
            flag = 1;
            continue;
        }
        fprintf(stdout, "Enter the number according to the scientific notation:\nNumber: ");
        fscanf(stdin, "%f", &af);
        fprintf(stdout, "Base: 10\nExponent: ");
        fscanf(stdin, "%f", &exponent);
        ad = (double) af;
        ald = (long double) af;
        af = af * powf((float) 10, exponent);
        ad = ad * pow((double) 10, (double) exponent);
        ald = ald * powl((long double) 10, (long double) exponent);
        fprintf(stdout, "The architecture is %s\n", bigEndian == 1 ? "Big Endian" : "Little Endian");
        __mingw_fprintf(stdout, "The three variables are:\n\tad: %lf\n\taf: %f\n\tald: %Lf\n", ad, af, ald);
        fprintf(stdout, "The dimension of the three variables is:\n\tad: %d\n\taf: %d\n\tald: %d\n", sizeof(ad), sizeof(af), sizeof(ald));
        fprintf(stdout, "The hexadecimal code of the three variables is:\n\tad: ");
        print((void *) &ad, sizeof(ad), bigEndian);
        fprintf(stdout, "\taf: ");
        print((void *) &af, sizeof(af), bigEndian);
        fprintf(stdout, "\tald: ");
        print((void *) &ald, sizeof(ald), bigEndian);
        fprintf(stdout, "Insert \"Yes\" or \"No\"\nDo you want continue ? > ");
        fscanf(stdin, "%s", string);
    }
    return 0;
}

void print(void *pointer, int size, int bigEndian) {
    int i;                                              // the index

    if(bigEndian == 1) {                                // if that checks the architecture of the computer
        for(i = 0; i < size; i++) {                     // cycling on the pointer
            if(i == size - 1) {                         // if that checks if the index is equal to size - 1
                fprintf(stdout, "%p", pointer + i);
            } else {
                fprintf(stdout, "%p ", pointer + i);
            }
        }
    } else {
        for(i = size - 1; i >= 0; i--) {                // cycling on the pointer
            if(i == 0) {                                // if that checks if the index is equal to 0
                fprintf(stdout, "%p", pointer + i);
            } else {
                fprintf(stdout, "%p ", pointer + i);
            }
        }
    }
    fprintf(stdout, "\n");
}