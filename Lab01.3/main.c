#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matrixRotation(int **matrix, int row, int column, char *selector, int index, char *direction, int position);
int **read(int *row, int *column);
void rotation(int *v, int length, int P, int dir);

int main() {
    char selector[7 + 1];                                                                           // the string that specifies if the rotation must be on the row or on the column
    char direction[8 + 1];                                                                          // the string with which the user specifies the parameters
    int **matrix;                                                                                   // the matrix
    int row;                                                                                        // the number of the row of the matrix
    int column;                                                                                     // the number of the column of the matrix
    int index;                                                                                      // index of the row/column to rotate
    int position;                                                                                   // the number of positions to which the row/column must rotate

    matrix = read(&row, &column);
    do {
        fprintf(stdout, "Insert the selector (riga|colonna|fine): ");
        fscanf(stdin, "%s", selector);                                                              // acquisition of the selector
        if(strcmp(selector, "riga") != 0 && strcmp(selector, "colonna") != 0) {
            assert(strcmp(selector, "fine") == 0);
            break;
        }
        fprintf(stdout, "Insert the parameters with the format <index> (> 0) <direction> (sinistra|destra / su|giu) <position> (> 0): ");
        fscanf(stdin, "%d %s %d", &index, direction, &position);                                    // acquisition of the other parameters
        assert(index > 0);
        assert(strcmp(direction, "sinistra") == 0 || strcmp(direction, "destra") == 0 || strcmp(direction, "su") == 0 || strcmp(direction, "giu") == 0);
        assert(position > 0);
        assert((strcmp(selector, "riga") == 0 && (strcmp(direction, "sinistra") == 0 || strcmp(direction, "destra") == 0)) || (strcmp(selector, "colonna") == 0 && (strcmp(direction, "su") != 0 || strcmp(direction, "giu") != 0)));
        index--;
        if (strcmp(selector, "riga") == 0) {                                                        // if that checks the selector
            if(index > row) {
                index = index % row;
            }
            if(position > row) {
                position = position % row;
            }
        } else {
            if(index > column) {
                index = index % column;
            }
            if(position > column) {
                position = position % column;
            }
        }
        matrixRotation(matrix, row, column, selector, index, direction, position);
        fprintf(stdout, "\n\n--- The program acquires data ---\n");
    } while(strcmp(selector, "fine") != 0);                                                         // cycle with termination selector equal to "fine"
    return 0;
}

void matrixRotation(int **matrix, int row, int column, char *selector, int index, char *direction, int position) {
    int i, j, dir;
    int *v;                                                                                         // the auxiliary vector

    if ((strcmp(selector, "riga") == 0 && strcmp(direction, "destra") == 0) ||
        (strcmp(selector, "colonna") == 0 && strcmp(direction, "su") == 0)) {                       // if that checks the selector and the direction
        dir = -1;
    } else {
        dir = 1;
    }
    fprintf(stdout, "\n--- The program is executed ---\n\tThe matrix before the rotation:\n");
    for (i = 0; i < row; i++) {                                                                     // cycle on the row of the matrix
        fprintf(stdout, "\t\t");
        for (j = 0; j < column; j++) {                                                              // cycle on the column of the matrix
            if (j == column - 1) {                                                                  // if that checks if the index is on the last column
                fprintf(stdout, "%d", matrix[i][j]);
            } else {
                fprintf(stdout, "%d ", matrix[i][j]);
            }
        }
        fprintf(stdout, "\n");
        if (i == row - 1) {                                                                         // if that checks if the index is on the last row
            fprintf(stdout, "\n");
        }
    }
    if (strcmp(selector, "riga") == 0) {                                                            // if that checks the selector
        rotation(matrix[index], column, position, dir);
    } else {
        v  = (int *) malloc(row * sizeof(int));
        for(i = 0; i < row; i++) {                                                                  // cycle on the column of the matrix
            v[i] = matrix[i][index];
        }
        rotation(v, row, position, dir);
        for(i = 0; i < row; i++) {                                                                  // cycle on the index column of the matrix
            matrix[i][index] = v[i];
        }
    }
    fprintf(stdout, "\n\tThe matrix after the rotation:\n");
    for (i = 0; i < row; i++) {                                                                     // cycle on the row of the matrix
        fprintf(stdout, "\t\t");
        for (j = 0; j < column; j++) {                                                              // cycle on the column of the matrix
            if (j == column - 1) {                                                                  // if that checks if the index is on the last column
                fprintf(stdout, "%d", matrix[i][j]);
            } else {
                fprintf(stdout, "%d ", matrix[i][j]);
            }
        }
        fprintf(stdout, "\n");
        if (i == row - 1) {                                                                         // if that checks if the index is on the last row
            fprintf(stdout, "\n");
        }
    }
}

int **read(int *row, int * column) {
    char fileName[20 + 1];
    FILE *filePointer;
    int i, j;
    int **matrix;

    fprintf(stdout, "\n--- The program acquires data ---\nInsert the name of the file: ");
    fscanf(stdin, "%s", fileName);                                                          // acquisition of the name of the file
    filePointer = fopen(fileName, "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d %d", row, column);                                              // reading the file
    assert(*row <= 30 && *column <= 30);
    matrix = (int **) malloc(*row * sizeof(int *));
    assert(matrix != NULL);
    for (i = 0; i < *row; i++) {                                                            // cycle on the row of the matrix
        matrix[i] = (int *) malloc(*column * sizeof(int));
        for (j = 0; j < *column; j++) {                                                     // cycle on the column of the matrix
            fscanf(filePointer, "%d", &matrix[i][j]);
        }
    }
    fclose(filePointer);
    return matrix;
}

void rotation(int *v, int length, int P, int dir) {
    int i, j, k, x;

    if (dir == -1) {                                                                        // if that checks the direction
        P = length - P;
    }
    for (k = i = 0; k < length; i++, k++) {                                                 // cycle on the vector
        x = v[i];
        for (j = i; (j + P) % length != i; j = (j + P) % length, k++) {                     // cycle on the part of the vector that starts at the i-th position
            v[j] = v[(j + P) % length];
        }
        v[j] = x;
    }
}