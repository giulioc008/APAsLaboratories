#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int minor(int a, int b);
void read(int ***matrix, int *row, int *column);

int main() {
    int **matrix;                                                             // the matrix
    int row;                                                                  // index that rappresents the number of the row of the matrix
    int column;                                                               // index that rappresents the number of the column of the matrix
    int dim;                                                                  // index that rappresents the dimension of the submatrix
    int i;                                                                    // index that is used to cycling on the row of the matrix
    int j;                                                                    // index that is used to cycling on the column of the matrix
    int k;                                                                    // index that is used to cycling on the row of the submatrix
    int l;                                                                    // index that is used to cycling on the column of the submatrix
    int limits_row;                                                           // index that rappresents the limits of the index used for cycling on the row of the matrix
    int limits_column;                                                        // index that rappresents the limits of the index used for cycling on the column of the matrix
    int max;                                                                  // index that rappresents the maximum sum of the element of the submatrix
    int sum;                                                                  // index that rappresents the sum of the element of the submatrix
    int r, c;                                                                 // index that marks the start of the submatrix

    read(&matrix, &row, &column);
    max = r = c = 0;
    for(dim = 1; dim > 0 && dim < minor(row, column) + 1;) {                  // cycle with termination dim minor of 0 or dim major of the minor between row and column
        fprintf(stdout, "\nInsert the dimension of the submatrix: ");
        fscanf(stdin, "%d", &dim);                                            // acquisition of the dimension of the submatrix
        if (dim < 0 && dim > minor(row, column) + 1) {                        // if that checks if dim is major of 0 and less than equal of the minor between row and column
            break;
        }
        limits_row = limits_column = minor(row, column) - dim + 1;
        if(minor(row, column) == row) {
            limits_column += column - row;
        } else {
            limits_row += row - column;
        }
        for(i = 0; i < limits_row; i++) {                                     // cycle on the row of the matrix
            for(j = 0; j < limits_column; j++) {                              // cycle on the column of the matrix
                for(sum = k = 0; k < dim; k++) {                              // cycle on the row of the submatrix
                    for(l = 0; l < dim; l++) {                                // cycle on the column of the submatrix
                        if(l != dim - 1) {                                    // if that checks if the index l is equal to the dimension of the submatrix minus one
                            fprintf(stdout, "%d ", matrix[i + k][j + l]);
                        } else {
                            fprintf(stdout, "%d", matrix[i + k][j + l]);
                        }
                        sum += matrix[i + k][j + l];
                    }
                    if (k != dim - 1) {                                        // if that checks if the index k is equal to the dimension of the submatrix minus one
                        fprintf(stdout, "\n");
                    }
                }
                fprintf(stdout, "\n\n");
                if(sum > max) {                                                // if that checks if the submatrix has the sum of the elements that is maximum
                    max = sum;
                    r = i;
                    c = j;
                }
            }
        }
        fprintf(stdout, "The submatrix with the maximum sum is:\n");
        for(i = r; i < r + dim; i++) {                                        // cycle on the row of the matrix
            for(j = c; j < c + dim; j++) {                                    // cycle on the column of the matrix
                if (j != c + dim - 1) {                                       // if that checks if the index j is equal to the dimension of the submatrix minus one
                    fprintf(stdout, "%d ", matrix[i][j]);
                } else {
                    fprintf(stdout, "%d", matrix[i][j]);
                }
            }
            if (i != r + dim - 1) {                                           // if that checks if the index i is equal to the dimension of the submatrix minus one
                fprintf(stdout, "\n");
            }
        }
    }
    return 0;
}

int minor(int a, int b) {
    if(a < b) {         // if that checks if a is minor of b
        return a;
    }
    return b;
}

void read(int ***matrix, int *row, int *column) {
    char fileName[20];
    FILE *filePointer;
    int i, j;

    fprintf(stdout, "\n--- The program acquires data ---\nInsert the name of the file: ");
    fscanf(stdin, "%s", fileName);                                                          // acquisition of the name of the file
    filePointer = fopen(fileName, "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d %d", row, column);                                              // reading the file
    *matrix = (int **) malloc(*row * sizeof(int *));
    for (i = 0; i < *row; i++) {                                                            // cycle on the row of the matrix
        (*matrix)[i] = (int *) malloc(*column * sizeof(int));
        for (j = 0; j < *column; j++) {                                                     // cycle on the column of the matrix
            fscanf(filePointer, "%d", &(*matrix)[i][j]);
        }
    }
    fclose(filePointer);
}