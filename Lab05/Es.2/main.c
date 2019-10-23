#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FLAG

void allocMatrixP(int ***matrix, int *row, int *column);
int **allocMatrixR(int *row, int *column);
void split(int **matrix, int row, int column, int *white, int *black);

int main() {
    int row;                                                                    // the row of the matrix
    int column;                                                                 // the column of the matrix
    int **matrix;                                                               // the matrix
    int *white;                                                                 // the vector that contains the white cells
    int *black;                                                                 // the vector that contains the black cells
    int i, j;                                                                   // the indexes

#ifdef FLAG
    matrix = allocMatrixR(&row, &column);
#else
    allocMatrixP(&matrix, &row, &column);
#endif
    white = (int *) malloc(column * row / 2 * sizeof(int));
    assert(white != NULL);
    black = (int *) malloc(column * row / 2 * sizeof(int));
    assert(black != NULL);
    split(matrix, row, column, white, black);
    fprintf(stdout, "Matrix:\n");
    for(i = 0; i < row; i++) {                                                  // cycle on the row of the matrix
        for(j = 0; j < column; j++) {                                           // cycle on the column of the matrix
            if(j == column - 1) {                                               // if that checks if the index is on the last column
                fprintf(stdout, "%d", matrix[i][j]);
            } else if(j == 0) {                                                 // if that checks if the index is on the first column
                fprintf(stdout, "\t%d ", matrix[i][j]);
            } else {
                fprintf(stdout, "%d ", matrix[i][j]);
            }
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "White Cells:\n");
    for(i = 0; i < column * row / 2; i++) {                                     // cycle on the vector
        if(i == column * row / 2 - 1) {                                         // if that checks if the index is on the last cell
            fprintf(stdout, "%d\n", white[i]);
        } else if(i == 0) {                                                     // if that checks if the index is on the first cell
            fprintf(stdout, "\t%d ", white[i]);
        } else {
            fprintf(stdout, "%d ", white[i]);
        }
    }
    fprintf(stdout, "\nBlack Cells:\n");
    for(i = 0; i < column * row / 2; i++) {                                     // cycle on the vector
        if(i == column * row / 2 - 1) {                                         // if that checks if the index is on the last cell
            fprintf(stdout, "%d\n", black[i]);
        } else if(i == 0) {                                                     // if that checks if the index is on the first cell
            fprintf(stdout, "\t%d ", black[i]);
        } else {
            fprintf(stdout, "%d ", black[i]);
        }
    }
    free(white);
    free(black);
    for(i = 0; i < row; i++) {                                                  // cycle on the row of the matrix
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}

void allocMatrixP(int ***matrix, int *row, int *column) {
    int i, j;                                                       // the indexes of the matrix
    FILE *filePointer;                                              // the file

    filePointer = fopen("example.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d %d", row, column);                      // reading the file
    *matrix = (int **) malloc(*row * sizeof(int *));
    assert(*matrix != NULL);
    for(i = 0; i < *row; i++) {                                     // cycle on the row of the matrix
        (*matrix)[i] = (int *) malloc(*column * sizeof(int));
        assert((*matrix)[i] != NULL);
        for(j = 0; j < *column; j++) {                              // cycle on the column of the matrix
            fscanf(filePointer, "%d", &(*matrix)[i][j]);
        }
    }
    fclose(filePointer);
}
int **allocMatrixR(int *row, int *column) {
    int **matrix;                                                   // the matrix
    int i, j;                                                       // the indexes of the matrix
    FILE *filePointer;                                              // the file

    filePointer = fopen("example.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d %d", row, column);                      // reading the file
    matrix = (int **) malloc(*row * sizeof(int *));
    assert(matrix != NULL);
    for(i = 0; i < *row; i++) {                                     // cycle on the row of the matrix
        matrix[i] = (int *) malloc(*column * sizeof(int));
        assert(matrix[i] != NULL);
        for(j = 0; j < *column; j++) {                              // cycle on the column of the matrix
            fscanf(filePointer, "%d", &matrix[i][j]);
        }
    }
    fclose(filePointer);
    return matrix;
}
void split(int **matrix, int row, int column, int *white, int *black) {
    int i, j;                                                              // the indexes
    int k, l;                                                              // the indexes

    for(i = k = l = 0; i < row; i++) {                                     // cycle on the row of the matrix
        switch (i % 2) {
            case 0:
                for(j = 0; j < column; j++) {                              // cycle on the column of the matrix
                    white[l++] = matrix[i][j];
                    if(++j < column) {
                        black[k++] = matrix[i][j];
                    }
                }
                break;
            case 1:
                for(j = 0; j < column; j++) {                              // cycle on the column of the matrix
                    black[k++] = matrix[i][j];
                    if(++j < column) {
                        white[l++] = matrix[i][j];
                    }
                }
                break;
            default:
                fprintf(stderr, "\tFatal Error");
                return;
        }
    }

}