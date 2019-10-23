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
} stone;          // the type of the stone

int check(int stones, int possibilities);
int provisionsWithRepetition(int *sol, int n, int k, int pos, int *mark);

int main() {
    char value[error] = {'S', 'R', 'T', 'E'};                                           // the vector used like a Simbol Table
    FILE *filePointer;                                                                  // the file
    int *solution;                                                                      // the vector of the solution
    int i;                                                                              // the indexes
    int maximumLength;                                                                  // the maximum value of length
    int length;                                                                         // the length of the necklace
    int *mark;                                                                          // the vector of the occurrences

    mark = (int *) malloc(error * sizeof(int));
    assert(mark != NULL);
    filePointer = fopen("e1_test_set_easy.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%*d");                                                         // reading the file
    for (; feof(filePointer) == FALSE;) {                                               // cycle on the file
        for (i = 0; i < error; i++) {                                                   // cycle on the vector of the occurrence
            fscanf(filePointer, "%d", &mark[i]);
        }
        for (i = maximumLength = 0; i < error; i++) {                                   // cycle on the vector of the occurrence
            maximumLength += mark[i];
        }
        solution = (int *) malloc(maximumLength * sizeof(int));
        assert(solution != NULL);
        length = 0;
        fprintf(stdout, "Sum: %d\t\t", maximumLength);
        for (i = maximumLength; i > 0 && length == 0; i--) {                            // cycle on the value of length
            length = provisionsWithRepetition(solution, error, i, 0, mark);
        }
        length = ++i;
        fprintf(stdout, "The necklace with the maximum length is long %d and is composed by:\n\t", length);
        for (i = 0; i < length; i++) {
          fprintf(stdout, "%c ", value[solution[i]]);
        }
        fprintf(stdout, "\n");
        free(solution);
    }
    fclose(filePointer);
    return 0;
}

int check(int stones, int possibilities) {
    switch(stones) {                                // switch that checks the type of the stone
        case sapphire:
        case topaz:
            switch(possibilities) {                 // switch that checks the type of the stone
                case sapphire:
                case ruby:
                    return 1;
                default:
                    break;
            }
            break;
        case ruby:
        case emerald:
            switch(possibilities) {                 // switch that checks the type of the stone
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
int provisionsWithRepetition(int *sol, int n, int k, int pos, int *mark) {
  int i;                                                                             // the index

  if(pos >= k) {                                                                     // if that checks the terminal case (vector full)
        return 1;
    }
    for (i = 0; i < n; i++) {                                                        // cycle on the stone
      if(mark[i] > 0) {                                                              // if that checks the occurrences of the stone
        if (pos == 0 || check(sol[pos - 1], i) != FALSE) {                           // if that checks the particular case or execute the pruning (checks if the stone to set is legal)
          mark[i]--;
          sol[pos] = i;
          if(provisionsWithRepetition(sol, n, k, pos + 1, mark) == 1) {              // recursion
            mark[i]++;                                                               // backtrack
            return 1;
          }
          mark[i]++;                                                                 // backtrack
        }
      }
    }
    return FALSE;
}