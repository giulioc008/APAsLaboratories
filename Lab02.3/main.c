#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

typedef struct Node node, *link;
struct Node {
    char *string;
    int position;
    link next;
};
typedef struct {
    char *string;
    link occurrencesHead, occurrencesTail;
} dictionary, *Dictionary;

void insert(link *head, link *tail, char *buffer, int counter);
link new(char *buffer, int counter, link next);
Dictionary read(int *length);

int main() {
    Dictionary dict;                                                                               // the dictionary
    char buffer[25 + 1];                                                                           // the buffer
    char character;                                                                                // the character read
    FILE *filePointer;                                                                             // the file
    int length;                                                                                    // the length of the dictionary
    int i;                                                                                         // the index
    int counter;                                                                                   // the counter of the words in the text
    link j;                                                                                        // the index of the list

    dict = read(&length);
    filePointer = fopen("testo.txt", "r");
    for(i = counter = 0; feof(filePointer) == FALSE; ) {                                           // cycle for reading the file
        fscanf(filePointer, "%c", &character);
        if(isalnum(character) != FALSE) {                                                          // if that checks if the character is a punctuation character
            buffer[i++] = character;
        } else {
            buffer[i] = '\0';
            counter++;
            for(i = 0; i < length; i++) {                                                          // cycling on the dictionary
                if(strnicmp(buffer, dict[i].string, strlen(dict[i].string)) == 0) {                // if that checks if the buffer is equal to the i-th string in the dictionary
                    insert(&dict[i].occurrencesHead, &dict[i].occurrencesTail, buffer, counter);
                }

            }
            i = 0;
        }
    }
    fclose(filePointer);
    for(i = 0; i < length; i++) {                                                                  // cycle on the vector
        fprintf(stdout, "Sequence %s:\n", dict[i].string);
        for (j = dict[i].occurrencesHead; j != NULL; j = j -> next) {                             // cycle on the list of occurrences
            fprintf(stdout, "\t%s (%d word of the text)\n", j -> string, j -> position);
        }
        fprintf(stdout, "\n");
    }
    return 0;
}

void insert(link *head, link *tail, char *buffer, int counter) {
    if(*head == NULL) {                                                     // if that checks if the list is empty
        *head = *tail = new(buffer, counter, NULL);
    } else {
        (*tail) -> next = new(buffer, counter, NULL);
        *tail = (*tail) -> next;
    }
}
link new(char *buffer, int counter, link next) {
    link x;                                 // the node of the list

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                         // if that checks the allocation of the node
        x -> string = strdup(buffer);
        x -> position = counter;
        x -> next = next;
    }
    return x;
}
Dictionary read(int *length) {
    char buffer[5 + 1];                                             // the buffer
    Dictionary dict;                                                // the dictionary
    FILE *filePointer;                                              // the file
    int i;                                                          // index

    filePointer = fopen("sequenze.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d", length);                              // reading the file
    dict = (Dictionary) malloc(*length * sizeof(dictionary));
    for(i = 0; i < *length; i++) {                                  // cycling on the dictionary
        fscanf(filePointer, "%s", buffer);
        dict[i].string = strdup(buffer);
        assert(dict[i].string != NULL);
        dict[i].occurrencesHead = dict[i].occurrencesTail = NULL;
    }
    fclose(filePointer);
    return dict;
}