#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} activity, *Activity;          // the activity

int check(int *sol, int n, int pos,  Activity attivita);
Activity read(int *length);
int period(int *sol, int n, Activity attivita);
void powerset(int k, Activity attivita);
void powersetR(int *sol, int *finalSol, int k, int n, int pos, int start, int *duration, Activity attivita);

int main() {
    Activity attivita;
    int length;

    attivita = read(&length);
    powerset(length, attivita);
    free(attivita);
    return 0;
}

int check(int *sol, int n, int pos,  Activity attivita) {
    int i;                                                                                                              // the index

    for (i = 0; i < n; i++) {                                                                                           // cycle on the solution
        if((attivita[pos].start < attivita[sol[i]].end && attivita[sol[i]].start < attivita[pos].start) ||
                (attivita[pos].end < attivita[sol[i]].end && attivita[sol[i]].start < attivita[pos].end) ||
                (attivita[sol[i]].start < attivita[pos].end && attivita[pos].start < attivita[sol[i]].start) ||
                (attivita[sol[i]].end < attivita[pos].end && attivita[pos].start < attivita[sol[i]].end)) {             // if that checks if two activities are compatible
            return 0;
        }
    }
    return 1;
}
Activity read(int *length) {
    Activity attivita;                                                          // the vector of the activities
    FILE *filePointer;                                                          // the file
    int i;                                                                      // the index

    filePointer = fopen("example.txt", "r");
    fscanf(filePointer, "%d", length);                                          // reading the file
    attivita = (Activity) malloc(*length * sizeof(activity));
    assert(attivita != NULL);
    for (i = 0; i < *length; ++i) {                                             // cycle on the activities
        fscanf(filePointer, "%d %d", &attivita[i].start, &attivita[i].end);
    }
    fclose(filePointer);
    return attivita;
}
int period(int *sol, int n, Activity attivita) {
    int i;                                                      // the index
    int sum;                                                    // the sum of the duration

    for (i = sum = 0; i < n; i++) {                             // cycle on the solution
        sum += attivita[sol[i]].end - attivita[sol[i]].start;
    }
    return sum;
}
void powerset(int k, Activity attivita) {
    int i;                                                      // the index
    int *sol;                                                   // the solution
    int *finalSol;                                              // the optimality solution
    int duration;                                               // the maximum duration of the activities

    sol = (int *) malloc(k * sizeof(int));
    finalSol = (int *) malloc(k * sizeof(int));
    for(i = 0; i < k; i++){                                    // cycle on the solution
        sol[i] = finalSol[i] = -1;
    }
    duration = 0;
    for(i = 1; i < k + 1; i++){                                // cycle on the value of k
        powersetR(sol, finalSol, k, i, 0, 0, &duration, attivita);
    }
    fprintf(stdout,"The set that maximize the duration is:\n\t{");
    for (i = 0; i < k && finalSol[i] != -1; i++) {             // cycle on the optimality solution
        fprintf(stdout,"(%d %d)%s", attivita[finalSol[i]].start, attivita[finalSol[i]].end, finalSol[i + 1] == -1 || i + 1 == k ? "}\n" : " ");
    }
    fprintf(stdout,"And the duration is: %d", duration);
    free(sol);
    free(finalSol);
}
void powersetR(int *sol, int *finalSol, int k, int n, int pos, int start, int *duration, Activity attivita) {
    int i;                                                                                    // the index
    int a;                                                                                    // the duration of the activities

    if (pos == n){                                                                            // if that checks the terminal case (vector full)
        a = period(sol, n, attivita);
        if(a > *duration) {
            for (i = 0; i < n; i++) {                                                         // cycle on the optimality solution
                finalSol[i] = sol[i];
            }
            *duration = a;
        }
        return;
    }
    for (i = start; i < k; i++){                                                              // cycle on the value of k
        if(check(sol, pos, i, attivita) == 1) {                                               // if that checks if the activity to choose is legal
            sol[pos] = i;
            powersetR(sol, finalSol, k, n, pos + 1, i + 1, duration, attivita);               // recursion
        }
    }
}