#include <assert.h>
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DD 10
#define DP 20
#define FALSE 0
#define NUMBEROFDIAGONAL 3
#define THRESHOLD 8

typedef enum {
    transition,
    backward,
    forward,
    error
} types;                                                                                                                // the type of the element
typedef enum {
    behind,
    frontally,
    fatal
} directions;                                                                                                           // the direction of the element
typedef struct {
    char *name;
    directions input, output;
    float points;
    int priority, final, difficulty;
    types type;
} element, *Element;                                                                                                    // the element
typedef struct {
    Element vector;
    int lengthOfVector, lengthOfList;
    link head, *listInVector;
} logging, *Logging;                                                                                                    // the log

int check(int i, int *sol, int length, Element vector);
int checkBonus(int *sol, int length, Element vector);
void combinationWithRepetition(int pos, int *sol, int *finalSol, int n, int k, int start, logging log, int flagForwardAcrobatic, int flagBackwardAcrobatic, int flagSequenceAcrobatic, float *points);
int diagonalDifficulty(int *sol, int length, Element vector);
float diagonalPoints(int *sol, int length, Element vector);
int isAcrobatic(element x);
int isBackwardAcrobaticDiagonal(int *diagonal, int length, Element vector);
int isDoubleAcrobaticDiagonal(int *diagonal, int length, Element vector);
int isFinal(element x);
int isFirst(element x);
int isForwardAcrobaticDiagonal(int *diagonal, int length, Element vector);
int isFrontally(element x);
logging read();
int programDifficulty(int *sol, int length, logging log);
float programPoints(int *sol, int length, logging log);
void provisionsWithRepetition(int pos, int *sol, int n, int k, Logging log, int flagAcrobatic);

int main() {
    int *solution;                                                                                                      // the solution
    int *finalSolution;                                                                                                 // the final solution
    int i, j;                                                                                                           // the indexes
    float points;                                                                                                       // the points of the program
    link x;                                                                                                             // the auxiliary node
    logging log;                                                                                                        // the log

    log = read();
    solution = (int *) malloc(NUMBEROFELEMENT * sizeof(int));
    assert(solution != NULL);
    for(i = 1; i < NUMBEROFELEMENT + 1; ++i) {                                                                              // cycle on the diagonal
        provisionsWithRepetition(0, solution, log.lengthOfVector, i, &log, FALSE);
    }
    free(solution);
    solution = (int *) malloc(NUMBEROFDIAGONAL * sizeof(int));
    assert(solution != NULL);
    finalSolution = (int *) malloc(NUMBEROFDIAGONAL * sizeof(int));
    assert(finalSolution != NULL);
    log.listInVector = (link *) malloc(log.lengthOfList * sizeof(link));
    assert(log.listInVector != NULL);
    for(i = 0, x = log.head; i < log.lengthOfList; i++, x = LISTnext(x)) {                                              // cycle on the vector
        log.listInVector[i] = x;
    }
    points = 0.0;
    combinationWithRepetition(0, solution, finalSolution, log.lengthOfList, NUMBEROFDIAGONAL, 0, log, FALSE, FALSE, FALSE, &points);
    free(solution);
    fprintf(stdout, "The program with the maximum points is:\n");
    for(i = 0; i < NUMBEROFDIAGONAL; ++i) {                                                                             // cycle on the program
        fprintf(stdout, "\t%d-th diagonal:\n\t\tPoints:\n\t\t\t%.2f\n\t\tElements:\n", i + 1, diagonalPoints(LISTdiagonal(log.listInVector[finalSolution[i]]), LISTdiagonalLength(log.listInVector[finalSolution[i]]), log.vector));
        for(j = 0; j < LISTdiagonalLength(log.listInVector[finalSolution[i]]); ++j) {                                   // cycle on the diagonal
            fprintf(stdout, "\t\t\t%s\n", log.vector[LISTdiagonal(log.listInVector[finalSolution[i]])[j]].name);
        }
    }
    fprintf(stdout, "and the points is: %.2f\n", points);
    free(finalSolution);
    LISTfree(&log.head);
    for(i = 0; i < log.lengthOfList; i++) {                                                                             // cycle on the vector
        free(log.listInVector[i]);
    }
    for(i = 0; i < log.lengthOfVector; ++i) {                                                                           // cycle on the vector
        free(log.vector[i].name);
    }
    free(log.vector);
    return 0;
}

