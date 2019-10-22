#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int length, *v;
} vector, *Vector;

void dealloc(Vector v);
void execute(vector v);
void read(Vector v);

int main() {
    vector v;

    v.length = 0;
    v.v = NULL;
    read(&v);
    execute(v);
    dealloc(&v);
    return 0;
}

void dealloc(Vector v) {
    free((*v).v);
}

void execute(vector v) {
    int i;

    fprintf(stdout, "\n--- The program is executed ---\n[");
    for (i = 0; i < v.length; i++){                             // cycle on the vector
        if (v.v[i] == 0) {                                      // if that checks if the element is 0
            fprintf(stdout, "]\n[");
            continue;
        }
        fprintf(stdout, "%d", v.v[i]);
        if (i != v.length - 1 && v.v[i + 1] != 0) {             // if that checks if the index is on the last element and if the next element is 0
            fprintf(stdout, ", ");
        }
    }
    fprintf(stdout, "]");
}

void read(Vector v) {
    int i;

    fprintf(stdout, "\n--- The program acquires data ---\nInsert the dimension of the vector: ");
    fscanf(stdin, "%d", &i);                                                                            // acquisition of the length of the vector
    assert(i <= 30);
    (*v).length = i;
    (*v).v = (int *) malloc((*v).length * sizeof(int));
    assert((*v).v != NULL);
    fprintf(stdout, "Insert the element of the vector:\n");
for (i = 0; i < (*v).length; i++) {                                                                     // cycle on the vector
        fprintf(stdout, "\t%d element: ", i + 1);
        fscanf(stdin, "%d", &(*v).v[i]);                                                                // acquisition of the element of the vector
    }
}