#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *v;
    int length;
} vector, *Vector;
typedef struct {
    int length;
    Vector v;
} sequence, *Sequence;

void InsertionSort(int *A, int l, int r, int *externalIteration, int *internalIteration, int *exchange);
sequence read();
void SelectionSort(int *A, int l, int r, int *externalIteration, int *internalIteration, int *exchange);
void ShellSort(int *A, int l, int r, int *externalIteration, int *internalIteration, int *exchange);

int main() {
    int i;                                                                                                                  // the index
    int externalIteration;                                                                                                  // the counter for the external iteration
    int internalIteration;                                                                                                  // the counter for the internal iteration
    int exchange;                                                                                                           // the counter for the exchange
    sequence seq;                                                                                                           // the sequence

    seq = read();
    fprintf(stdout, "InsertionSort:\n");
    for(i = 0; i < seq.length; i++) {                                                                                       // cycling on the sequence
        externalIteration = exchange = internalIteration = 0;
        InsertionSort(seq.v[i].v, 0, seq.v[i].length - 1, &externalIteration, &internalIteration, &exchange);
        fprintf(stdout, "\t%d-th vector:\n\t\tThe number of exchange is: %d\n\t\tThe number of external iteration is: %d\n", i + 1 , exchange, externalIteration);
        fprintf(stdout, "\t\tThe number of internal iteration is: %d\n\t\tThe number of interation (external + internal) is: %d\n", internalIteration , externalIteration + internalIteration);
    }
    seq = read();
    fprintf(stdout, "SelectionSort:\n");
    for(i = 0; i < seq.length; i++) {                                                                                       // cycling on the sequence
        externalIteration = exchange = internalIteration = 0;
        SelectionSort(seq.v[i].v, 0, seq.v[i].length - 1, &externalIteration, &internalIteration, &exchange);
        fprintf(stdout, "\t%d-th vector:\n\t\tThe number of exchange is: %d\n\t\tThe number of external iteration is: %d\n", i + 1 , exchange, externalIteration);
        fprintf(stdout, "\t\tThe number of internal iteration is: %d\n\t\tThe number of interation (external + internal) is: %d\n", internalIteration , externalIteration + internalIteration);
    }
    seq = read();
    fprintf(stdout, "ShellSort:\n");
    for(i = 0; i < seq.length; i++) {                                                                                       // cycling on the sequence
        externalIteration = exchange = internalIteration = 0;
        ShellSort(seq.v[i].v, 0, seq.v[i].length - 1, &externalIteration, &internalIteration, &exchange);
        fprintf(stdout, "\t%d-th vector:\n\t\tThe number of exchange is: %d\n\t\tThe number of external iteration is: %d\n", i + 1 , exchange, externalIteration);
        fprintf(stdout, "\t\tThe number of internal iteration is: %d\n\t\tThe number of interation (external + internal) is: %d\n", internalIteration , externalIteration + internalIteration);
    }
    return 0;
}

void InsertionSort(int *A, int l, int r, int *externalIteration, int *internalIteration, int *exchange) {
    int i, j;                                                                                                 // the indexes
    int x;                                                                                                    // the auxiliary element

    for(i = l + 1; i <= r; i++, (*externalIteration)++) {                                                     // cycling on the vector
        x = A[i];
        for(j = i - 1; j >= l && x < A[j]; j--, (*exchange)++, (*internalIteration)++) {                      // cycling on the subvector that ends at the (i - 1)-th positions
            A[j + 1] = A[j];
        }
        A[j + 1] = x;
    }
}
sequence read() {
    FILE *filePointer;                                              // the file
    int i, j;                                                       // the indexes
    sequence seq;                                                   // the sequence

    filePointer = fopen("sort.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d", &seq.length);                         // reading the file
    seq.v = (Vector) malloc(seq.length * sizeof(vector));
    for(i = 0; i < seq.length; i++) {                               // cycling on the sequence
        fscanf(filePointer, "%d", &seq.v[i].length);
        seq.v[i].v = (int *) malloc(seq.v[i].length * sizeof(int));
        for(j = 0; j < seq.v[i].length; j++) {                      // cycling on the vector
            fscanf(filePointer, "%d", &seq.v[i].v[j]);
        }

    }
    fclose(filePointer);
    return seq;
}
void SelectionSort(int *A, int l, int r, int *externalIteration, int *internalIteration, int *exchange) {
    int i, j;                                                                      // the indexes
    int min;                                                                       // the minimum of the subvector
    int x;                                                                         // the auxiliary element

    for(i = l; i < r; i++, (*externalIteration)++) {                               // cycling on the vector
        min = i;
        for(j = i + 1; j <= r; j++, (*internalIteration)++){                       // cycling on the subvector that starts at the (i + 1)-th positions
            if(A[j] < A[min]) {                                                    // if that checks if the element si the minimum of the subvector
                min = j;
            }
        }
        if(min != i) {                                                             // if that checks if the minimum of the subvector isn't the starts of the subvector
            x = A[i];
            A[i] = A[min];
            A[min] = x;
            (*exchange)++;
        }
    }
}
void ShellSort(int *A, int l, int r, int *externalIteration, int *internalIteration, int *exchange) {
    int i, j;                                                                                   // the indexes
    int h;                                                                                      // the index of the Knuth sequence
    int n;                                                                                      // the limit of the Knuth sequence
    int x;                                                                                      // the auxiliary element
    int counter;                                                                                // the counter

    n = r - l;
    counter = 0;
    for(h = 1; h < n / 3; h = 3 * h + 1);                                                       // calculation of the Knuth sequence
    for(; h >= 1; h = h / 3, *externalIteration += counter, counter = 0) {                      // cycling on the vector
        for(i = l + h; i <= r; i++) {                                                           // application of the Insertion Sort on the vector
            counter++;
            x = A[i];
            for(j = i; j >= l + h && x < A[j - h]; j -= h, (*exchange)++, (*internalIteration)++) {
                A[j] = A[j - h];
            }
            A[j] = x;
        }
    }
}