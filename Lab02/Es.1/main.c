#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define  MAX 50

typedef struct {
    int area;                       // the area of the rectangle
    int base;                       // the base of the rectangle
    int height;                     // the height of the rectangle
    int x, y;                       // the coordinates of the superior left extreme of the matrix
} rectangle, *Rectangle;

void read(int ***matrix, int *row, int *column);
Rectangle region(int **matrix, int row, int column);

int main() {
    int **matrix;                                                                                   // the matrix
    int row;                                                                                        // the number of the row of the matrix
    int column;                                                                                     // the number of the column of the matrix
    int i;
    Rectangle rect;                                                                                 // the vector of rectangle

    read(&matrix, &row, &column);
    rect = region(matrix, row, column);
    for (i = 0; i < 3; i++) {                                                                       // cycle on the vector of rectangle
        fprintf(stdout, "Max %s:\n\tSuperior Left Extreme = <%d,%d>\n\tBase = %d\n\tHeight = %d\n\tArea = %d\n", i == 0 ? "Base" : (i == 1 ? "Altezza" : "Area"),rect[i].x, rect[i].y, rect[i].base, rect[i].height, rect[i].area);
    }
    return 0;
}

void read(int ***matrix, int *row, int * column) {
    FILE *filePointer;
    int i, j;

    filePointer = fopen("mappa.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d %d", row, column);                                              // reading the file
    assert(*row <= MAX && *column <= MAX);
    *matrix = (int **) malloc(*row * sizeof(int *));
    assert(*matrix != NULL);
    for (i = 0; i < *row; i++) {                                                            // cycle on the row of the matrix
        (*matrix)[i] = (int *) malloc(*column * sizeof(int));
        for (j = 0; j < *column; j++) {                                                     // cycle on the column of the matrix
            fscanf(filePointer, "%d", &(*matrix)[i][j]);
            assert((*matrix)[i][j] == 0 || (*matrix)[i][j] == 1);
        }
    }
    fclose(filePointer);
}

Rectangle region(int **matrix, int row, int column) {
    int i, j;                                                                        // the index of the matrix
    int k, l;                                                                        // the index of the submatrix
    int area, base, height;                                                          // the maximum area, base and height
    Rectangle rect;                                                                  // the vector of rectangle

    rect = (Rectangle) malloc(3 * sizeof(rectangle));
    area = base = height = 0;
    for (i = 0; i < row; i++) {                                                      // cycle on the row of the matrix
        for (j = 0; j < column; j++) {                                               // cycle on the column of the matrix
            if(matrix[i][j] == 1) {
                for (k = 0, l = 0; i + k < row && matrix[i + k][j] == 1; k++) {      // cycle on the row of the submatrix
                    for (; j + l < column && matrix[i + k][j + l] == 1; l++) {       // cycle on the column of the submatrix
                        matrix[i + k][j + l] = 2;
                    }
                }
                if(l > base) {                                                       // if that checks if the base is major then the maximum base
                    rect[0].base = base = l;
                    rect[0].height = k;
                    rect[0].area = l * k;
                    rect[0].x = i;
                    rect[0].y = j;
                }
                if(k > height) {                                                     // if that checks if the height is major then the maximum height
                    rect[1].base = l;
                    rect[1].height = height = k;
                    rect[1].area = l * k;
                    rect[1].x = i;
                    rect[1].y = j;
                }
                if(l * k > area) {                                                   // if that checks if the area is major then the maximum area
                    rect[2].base = l;
                    rect[2].height = k;
                    rect[2].area = area = l * k;
                    rect[2].x = i;
                    rect[2].y = j;
                }
            }
        }
    }
    return rect;
}