#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

int conta(char *S, int n, int p);

int main() {
    char string[20 + 1];
    FILE *filePointer;
    int index, length, number, vowels, substring;

    fprintf(stdout, "--- The program acquires data ---\n\tInsert the name of the file to open with the relative extension:  ");
    fscanf(stdin, "%s", string);                                                                                                                // acquisition of the name of the file
    fprintf(stdout, "\tInsert the length of the substring to search: ");
    fscanf(stdin, "%d", &length);                                                                                                               // acquisition of the length of the substring
    fprintf(stdout, "\tInsert the number of vowels: ");
    fscanf(stdin, "%d", &vowels);                                                                                                               // acquisition of the number of vowels
    fprintf(stdout, "\n--- The program is execute ---\n");
    filePointer = fopen(string, "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d", &number);                                                                                                         // reading the file
    for (index = substring = 0; (index < number) && (feof(filePointer) == FALSE); ++index) {
        fscanf(filePointer, "%s", string);
        if (feof(filePointer) != FALSE) {
            break;
        }
        substring += conta(string, length, vowels);
        fprintf(stdout, "\tThe number of %d long substrings containing %d vowels is: %d\n", length, vowels, conta(string, length, vowels));
    }
    fclose(filePointer);
    fprintf(stdout, "\n\tThe total of %d long substrings containing %d vowels is: %d\n", length, vowels, substring);
    return 0;
}

int conta(char *S, int n, int p) {
    int finish;             // index that mark the end of the substring
    int write;              // index that mark the position of the last cell write in the circular buffer
    int length;             // length of the string S
    int index;              // index that mark the start of the substring
    int read;               // index that mark the position of the last cell read in the circular buffer
    int partialCounter;     // counter of the vowels
    int v[n];               // circular buffer that trace the index of vowels
    int counter;            // counter of the substring with almost p vowels

    write = read = partialCounter = counter = 0;
    length = strlen(S);
    for (finish = 0; finish < n; finish++) {                    // cycle that analyzes the first substring
        if (S[finish] == 'A' || S[finish] == 'a' ||             // if that determines if the letter is a vowels
            S[finish] == 'E' || S[finish] == 'e' ||
            S[finish] == 'I' || S[finish] == 'i' ||
            S[finish] == 'O' || S[finish] == 'o' ||
            S[finish] == 'U' || S[finish] == 'u') {
            v[write++] = finish;
            partialCounter++;
        }
    }
    if (partialCounter == p) {                                  // if that checks if there were p vowels in the substring
        counter++;
    }
    for (index = 0; finish < length; index++, finish++) {
        if (v[read] == index) {                                 // if that removes the vowels already considered
            read++;
            read = read % n;
            partialCounter--;
        }
        if (S[finish] == 'A' || S[finish] == 'a' ||             // if that determines if the letter is a vowels
            S[finish] == 'E' || S[finish] == 'e' ||
            S[finish] == 'I' || S[finish] == 'i' ||
            S[finish] == 'O' || S[finish] == 'o' ||
            S[finish] == 'U' || S[finish] == 'u') {
            v[write++] = finish;
            write = write % n;
            partialCounter++;
        }
        if (partialCounter == p) {                              // if that checks if there were p vowels in the substring
            counter++;
        }
    }
    return counter;
}