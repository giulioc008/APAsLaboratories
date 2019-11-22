#include <assert.h>
#include <limits.h>
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 8

int maxmindiff(int **A, int n, int m);
int minimumDifferenceColumn(int **A, int j, int n);
void powerset(int *finalSol, int n, int m, int *length, int *price, int *max);
void powerset_r(int pos, int *finalSol, int k, int start, int *sol, int *length, int m, int *price, int *maxmimumPrice);
int value(int *length, int *sol, int *price, int n, int m);

int main() {
    char c;                                                                                                             // the control character
    FILE *filePointer;                                                                                                  // the file
    int length[M] = {7, 4, 8, 1, 5, 2, 6, 3};                                                                           // the vector with the length of the tape pieces
    int price[M] = {17, 9, 20, 1, 10, 5, 17, 8};                                                                        // the vector with the price of the tape pieces
    int **A;                                                                                                            // the matrix
    int n, m;                                                                                                           // the dimensions of the matrix
    int maxmimumPrice;                                                                                                  // the maximum price of the tape pieces
    int solution[N];                                                                                                    // the best solution
    int i, j;                                                                                                           // the indexes
    list L1, L2;                                                                                                        // the two lists

    fprintf(stdout, "First exercise\n");
    filePointer = fopen("exercise#1.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d %d", &n, &m);
    A = (int **) malloc(n * sizeof(int *));
    assert(A != NULL);
    for(i = 0; i < n; i++) {                                                                                            // cycle on the row of the matrix
        A[i] = (int *) malloc(m * sizeof(int));
        assert(A[i] != NULL);
        for(j = 0; j < m; j++) {                                                                                        // cycle on the column of the matrix
            fscanf(filePointer, "%d", &A[i][j]);
        }
    }
    fclose(filePointer);
    i = maxmindiff(A, n, m);
    fprintf(stdout, "\tThe maximum difference is on the column number %d.\n", i + 1);
    for(i = 0; i < n; i++) {                                                                                            // cycle on the row of the matrix
        free(A[i]);
    }
    free(A);
    fprintf(stdout, "Second exercise\n");
    L1 = LISTinit();
    L2 = LISTinit();
    filePointer = fopen("exercise#2.txt", "r");
    assert(filePointer != NULL);
    for(; fscanf(filePointer, "%d%c", &n, &c);) {
        LISTinsertTail(L1, n);
        if(c == '\n'){
            break;
        }
    }
    for(; fscanf(filePointer, "%d", &n) != EOF;) {
        LISTinsertTail(L2, n);
    }
    fclose(filePointer);
    LISTshow(L1);
    LISTshow(L2);
    splice(L1, L2, 1, 2);
    LISTshow(L1);
    LISTshow(L2);
    LISTfree(L1);
    LISTfree(L2);
    fprintf(stdout, "Third exercise\n");
    maxmimumPrice = 0;
    for(i = 0; i < N; i++) {                                                                                            // cycle on the best solution
        solution[i] = -1;
    }
    powerset(solution, N, M, length, price, &maxmimumPrice);
    fprintf(stdout, "\tThe best cut of the tape is:\n\t\t");
    for(i = 0; i < N; i++) {                                                                                            // cycle on the best solution
        if(solution[i] == -1) {
            break;
        }
        fprintf(stdout, "%d ", solution[i]);
    }
    return 0;
}

int maxmindiff(int **A, int n, int m) {
    int i;                                                                                                              // the index
    int j;                                                                                                              // the auxiliary variables
    int maximumDifference;                                                                                              // the maximum difference
    int maximumColumn;                                                                                                  // the maximum difference

    maximumDifference = maximumColumn = -1;
    for(i = 0; i < m; ++i) {                                                                                            // cycle on the column of the matrix
        j = minimumDifferenceColumn(A, i, n);
        if(j > maximumDifference) {                                                                                     // if that checks the optimality
            maximumDifference = j;
            maximumColumn = i;
        }
    }
    return maximumColumn;
}
int minimumDifferenceColumn(int **A, int j, int n) {
    int i;                                                                                                              // the index
    int a;                                                                                                              // the auxiliary variables
    int minimum;                                                                                                        // the minimum difference

    minimum = INT_MAX;
    for(i = 0; i < n - 1; ++i) {                                                                                        // cycle on the row of the matrix
        a = abs(A[i][j] - A[i + 1][j]);
        if(a < minimum) {                                                                                               // if that checks the optimality
            minimum = a;
        }
    }
    return minimum;
}
void powerset(int *finalSol, int n, int m, int *length, int *price, int *max) {
    int i;                                                                                                              // the index
    int *sol;                                                                                                           // the partial solution

    for(i = 1; i < m + 1; i++) {                                                                                        // cycle on the number of the pieces
        sol = (int *) malloc(i * sizeof(int));
        assert(sol != NULL);
        powerset_r(0, finalSol, i, n, sol, length, m, price, max);
        free(sol);
    }
}
void powerset_r(int pos, int *finalSol, int k, int start, int *sol, int *length, int m, int *price, int *maxmimumPrice) {
    int i;                                                                                                              // the index

    if (pos >= k) {                                                                                                     // if that checks the terminal case (vector full)
        if (start == 0) {                                                                                               // if that checks if the solution is legal
            i = value(length, sol, price, pos, m);
            if(i > *maxmimumPrice) {                                                                                    // if that checks the optimality of the solution (maximum price)
                *maxmimumPrice = i;
                for(i = 0; i < k; i++) {                                                                                // cycle on the solution
                    finalSol[i] = sol[i];
                }
            }
        }
        return;
    }
    for (i = start; i >= 0; i--) {                                                                                      // cycle on the possible length of the tape pieces
        sol[pos] = i;
        powerset_r(pos + 1, finalSol, k, start - sol[pos], sol, length, m, price, maxmimumPrice);                       // recursion
    }
}
int value(int *length, int *sol, int *price, int n, int m) {
    int i, j;                                                                                                           // the indexes
    int sum;                                                                                                            // the price of the tape pieces

    for(i = sum = 0; i < n; ++i) {
        for(j = 0; j < m; ++j) {
            if(length[j] == sol[i]) {
                sum += price[j];
                break;
            }
        }
    }
    return sum;
}