int check(int i, int *sol, int length, Element vector) {
    if(vector[sol[length - 1]].output == vector[i].input && diagonalDifficulty(sol, length, vector) + vector[i].difficulty <= DD) {   // if that checks if the two element are compatible
        return 1;
    }
    return FALSE;
}
int checkBonus(int *sol, int length, Element vector) {
    if(vector[sol[length - 1]].difficulty >= THRESHOLD) {                                                               // if that checks if the diagonal have the bonus
        return 1;
    }
    return FALSE;
}
void combinationWithRepetition(int pos, int *sol, int *finalSol, int n, int k, int start, logging log, int flagForwardAcrobatic, int flagBackwardAcrobatic, int flagSequenceAcrobatic, float *points) {
    int i;                                                                                                              // the index
    int a, b, c;                                                                                                        // the auxiliary variables
    float d;                                                                                                            // the points of the program

    if (pos >= k) {                                                                                                     // if that checks the terminal case (vector full)
        if(flagForwardAcrobatic != FALSE && flagBackwardAcrobatic != FALSE && flagSequenceAcrobatic != FALSE) {         // if that checks if the program is legal (if is present a forward acrobatic element, if is present a backward acrobatic element and if are present two acrobatic element in sequence)
            d = programPoints(sol, pos, log);
            if(d > *points) {                                                                                           // if that checks the optimality of the program
                *points = d;
                for (i = 0; i < pos; ++i) {                                                                             // cycle on the vector
                    finalSol[i] = sol[i];
                }
            }
        }
        return;
    }
    for(i = start; i < n; i++) {                                                                                        // cycle on the vector
        if(pos == 0 || (pos > 0 && programDifficulty(sol, pos, log) + diagonalDifficulty(LISTdiagonal(log.listInVector[i]), LISTdiagonalLength(log.listInVector[i]), log.vector) <= DP)) {  // if that execute the pruning on the difficulty of the program
            sol[pos] = i;
            a = flagForwardAcrobatic;
            b = flagBackwardAcrobatic;
            c = flagSequenceAcrobatic;
            if(flagForwardAcrobatic == FALSE && isForwardAcrobaticDiagonal(LISTdiagonal(log.listInVector[i]), LISTdiagonalLength(log.listInVector[i]), log.vector) != FALSE) {  // if that checks if the diagonal has a forward acrobatic element
                flagForwardAcrobatic = 1;
            }
            if(flagBackwardAcrobatic == FALSE && isBackwardAcrobaticDiagonal(LISTdiagonal(log.listInVector[i]), LISTdiagonalLength(log.listInVector[i]), log.vector) != FALSE) {    // if that checks if the diagonal has a backward acrobatic element
                flagBackwardAcrobatic = 1;
            }
            if(flagSequenceAcrobatic == FALSE && isDoubleAcrobaticDiagonal(LISTdiagonal(log.listInVector[i]), LISTdiagonalLength(log.listInVector[i]), log.vector) != FALSE) {  // if that checks if the diagonal has a two acrobatic element in sequence
                flagSequenceAcrobatic = 1;
            }
            combinationWithRepetition(pos + 1, sol, finalSol, n, k, start, log, flagForwardAcrobatic, flagBackwardAcrobatic, flagSequenceAcrobatic, points);    // recursion
            flagForwardAcrobatic = a;                                                                                   // backtrack
            flagBackwardAcrobatic = b;                                                                                  // backtrack
            flagSequenceAcrobatic = c;                                                                                  // backtrack
            start++;
        }
    }
}
int diagonalDifficulty(int *sol, int length, Element vector) {
    int i;                                                                                                              // the index
    int sum;                                                                                                            // the sum of the difficulty

    for(i = sum = 0; i < length; i++) {                                                                                 // cycle on the solution
        sum += vector[sol[i]].difficulty;
    }
    return sum;
}
float diagonalPoints(int *sol, int length, Element vector) {
    int i;                                                                                                              // the index
    float sum;                                                                                                          // the sum of the points

    for(i = 0, sum = 0.0; i < length; i++) {                                                                            // cycle on the solution
        sum += vector[sol[i]].points;
    }
    return sum;
}
int isAcrobatic(element x) {
    if(x.type == transition) {                                                                                          // if that checks if the element is acrobatic
        return FALSE;
    }
    return 1;
}
int isBackwardAcrobaticDiagonal(int *diagonal, int length, Element vector) {
    int i;                                                                                                              // the index

    for(i = 0; i < length; i++) {                                                                                       // cycle on the diagonal
        if(vector[diagonal[i]].type == backward) {                                                                      // if that checks if the i-th element is a backward acrobatic element
            return 1;
        }
    }
    return FALSE;
}
int isDoubleAcrobaticDiagonal(int *diagonal, int length, Element vector) {
    int i;                                                                                                              // the index

    for(i = 0; i < length - 1; i++) {                                                                                   // cycle on the diagonal
        if(isAcrobatic(vector[diagonal[i]]) != FALSE && isAcrobatic(vector[diagonal[i + 1]]) != FALSE) {                // if that checks if there are two acrobatic element in sequence
            return 1;
        }
    }
    return FALSE;
}
int isFinal(element x) {
    return x.final;
}
int isFirst(element x) {
    if(x.priority != FALSE) {                                                                                           // if that checks if the element is acrobatic
        return FALSE;
    }
    return 1;
}
int isForwardAcrobaticDiagonal(int *diagonal, int length, Element vector) {
    int i;                                                                                                              // the index

    for(i = 0; i < length; i++) {                                                                                       // cycle on the diagonal
        if(vector[diagonal[i]].type == forward) {                                                                       // if that checks if the i-th element is a forward acrobatic element
            return 1;
        }
    }
    return FALSE;
}
int isFrontally(element x) {
    if(x.input != frontally) {                                                                                          // if that checks if the element starts frontally
        return FALSE;
    }
    return 1;
}
logging read() {
    char buffer[100 + 1];                                                                                               // the buffer
    FILE *filePointer;                                                                                                  // the file
    int i;                                                                                                              // the index
    logging log;                                                                                                        // the log

    filePointer = fopen("elementi.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d", &log.lengthOfVector);
    log.vector = (Element) malloc(log.lengthOfVector * sizeof(element));
    assert(log.vector != NULL);
    log.head = NULL;
    log.lengthOfList = 0;
    for(i = 0; i < log.lengthOfVector - 1; i++) {                                                                       // cycle on the vector
        fscanf(filePointer, "%s %d %d %d %d %d %f %d", buffer, &log.vector[i].type, &log.vector[i].input,
               &log.vector[i].output, &log.vector[i].priority, &log.vector[i].final, &log.vector[i].points,
               &log.vector[i].difficulty);
        assert(log.vector[i].input != fatal && log.vector[i].output != fatal && log.vector[i].type != error);
        log.vector[i].name = strdup(buffer);
        assert(log.vector[i].name != NULL);
    }
    fclose(filePointer);
    return log;
}
int programDifficulty(int *sol, int length, logging log) {
    int i;                                                                                                              // the index
    int sum;                                                                                                            // the sum of the difficulty

    for (i = sum = 0; i < length; i++) {                                                                                // cycle on the program
        sum += diagonalDifficulty(LISTdiagonal(log.listInVector[sol[i]]), LISTdiagonalLength(log.listInVector[sol[i]]), log.vector);
    }
    return sum;
}
float programPoints(int *sol, int length, logging log) {
    int i;                                                                                                              // the index
    float sum;                                                                                                          // the sum of the difficulty

    for (i = 0, sum = 0.0; i < length; i++) {                                                                           // cycle on the program
        if(i == length - 1 && checkBonus(LISTdiagonal(log.listInVector[sol[i]]), LISTdiagonalLength(log.listInVector[sol[i]]), log.vector) != FALSE) {  // if that checks if the last diagonal have the bonus
            sum += diagonalPoints(LISTdiagonal(log.listInVector[sol[i]]), LISTdiagonalLength(log.listInVector[sol[i]]), log.vector) * 1.5;
        } else {
            sum += diagonalPoints(LISTdiagonal(log.listInVector[sol[i]]), LISTdiagonalLength(log.listInVector[sol[i]]), log.vector);
        }
    }
    return sum;
}
void provisionsWithRepetition(int pos, int *sol, int n, int k, Logging log, int flagAcrobatic) {
    int i;                                                                                                              // the index
    int a;                                                                                                              // the auxiliary variable

    if(pos >= k || (pos > 0 && isFinal(log->vector[sol[pos - 1]]) != FALSE)) {                                          // if that checks the terminal case (vector full or final element set)
        if(flagAcrobatic != FALSE) {                                                                                    // if that checks if the diagonal is legal (if is present an acrobatic element)
            LISTinsertHeadPointers(&log->head, sol, pos);
            log->lengthOfList++;
        }
        return;
    }
    for(i = 0; i < n; i++) {                                                                                            // cycle on the vector
        if((pos == 0 && isFrontally(log->vector[i]) != FALSE && isFirst(log->vector[i]) != FALSE) || (pos > 0 && check(i, sol, pos, log->vector) != FALSE)) {   // if that checks if the first element is legal and that execute the pruning on the difficulty of the diagonal
            sol[pos] = i;
            a = flagAcrobatic;
            if(flagAcrobatic == FALSE && isAcrobatic(log->vector[sol[pos]]) != FALSE) {                                 // if that checks if the element is acrobatic
                flagAcrobatic = 1;
            }
            provisionsWithRepetition(pos + 1, sol, n, k, log, flagAcrobatic);                                           // recursion
            flagAcrobatic = a;                                                                                          // backtrack
        }
    }
}