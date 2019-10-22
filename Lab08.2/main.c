#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0

typedef enum {
    horizontal,
    vertical,
    error
} position;                                                                                                             // the position of the pipe
typedef struct {
    int points;
    char colour;
} pipe;                                                                                                                 // the pipe
typedef struct {
    int fixed;
    pipe pipes[error];
} cell, *Cell;                                                                                                          // the tile
typedef struct {
    Cell vector;
    int numberOfCell;
} log, *Log;                                                                                                            // the struct
typedef struct {
    Cell *matrix;
    int row, column;
} board;                                                                                                                // the board

board readBoard(Log logging);
log readTiles();
int score(board chessboard);
void simpleProvisions(int *sol, int *finalSol, int *mark, int n, int pos, board chessboard, log logging, int *maximumPoints);

int main() {
    board chessboard;                                                                                                   // the board
    int *mark;                                                                                                          // the vector of the mark
    int *solution;                                                                                                      // the solution
    int *finalSolution;                                                                                                 // the optimal solution
    int i, j, k;                                                                                                        // the indexes
    int maximumPoints;                                                                                                  // the maximum points of the chessboard
    log logging;                                                                                                        // the struct

    logging = readTiles();
    chessboard = readBoard(&logging);
    mark = (int *) calloc(logging.numberOfCell, sizeof(int));
    assert(mark != NULL);
    solution = (int *) malloc(logging.numberOfCell * sizeof(int));
    assert(solution != NULL);
    finalSolution = (int *) malloc(logging.numberOfCell * sizeof(int));
    assert(finalSolution != NULL);
    maximumPoints = 0;
    simpleProvisions(solution, finalSolution, mark, logging.numberOfCell, 0, chessboard, logging, &maximumPoints);
    fprintf(stdout, "The solution that maximize the chessboard is:\n");
    for (i = k = 0; i < chessboard.row; i++) {                                                                          // cycle on the row
        fprintf(stdout, "\t");
        for (j = 0; j < chessboard.column; j++) {                                                                       // cycle on the column
            if(chessboard.matrix[i][j].fixed != FALSE) {                                                                 // if that checks if the cell is empty
                fprintf(stdout, "(%c %d, %c %d) ", chessboard.matrix[i][j].pipes[horizontal].colour, chessboard.matrix[i][j].pipes[horizontal].points, chessboard.matrix[i][j].pipes[vertical].colour, chessboard.matrix[i][j].pipes[vertical].points);
            } else {
                fprintf(stdout, "(%c %d, %c %d) ", logging.vector[finalSolution[k]].pipes[horizontal].colour, logging.vector[finalSolution[k]].pipes[horizontal].points, logging.vector[finalSolution[k]].pipes[vertical].colour, logging.vector[finalSolution[k]].pipes[vertical].points);
                k++;
            }
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\nThe points are %d", maximumPoints);
    free(solution);
    free(finalSolution);
    free(mark);
    for (i = 0; i < chessboard.row; i++) {                                                                              // cycle on the row
        for (j = 0; j < chessboard.column; j++) {                                                                       // cycle on the column
            free(chessboard.matrix[i][j].pipes);
        }
        free(chessboard.matrix[i]);
    }
    free(chessboard.matrix);
    for (i = 0; i < logging.numberOfCell; i++) {                                                                        // cycle on the cells
        free(logging.vector[i].pipes);
    }
    free(logging.vector);
    return 0;
}

board readBoard(Log logging) {
    board chessboard;                                                                                                   // the board
    FILE *filePointer;                                                                                                  // the file
    int i, j;                                                                                                           // the indexes
    int index;                                                                                                          // the auxiliary int
    int rotation;                                                                                                       // the flag that indicates if the cell

    filePointer = fopen("board.txt", "r");
    fscanf(filePointer, "%d %d", &chessboard.row, &chessboard.column);                                                  // reading the file
    chessboard.matrix = (Cell *) malloc(chessboard.row * sizeof(Cell));
    assert(chessboard.matrix != NULL);
    for (i = 0; i < chessboard.row; i++) {                                                                              // cycle on the row
        chessboard.matrix[i] = (Cell) malloc(chessboard.column * sizeof(cell));
        assert(chessboard.matrix[i] != NULL);
        for (j = 0; j < chessboard.column; j++) {                                                                       // cycle on the column
            fscanf(filePointer, "%d/%d", &index, &rotation);
            chessboard.matrix[i][j].fixed = FALSE;
            if(index != -1 && rotation != -1) {                                                                         // if that checks if the cell must be empty
                if(rotation == 1) {                                                                                     // if that checks if the tile must be rotated
                    chessboard.matrix[i][j].pipes[horizontal] = logging->vector[index].pipes[vertical];
                    chessboard.matrix[i][j].pipes[vertical] = logging->vector[index].pipes[horizontal];
                } else {
                    chessboard.matrix[i][j] = logging->vector[index];
                }
                chessboard.matrix[i][j].fixed = 1;
            }
        }
    }
    rewind(filePointer);
    fscanf(filePointer, "%*d %*d");                                                                                     // reading the file
    for (i = j = 0; i < chessboard.row * chessboard.column; i++) {                                                      // cycle on the matrix
        fscanf(filePointer, "%d/%*d", &index);
        if(index != -1) {                                                                                               // if that checks if the cell must be empty
            index -= j;
            logging->numberOfCell--;
            for (rotation = index; rotation < logging->numberOfCell; rotation++) {                                      // cycle on the part of the vector that starts at the index-th position
                logging->vector[rotation] = logging->vector[rotation + 1];
            }
            j++;
        }
    }
    fclose(filePointer);
    realloc(logging->vector, logging->numberOfCell);
    return chessboard;
}
log readTiles() {
    FILE *filePointer;                                                                                                  // the file
    int i, j;                                                                                                           // the indexes
    log logging;                                                                                                        // the struct

    filePointer = fopen("tiles.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d\n", &logging.numberOfCell);                                                                 // reading the file
    logging.vector = (Cell) malloc(logging.numberOfCell * sizeof(cell));
    assert(logging.vector != NULL);
    for (i = 0; i < logging.numberOfCell; i++) {                                                                        // cycle on the cells
        for (j = 0; j < error; j++) {                                                                                   // cycle on the pipes
            fscanf(filePointer, "%c %d ", &logging.vector[i].pipes[j].colour, &logging.vector[i].pipes[j].points);
        }
    }
    fclose(filePointer);
    return logging;
}
int score(board chessboard) {
    int i, j;                                                                                                           // the indexes
    int sum;                                                                                                            // the sum of the points
    int partialSum;                                                                                                     // the sum of the points for a row

    for (i = sum = 0; i < chessboard.row; i++) {                                                                        // cycle on the row
        partialSum = chessboard.matrix[i][0].pipes[horizontal].points;
        for (j = 1; j < chessboard.column; j++) {                                                                       // cycle on the column
            if(chessboard.matrix[i][j].pipes[horizontal].colour == chessboard.matrix[i][j - 1].pipes[horizontal].colour) {           // if that checks if the colour of the j-th cell and the (j - 1)-th cell are equal
                partialSum += chessboard.matrix[i][j].pipes[horizontal].points;
            } else {
                partialSum = 0;
                break;
            }
        }
        sum += partialSum;
    }
    for (i = 0; i < chessboard.column; i++) {                                                                           // cycle on the column
        partialSum = chessboard.matrix[0][i].pipes[vertical].points;
        for (j = 1; j < chessboard.row; j++) {                                                                          // cycle on the row
            if(chessboard.matrix[j][i].pipes[vertical].colour == chessboard.matrix[j - 1][i].pipes[vertical].colour) {  // if that checks if the colour of the j-th cell and the (j - 1)-th cell are equal
                partialSum += chessboard.matrix[j][i].pipes[vertical].points;
            } else {
                partialSum = 0;
                break;
            }
        }
        sum += partialSum;
    }
    return sum;
}
void simpleProvisions(int *sol, int *finalSol, int *mark, int n, int pos, board chessboard, log logging, int *maximumPoints) {
    int i, j, k;                                                                                                        // the indexes
    cell x;                                                                                                             // the auxiliary cell

    if(pos >= n) {                                                                                                      // if that checks the terminal case (vector full)
        for (i = k = 0; i < chessboard.row; i++) {                                                                      // cycle on the row
            for (j = 0; j < chessboard.column; j++) {                                                                   // cycle on the column
                if(chessboard.matrix[i][j].fixed == FALSE) {                                                             // if that checks if the cell is empty
                    chessboard.matrix[i][j] = logging.vector[sol[k++]];
                }
            }
        }
        i = score(chessboard);
        if(i > *maximumPoints) {                                                                                        // if that checks the optimality of the solution
            *maximumPoints = i;
            for (i = 0; i < n; i++) {                                                                                   // cycle on the solution
                finalSol[i] = sol[i];
            }
        }
        return;
    }
    for(i = 0; i < n; i++) {                                                                                            // cycle on the tiles
        if (mark[i] == FALSE) {                                                                                         // if that checks if the i-th element is already considered
            x.pipes[horizontal] = logging.vector[i].pipes[horizontal];
            x.pipes[vertical] = logging.vector[i].pipes[vertical];
            mark[i] = 1;
            sol[pos] = i;
            simpleProvisions(sol, finalSol, mark, n, pos + 1, chessboard, logging, maximumPoints);                      // recursion
            j = *maximumPoints;
            logging.vector[i].pipes[vertical] = x.pipes[horizontal];
            logging.vector[i].pipes[horizontal] = x.pipes[vertical];
            simpleProvisions(sol, finalSol, mark, n, pos + 1, chessboard, logging, maximumPoints);                      // recursion
            if(j == *maximumPoints) {
                logging.vector[i].pipes[vertical] = x.pipes[vertical];                                                      // backtrack
                logging.vector[i].pipes[horizontal] = x.pipes[horizontal];                                                  // backtrack
            }
            mark[i] = FALSE;                                                                                            // backtrack
        }
    }
}