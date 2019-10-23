#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

typedef enum {
    sapphire,
    ruby,
    topaz,
    emerald,
    error
} stone;                                                                                                                // the type of the stone

int check(int stones, int possibilities);
void deallocMatrix(int *****vector, int *mark);
int *****mallocMatrix(int *mark);
int provisionsWithRepetition(int *sol, int n, int pos, int *mark, int *****vector);

int main() {
    FILE *filePointer;                                                                                                  // the file
    int *****vector;                                                                                                    // the struct used for the memoization paradigm
    int *solution;                                                                                                      // the vector of the solution
    int i;                                                                                                              // the indexes
    int maximumLength;                                                                                                  // the maximum value of length
    int length;                                                                                                         // the length of the necklace
    int *mark;                                                                                                          // the vector of the occurrences

    mark = (int *) malloc(error * sizeof(int));
    assert(mark != NULL);
    filePointer = fopen("e1_test_set_easy.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%*d");                                                                                         // reading the file
    for (; feof(filePointer) == FALSE;) {                                                                               // cycle on the file
        for (i = 0; i < error; i++) {                                                                                   // cycle on the vector of the occurrence
            fscanf(filePointer, "%d", &mark[i]);
        }
        for (i = maximumLength = 0; i < error; i++) {                                                                   // cycle on the vector of the occurrence
            maximumLength += mark[i];
        }
        solution = (int *) malloc(maximumLength * sizeof(int));
        assert(solution != NULL);
        vector = mallocMatrix(mark);
        fprintf(stdout, "Sum: %d\t\t", maximumLength);
        for (i = 1, length = 0; i < maximumLength + 1; i++) {                                                           // cycle on the value of length
            length = provisionsWithRepetition(solution, error, 0, mark, vector);
        }
        fprintf(stdout, "The necklace with the maximum length is long %d\n", length);
        free(solution);
        deallocMatrix(vector, mark);
    }
    fclose(filePointer);
    return 0;
}

int check(int stones, int possibilities) {
    switch(stones) {                                                                                                    // switch that checks the type of the stone
        case sapphire:
        case topaz:
            switch(possibilities) {                                                                                     // switch that checks the type of the stone
                case sapphire:
                case ruby:
                    return 1;
                default:
                    break;
            }
            break;
        case ruby:
        case emerald:
            switch(possibilities) {                                                                                     // switch that checks the type of the stone
                case emerald:
                case topaz:
                    return 1;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return FALSE;
}
void deallocMatrix(int *****vector, int *mark) {
    int i, j, k, l;                                                                                                     // the indexes

    for (i = 0; i < error; i++) {                                                                                       // cycle on the first dimension
        for (j = 0; j < mark[sapphire] + 1; j++) {                                                                      // cycle on the second dimension
            for (k = 0; k < mark[ruby] + 1; k++) {                                                                      // cycle on the third dimension
                for (l = 0; l < mark[topaz] + 1; l++) {                                                                 // cycle on the fourth dimension
                    free(vector[i][j][k][l]);
                }
                free(vector[i][j][k]);
            }
            free(vector[i][j]);
        }
        free(vector[i]);
    }
    free(vector);
}
int *****mallocMatrix(int *mark) {
    int i, j, k, l;                                                                                                     // the indexes
    int *****vector;                                                                                                    // the matrix in five dimension

    vector = (int *****) calloc(error, sizeof(int ****));
    assert(vector != NULL);
    for (i = 0; i < error; i++) {                                                                                       // cycle on the first dimension
        vector[i] = (int ****) calloc(mark[sapphire] + 1, sizeof(int ***));
        assert(vector[i] != NULL);
        for (j = 0; j < mark[sapphire] + 1; j++) {                                                                      // cycle on the second dimension
            vector[i][j] = (int ***) calloc(mark[ruby] + 1, sizeof(int **));
            assert(vector[i][j] != NULL);
            for (k = 0; k < mark[ruby] + 1; k++) {                                                                      // cycle on the third dimension
                vector[i][j][k] = (int **) calloc(mark[topaz] + 1, sizeof(int *));
                assert(vector[i][j][k] != NULL);
                for (l = 0; l < mark[topaz] + 1; l++) {                                                                 // cycle on the fourth dimension
                    vector[i][j][k][l] = (int *) calloc(mark[emerald] + 1, sizeof(int));
                    assert(vector[i][j][k][l] != NULL);
                }
            }
        }
    }
    return vector;
}
int provisionsWithRepetition(int *sol, int n, int pos, int *mark, int *****vector) {
    int i;                                                                                                              // the index                                                                                                              // the index
    int length;                                                                                                         // the length
    int maximumLength;                                                                                                  // the maximum length

    maximumLength = 0;
    for (i = 0; i < n; i++) {                                                                                           // cycle on the stone
        if(mark[i] > 0) {                                                                                               // if that checks the occurrences of the stone
            if (pos == 0 || check(sol[pos - 1], i) != FALSE) {                                                          // if that checks the particular case and execute the pruning (checks if the stone to set is legal)
                mark[i]--;
                sol[pos] = i;
                if(vector[sol[pos]][mark[sapphire]][mark[ruby]][mark[topaz]][mark[emerald]] > 0) {                      // if that checks the memoization
                    length = vector[sol[pos]][mark[sapphire]][mark[ruby]][mark[topaz]][mark[emerald]] - 1;
                } else {
                    length = provisionsWithRepetition(sol, n, pos + 1, mark, vector);                                   // recursion
                    vector[sol[pos]][mark[sapphire]][mark[ruby]][mark[topaz]][mark[emerald]] = length;                  // memoization
                }
                if(length > maximumLength) {                                                                            // if that checks the maximum length
                    maximumLength = length;
                }
                mark[i]++;                                                                                              // backtrack
            }
        }
    }
    return maximumLength + 1;
}