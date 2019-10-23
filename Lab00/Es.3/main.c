#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define maxN 30

typedef struct {
    int length, *v;
} vector, *Vector;

void dealloc(Vector v);
void read(Vector v);
void rotation(vector v, int P, int dir);

int main() {
    vector v;
    int P, dir;

    v.length = 0;
    v.v = NULL;
    read(&v);
    do {
        fprintf(stdout, "Insert the position number for which the vector is to be rotated (it must be != 0): ");
        fscanf(stdin, "%d", &P);                                                                                    // acquisition of the number of positions to which the vector must rotate
    if (P >= v.length) {                                                                                            // if that checks if P is major of the length of the vector
            P = P % v.length;
        }
        if (P == 0) {                                                                                               // if that checks if P is 0
            break;
        }
        fprintf(stdout, "Insert the direction in which the vector is to be rotated (-1 for DX, 1 for SX): ");
        fscanf(stdin, "%d", &dir);                                                                                  // acquisition of the direction in which to rotate the vector
        assert(dir == 1 || dir == -1);
        rotation(v, P, dir);
    } while(P != 0);                                                                                                // cycle with termination P equal to 0
    dealloc(&v);
    return 0;
}

void dealloc(Vector v) {
    free((*v).v);
}

void read(Vector v) {
    int i;

    fprintf(stdout, "\n--- The program acquires data ---\nInsert the dimension of the vector: ");
    fscanf(stdin, "%d", &i);                                                                        // acquisition of the length of the vector
    assert(i <= maxN);
    (*v).length = i;
    (*v).v = (int *) malloc((*v).length * sizeof(int));
    assert((*v).v != NULL);
    fprintf(stdout, "Insert the element of the vector:\n");
    for (i = 0; i < (*v).length; i++) {                                                             // cycle on the vector
        fprintf(stdout, "\t%d element: ", i + 1);
        fscanf(stdin, "%d", &(*v).v[i]);                                                            // acquisition of the element of the vector
    }
}

void rotation(vector v, int P, int dir) {
    int i, j, k, x;

    if (dir == -1) {                                                                            // if that checks the direction
        P = v.length - P;
    }
    fprintf(stdout, "\n--- The program is executed ---\nThe vector before the rotation:\n\t[");
    for (i = 0; i < v.length; i++) {                                                            // cycle on the vector
        if (i == v.length - 1) {                                                                // if that checks if the index is on the last element
            fprintf(stdout, "%d]\n", v.v[i]);
        } else {
            fprintf(stdout, "%d, ", v.v[i]);
        }
    }
    fprintf(stdout, "\nThe vector after the rotation:\n\t[");
    for (k = i = 0; k < v.length; i++, k++) {                                                   // cycle on the vector
        x = v.v[i];
        for (j = i; (j + P) % v.length != i; j = (j + P) % v.length, k++) {                     // cycle on the part of the vector that starts at the i-th position
            v.v[j] = v.v[(j + P) % v.length];
        }
        v.v[j] = x;
    }
    for (i = 0; i < v.length; i++) {                                                            //cycle on the vector
        if (i == v.length - 1) {                                                                // if that checks if the index is on the last element
            fprintf(stdout, "%d]\n\n", v.v[i]);
        } else {
            fprintf(stdout, "%d, ", v.v[i]);
        }
    }
    fprintf(stdout, "--- The program acquires data ---\n");
}