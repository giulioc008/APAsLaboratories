#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0

typedef struct {
    int start;
    int end;
} activity, *Activity;          // the activity

int check(int x, int y,  Activity attivita);
int duration(activity x);
void merge(Activity attivita, Activity auxiliary, int l, int r, int q);
void mergeSort(Activity attivita, int length);
void mergeSortR(Activity attivita, Activity auxiliary, int l, int r);
Activity read(int *length);
int period(int *sol, int n, Activity attivita);
void dynamicProgramming(int length, Activity attivita);

int main() {
    Activity attivita;                                                                                                  // the activities
    int length;                                                                                                         // the length of the vector

    attivita = read(&length);
    mergeSort(attivita, length);
    dynamicProgramming(length, attivita);
    free(attivita);
    return 0;
}

int check(int x, int y,  Activity attivita) {
    if((attivita[y].start < attivita[x].start && attivita[x].start < attivita[y].end) ||
            (attivita[y].start < attivita[x].end && attivita[x].end < attivita[y].end) ||
            (attivita[x].start < attivita[y].start && attivita[y].start < attivita[x].end) ||
            (attivita[x].start < attivita[y].end && attivita[y].end < attivita[x].end)) {                               // if that checks if two activities are compatible
        return FALSE;
    }
    return 1;
}
int duration(activity x) {
    return x.end - x.start;
}
void merge(Activity attivita, Activity auxiliary, int l, int r, int q) {
    int i, j, k;

    i = l;
    j = q + 1;
    for (k = l; k <= r; k++) {                                                                                          // cycle on the auxiliary vector
        if(i > q) {                                                                                                     // if that checks if the left subvector is finish
            auxiliary[k] = attivita[j++];
        } else if(j > r) {                                                                                              // if that checks if the right subvector is finish
            auxiliary[k] = attivita[i++];
        } else if(duration(attivita[i]) >= duration(attivita[j])) {                                                     // if that checks if the left element is greater then the right element
            auxiliary[k] = attivita[i++];
        } else {
            auxiliary[k] = attivita[j++];
        }
    }
    for (k = l; k <= r; k++) {                                                                                          // cycle on the auxiliary vector
        attivita[k] = auxiliary[k];
    }
}
void mergeSort(Activity attivita, int length) {
    Activity auxiliary;
    int l, r;

    l = 0;
    r = length - 1;
    auxiliary = (Activity) malloc(length * sizeof(activity));
    mergeSortR(attivita, auxiliary, l, r);
    free(auxiliary);
}
void mergeSortR(Activity attivita, Activity auxiliary, int l, int r) {
    int q;

    if(r <= l) {                                                                                                        // if that checks the elementary case
        return;
    }
    q = (l + r) / 2;
    mergeSortR(attivita, auxiliary, l, q);
    mergeSortR(attivita, auxiliary, q + 1, r);
    merge(attivita, auxiliary, l, r, q);
}
Activity read(int *length) {
    Activity attivita;                                                                                                  // the vector of the activities
    FILE *filePointer;                                                                                                  // the file
    int i;                                                                                                              // the index

    filePointer = fopen("example.txt", "r");
    fscanf(filePointer, "%d", length);                                                                                  // reading the file
    attivita = (Activity) malloc(*length * sizeof(activity));
    assert(attivita != NULL);
    for (i = 0; i < *length; ++i) {                                                                                     // cycle on the activities
        fscanf(filePointer, "%d %d", &attivita[i].start, &attivita[i].end);
    }
    fclose(filePointer);
    return attivita;
}
int period(int *sol, int n, Activity attivita) {
    int i;                                                                                                              // the index
    int sum;                                                                                                            // the sum of the duration

    for (i = sum = 0; i < n; i++) {                                                                                     // cycle on the solution
        sum += duration(attivita[sol[i]]);
    }
    return sum;
}
void dynamicProgramming(int length, Activity attivita) {
    int i, j, k, x;                                                                                                     // the indexes
    int *sol;                                                                                                           // the solution
    int *mark;                                                                                                          // the vector of the choices
    int *finalSol;                                                                                                      // the optimality solution
    int maximumDuration;                                                                                                // the maximum duration of the activities
    int duration;                                                                                                       // the duration of the activities

    mark = (int *) calloc(length, sizeof(int));
    assert(mark != NULL);
    sol = (int *) malloc(length * sizeof(int));
    assert(sol != NULL);
    finalSol = (int *) malloc(length * sizeof(int));
    assert(finalSol != NULL);
    for (i = 0; i < length; i++) {                                                                                      // cycle on the optimality solution
        finalSol[i] = -1;
    }
    maximumDuration = 0;
    for (x = 0; x < length; x++) {                                                                                      // cycle on the vector
        for(i = x, k = 0; i < length; i++) {                                                                            // cycle on the remaining part of the vector
            if(mark[i] == FALSE) {                                                                                      // if that checks if the choices is legal
                sol[k++] = i;
                mark[i] = 1;
                for(j = i + 1; j < length; j++) {                                                                       // cycle on the remaining part of the vector
                    if(check(i, j, attivita) == FALSE) {                                                                // if that checks if the activity is illegal
                        mark[j] = 1;
                    }
                }
            }
        }
        for(i = x; i < length; i++) {                                                                                   // cycle on the vector
            for(j = 0; j < k && mark[i] != FALSE; j++) {                                                                // cycle on the remaining part of the vector
                if(check(i, sol[j], attivita) == FALSE) {                                                               // if that checks if the activity is illegal
                    mark[i] = FALSE;                                                                                    // backtrack
                }
            }
        }
        duration = period(sol, k, attivita);
        if(duration > maximumDuration) {                                                                                // if that checks the optimality condition
            maximumDuration = duration;
            for(j = 0; j < k; j++) {                                                                                    // cycle on the optimal solution
                finalSol[j] = sol[j];
            }
        }
    }
    if(maximumDuration != 0) {                                                                                          // if that checks if exists a set that maximize the duration
        fprintf(stdout, "The set that maximize the duration is:\n\t{");
        for (i = 0; i < length && finalSol[i] != -1; i++) {                                                             // cycle on the optimality solution
            fprintf(stdout, "(%d %d)%s", attivita[finalSol[i]].start, attivita[finalSol[i]].end, finalSol[i + 1] == -1 || i + 1 == length ? "}\n" : " ");
        }
        fprintf(stdout, "And the duration is: %d", maximumDuration);
    } else {
        fprintf(stdout, "There isn't a set that maximize the duration");
    }
    free(sol);
    free(mark);
    free(finalSol);
}