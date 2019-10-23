#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *choices;
    int numberOfChoices;
} level, *Level;                // the choices
typedef struct {
    char **songs;
    int numberOfSongs;
} person, *Person;              // the friends
typedef struct {
    Person friend;
    int numberOfFriend;
} log;                          // the struct

void multiplicationPrinciple(int pos, Level val, int *sol, int n, Person friend);
log read();

int main() {
    int i, j;                                                                           // the indexes
    int *solution;                                                                      // the solution
    Level val;                                                                          // the vector of the choices
    log vector;                                                                         // the struct

    vector = read();
    val = (Level) malloc(vector.numberOfFriend * sizeof(level));
    assert(val != NULL);
    for (i = 0; i < vector.numberOfFriend; i++) {                                       // cycle on the vector of the choices
        val[i].numberOfChoices = vector.friend[i].numberOfSongs;
        val[i].choices = (int *) malloc(val[i].numberOfChoices * sizeof(int));
        assert(val[i].choices != NULL);
        for (j = 0; j < val[i].numberOfChoices; j++) {
            val[i].choices[j] = j;
        }
    }
    solution = (int *) malloc(vector.numberOfFriend * sizeof(int));
    assert(solution != NULL);
    multiplicationPrinciple(0, val, solution, vector.numberOfFriend, vector.friend);
    free(solution);
    for (i = 0; i < vector.numberOfFriend; i++) {                                       // cycle on the vector of the choices
        free(val[i].choices);
    }
    free(val);
    for (i = 0; i < vector.numberOfFriend; i++) {                                       // cycle on the friends
        for (j = 0; j < vector.friend[i].numberOfSongs; j++) {                          // cycle on the songs
            free(vector.friend[i].songs[j]);
        }
        free(vector.friend[i].songs);
    }
    free(vector.friend);
    return 0;
}

void multiplicationPrinciple(int pos, Level val, int *sol, int n, Person friend) {
    int i;                                                          // the index

    if(pos >= n) {                                                  // if that checks if there are a solution (the vector is full)
        fprintf(stdout, "The playlist is formed by:\n");
        for (i = 0; i < n; i++) {                                   // cycle on the solution
            fprintf(stdout, "\t%s\n", friend[i].songs[sol[i]]);
        }
        return;
    }
    for(i = 0; i < val[pos].numberOfChoices; i++) {                 // cycle on the choices
        sol[pos] = val[pos].choices[i];
        multiplicationPrinciple(pos + 1, val, sol, n, friend);      // recursion
    }
}
log read() {
    char buffer[255 + 1];                                                           // the buffer
    FILE *filePointer;                                                              // the file
    int i, j;                                                                       // the indexes
    log vector;                                                                     // the struct

    filePointer = fopen("brani.txt", "r");
    fscanf(filePointer, "%d", &vector.numberOfFriend);                              // reading the file
    vector.friend = (Person) malloc(vector.numberOfFriend * sizeof(person));
    assert(vector.friend != NULL);
    for (i = 0; i < vector.numberOfFriend; i++) {                                   // cycle on the friends
        fscanf(filePointer, "%d", &vector.friend[i].numberOfSongs);
        vector.friend[i].songs = (char **) malloc(vector.numberOfFriend * sizeof(char *));
        assert(vector.friend[i].songs != NULL);
        for (j = 0; j < vector.friend[i].numberOfSongs; j++) {                      // cycle on the songs
            fscanf(filePointer, "%s\n", buffer);
            vector.friend[i].songs[j] = strdup(buffer);
            assert(vector.friend[i].songs[j] != NULL);
        }
    }
    fclose(filePointer);
    return vector;
}