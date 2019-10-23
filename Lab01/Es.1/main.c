#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void read(int ***matrix, int *row, int *column);

int main() {
    int **matrix;                                              // the matrix
    int row;                                                   // index that rappresents the number of the row of the matrix
    int column;                                                // index that rappresents the number of the column of the matrix
    int i;                                                     // index that is used to cycling on the row of the matrix
    int j;                                                     // index that is used to cycling on the column of the matrix
    int *points;                                               // the vector of the points
    int max;                                                   // index that rappresents the maximum score
    int k;                                                     // index that rappresents the index of the capolista

    read(&matrix, &row, &column);
    fprintf(stdout, "\n--- The program is executed ---\n");
    points = (int *) calloc(row, sizeof(int));
    for(j = 0; j < column; j++) {                               // cycle on the column of the matrix
        for(i = max = k = 0; i < row; i++) {                    // cycle on the row of the matrix
            points[i] += matrix[i][j];
            if(matrix[i][j] > max) {
                max = matrix[i][j];
                k = i;
            }
        }
        fprintf(stdout, "\tThe leaders of the %d day is the %d team\n", j + 1, k + 1);
    }
    for(i = max = k = 0; i < row; i++) {                        // cycle on the vector points
        if(points[i] > max) {
            max = points[i];
            k = i;
        }
    }
    fprintf(stdout, "\n\tThe global leaders is the %d team", k + 1);
    return 0;
}

void read(int ***matrix, int *row, int *column) {
    FILE *filePointer;
    int i, j;

    fprintf(stdout, "--- The program acquires data ---\n\n");
    filePointer = fopen("example.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d %d", row, column);                       // reading the file
    *matrix = (int **) malloc(*row * sizeof(int *));
    for (i = 0; i < *row; i++) {                                     // cycle on the row of the matrix
        (*matrix)[i] = (int *) malloc(*column * sizeof(int));
        for (j = 0; j < *column; j++) {                              // cycle on the column of the matrix
            fscanf(filePointer, "%d", &(*matrix)[i][j]);
        }
    }
    fclose(filePointer);
}