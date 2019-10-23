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
} type;                                                                                                                 // the type of the stone
typedef enum {
    number,
    priceOfTheStone,
    consecutiveOccurrence,
    fatal
} data;                                                                                                                 // the data of the stone

int check(int stones, int possibilities);
int price(int *sol, int n, int **mark);
void provisionsWithRepetition(int *sol, int *finalSol, int n, int k, int pos, int **mark, int maximumRepetition, int *finalPrice);

int main() {
    char value[error] = {'S', 'R', 'T', 'E'};                                                                           // the vector used like a Simbol Table
    FILE *filePointer;                                                                                                  // the file
    int *solution;                                                                                                      // the solution
    int *finalSolution;                                                                                                 // the optimal solution
    int i, j;                                                                                                           // the indexes
    int maximumLength;                                                                                                  // the maximum value of length
    int price;                                                                                                          // the price of the necklace
    int maximumRepetition;                                                                                              // the maximum consecutive repetition of a stone
    int **mark;                                                                                                         // the vector of the occurrences

    mark = (int **) malloc(error * sizeof(int *));
    assert(mark != NULL);
    for (i = 0; i < error; i++) {                                                                                       // cycle on the matrix of the occurrence
        mark[i] = (int *) malloc(fatal * sizeof(int));
        assert(mark[i] != NULL);
    }
    filePointer = fopen("e2_test_set.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%*d");                                                                                         // reading the file
    for (; feof(filePointer) == FALSE;) {                                                                               // cycle on the file
        for (i = 0; i < consecutiveOccurrence; i++) {                                                                   // cycle on the matrix of the occurrence
            for (j = 0; j < error; j++) {
                fscanf(filePointer, "%d", &mark[j][i]);
                mark[j][consecutiveOccurrence] = 0;
            }
        }
        fscanf(filePointer, "%d", &maximumRepetition);
        for (i = maximumLength = 0; i < error; i++) {                                                                   // cycle on the vector of the occurrence
            maximumLength += mark[i][number];
        }
        finalSolution = (int *) malloc(maximumLength * sizeof(int));
        assert(finalSolution != NULL);
        for (i = 0; i < maximumLength; i++) {                                                                           // cycle on the optimal solution
            finalSolution[i] = -1;
        }
        fprintf(stdout, "Sum: %d\t\t", maximumLength);
        for (i = 1, price = 0; i < maximumLength + 1; i++) {                                                            // cycle on the value of length
            solution = (int *) malloc(i * sizeof(int));
            assert(solution != NULL);
            provisionsWithRepetition(solution, finalSolution, error, i, 0, mark, maximumRepetition, &price);
            free(solution);
        }
        fprintf(stdout, "The necklace with the maximum price cost %d Euros and is composed by:\n\t", price);
        for (i = 0; i < maximumLength && finalSolution[i] != -1; i++) {
          fprintf(stdout, "%c ", value[finalSolution[i]]);
        }
        fprintf(stdout, "\nWhere the maximum consecutive repetition of a stone is equal to %d\n", maximumRepetition);
        free(finalSolution);
    }
    for (i = 0; i < error; i++) {                                                                                       // cycle on the matrix of the occurrence
        free(mark[i]);
    }
    free(mark);
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
int price(int *sol, int n, int **mark) {
    int i;                                                                                                              // the index
    int sum;                                                                                                            // the price

    for (i = sum = 0; i < n; i++) {
        sum += mark[sol[i]][priceOfTheStone];
    }
    return sum;
}
void provisionsWithRepetition(int *sol, int *finalSol, int n, int k, int pos, int **mark, int maximumRepetition, int *finalPrice) {
    int i;                                                                                                              // the index
    int countSapphire;                                                                                                  // the index
    int countEmerald;                                                                                                   // the index

    if(pos >= k) {                                                                                                      // if that checks the terminal case (vector full)
        for (i = countEmerald = countSapphire = 0; i < pos; i++) {                                                      // cycle on the solution
            switch(sol[i]) {                                                                                            // switch that checks the type of the stone
                case sapphire:
                    countSapphire++;
                    break;
                case emerald:
                    countEmerald++;
                    break;
                default:
                    break;
            }
        }
        if(countSapphire <= countEmerald) {                                                                             // if that checks the condition of the occurrence (#sapphire less or equal to #emerald)
            i = price(sol, pos, mark);
            if(i > *finalPrice) {                                                                                       // if that checks the optimality of the solution
                *finalPrice = i;
                for (i = 0; i < pos; i++) {
                    finalSol[i] = sol[i];
                }
            }
        }
        return;
    }
    for (i = 0; i < n; i++) {                                                                                           // cycle on the stone
        if(mark[i][number] > 0) {                                                                                       // if that checks the occurrences of the stone
            if (pos == 0) {                                                                                             // if that checks if pos is equal to 0
                switch(i) {                                                                                             // switch that checks the type of the stone
                    case sapphire:
                        countEmerald = mark[emerald][consecutiveOccurrence];
                        mark[emerald][consecutiveOccurrence] = 0;
                        mark[i][consecutiveOccurrence]++;
                        break;
                    case emerald:
                        countSapphire = mark[sapphire][consecutiveOccurrence];
                        mark[sapphire][consecutiveOccurrence] = 0;
                        mark[i][consecutiveOccurrence]++;
                        break;
                    default:
                        break;
                }
                if(mark[i][consecutiveOccurrence] <= maximumRepetition) {                                               // if that checks the consecutive repetition of a stone
                    mark[i][number]--;
                    sol[pos] = i;
                    provisionsWithRepetition(sol, finalSol, n, k, pos + 1, mark, maximumRepetition, finalPrice);        // recursion
                    mark[i][number]++;                                                                                  // backtrack
                }
                switch(i) {                                                                                             // switch that checks the type of the stone
                    case sapphire:
                        mark[emerald][consecutiveOccurrence] = countEmerald;
                        mark[i][consecutiveOccurrence]--;                                                               // backtrack
                        break;
                    case emerald:
                        mark[sapphire][consecutiveOccurrence] = countSapphire;
                        mark[i][consecutiveOccurrence]--;                                                               // backtrack
                        break;
                    default:
                        break;
                }
            } else if (check(sol[pos - 1], i) != FALSE) {                                                               // if that execute the pruning (checks if the stone to set is legal)
                switch(i) {                                                                                             // switch that checks the type of the stone
                    case sapphire:
                        countEmerald = mark[emerald][consecutiveOccurrence];
                        mark[emerald][consecutiveOccurrence] = 0;
                        mark[i][consecutiveOccurrence]++;
                        break;
                    case emerald:
                        countSapphire = mark[sapphire][consecutiveOccurrence];
                        mark[sapphire][consecutiveOccurrence] = 0;
                        mark[i][consecutiveOccurrence]++;
                        break;
                    default:
                        break;
                }
                if(mark[i][consecutiveOccurrence] <= maximumRepetition) {                                               // if that checks the consecutive repetition of a stone
                    mark[i][number]--;
                    sol[pos] = i;
                    provisionsWithRepetition(sol, finalSol, n, k, pos + 1, mark, maximumRepetition, finalPrice);        // recursion
                    mark[i][number]++;                                                                                  // backtrack
                }
                switch(i) {                                                                                             // switch that checks the type of the stone
                    case sapphire:
                        mark[emerald][consecutiveOccurrence] = countEmerald;
                        mark[i][consecutiveOccurrence]--;                                                               // backtrack
                        break;
                    case emerald:
                        mark[sapphire][consecutiveOccurrence] = countSapphire;
                        mark[i][consecutiveOccurrence]--;                                                               // backtrack
                        break;
                    default:
                        break;
                }
            }
        }
    }
}