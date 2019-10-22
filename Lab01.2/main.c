#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

typedef struct {
    char *word, *sostitute;
} dictionary, *Dictionary;

void read(Dictionary *dict, int *n);

int main() {
    char string[200 + 1];                                                       // string used to store the read strings
    char *c;                                                                    // pointer used to cycle on the string
    char *s;                                                                    // pointer used to checks if there're an occurrence of the word in the string
    char control;                                                               // character used in text formatting
    Dictionary dict;
    FILE *filePointerReader, *filePointerWriter;
    int i;                                                                      // index used to cycle on the Dictionary dict
    int j;                                                                      // index used to cycle on the string
    int n;                                                                      // index that rappresents the number of word in the Dictionary dict

    read(&dict, &n);
    fprintf(stdout, "--- The program is executed ---\n\n");
    filePointerReader = fopen("sorgente.txt", "r");
    assert(filePointerReader != NULL);
    filePointerWriter = fopen("ricodificato.txt", "w");
    assert(filePointerWriter != NULL);
    for (; feof(filePointerReader) == FALSE;) {                                 // reading the file sorgente.txt and writing the file ricodificato.txt
        fscanf(filePointerReader, "%s%c", string, &control);
        for(i = 0; i < n; i++) {                                                // cycling on the Dictionary dict
            s = strstr(string, dict[i].word);
            if (s != NULL) {                                                    // if that checks if there're an occurrence of the word in the string
                for(c = strdup(string), j = 0; strcmp(c, s) != 0; c++, j++) {   // cycling on the string
                    string[j] = *c;
                }
                c += strlen(dict[i].word);
                string[j] = '\0';
                strcat(string, dict[i].sostitute);
                for (j = strlen(string); *c != '\0'; c++, j++) {                // cycling on the restant part of the string
                    string[j] = *c;
                }
                string[j] = '\0';
                break;
            }
        }
        fprintf(filePointerWriter, "%s%c", string, control);
    }
    fclose(filePointerReader);
    fclose(filePointerWriter);
    return 0;
}

void read(Dictionary *dict, int *n) {
    char buffer[200 + 1];
    FILE *filePointer;
    int i;

    fprintf(stdout, "--- The program acquires data ---\n\n");
    filePointer = fopen("dizionario.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d", n);                                             // reading the file
    assert(*n <= 30);
    *dict = (Dictionary) malloc(*n * sizeof(dictionary));
    for (i = 0; i < *n; i++) {                                                // cycle on the Dictionary dict
        fscanf(filePointer, "%s", buffer);
        (*dict)[i].sostitute = strdup(buffer);
        assert((*dict)[i].sostitute != NULL);
        fscanf(filePointer, "%s", buffer);
        (*dict)[i].word = strdup(buffer);
        assert((*dict)[i].word != NULL);
    }
    fclose(filePointer);
}