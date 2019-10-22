#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

char *regEx(char *src, char *regex, int *length);

int main() {
    char *string;                                                                           // the string
    char *result;                                                                           // the result of the RegEx
    char *regex;                                                                            // the RegEx
    int length;                                                                             // the effective length of the RegEx

    string = strdup("Torino");
    regex = strdup("\\Aor\\a[^ckl]");
    result = regEx(string, regex, &length);
    if (result == NULL) {                                                                   // if that checks if the RegEx has product an output
        fprintf(stdout, "The RegEx \"%s\" hasn't product an output\n", regex);
    } else {
        fprintf(stdout, "The RegEx \"%s\" has product the output: \"%s\"\nThe RegEx is valid for the first %d-th characters of the output\n", regex, result, length);
    }
    return 0;
}

char *regEx(char *src, char *regex, int *length) {
    int i;                                                                                              // the index of the string
    int j;                                                                                              // the index of the RegEx
    int flag;                                                                                           // the flag used for the RegEx [%s] or [^%s]
    int regexLength;                                                                                    // the length of the RegEx
    int srcLength;                                                                                      // the length of the string

    regexLength = strlen(regex);
    srcLength = strlen(src);
    for(i = j = *length = 0; i < srcLength && j < regexLength && *length < regexLength; j++) {          // cycle on the RegEx
        if(isalnum(regex[j]) != FALSE) {                                                                // if that checks if the j-th character of the RegEx is alphanumeric
            if(regex[j] != src[i + *length]) {                                                          // if that checks if the j-th character of the RegEx isn't equal to the (i + length)-th character of the string
                j = *length = 0;
                i++;
            } else {
                (*length)++;
            }
        } else {
            switch (regex[j]) {                                                                         // switch that checks if the j-th character of the RegEx is one of '\', '.' and '['
                case '\\':
                    j++;
                    switch (regex[j]) {                                                                 // switch that checks if the j-th character of the RegEx is one of 'a' and 'A'
                        case 'a':
                            if (islower(src[i + *length]) == FALSE) {                                   // if that checks if the (i + length)-th character of the string is lowercase
                                j = *length = 0;
                                i++;
                            } else {
                                (*length)++;
                            }
                            break;
                        case 'A':
                            if (isupper(src[i + *length]) == FALSE) {                                   // if that checks if the (i + length)-th character of the string is uppercase
                                j = *length = 0;
                                i++;
                            } else {
                                (*length)++;
                            }
                            break;
                        default:
                            fprintf(stderr, "\tThe RegEx \"%s\" is incorrect\n", regex);
                            break;
                    }
                    break;
                case '.':
                    if(isalnum(src[i + *length]) == FALSE) {                                            // if that checks if the (i + length)-th character of the string is alphanumeric
                        j = *length = 0;
                        i++;
                    } else {
                        (*length)++;
                    }
                    break;
                case '[':
                    flag = FALSE;
                    j++;
                    switch (regex[j]) {                                                                 // if that checks if the j-th character of the RegEx is equal to '^'
                        case '^':
                            for (j++; regex[j] != ']'; j++) {                                           // cycle on the RegEx
                                if (regex[j] == src[i + *length]) {                                     // if that checks if the (i + length)-th character of the string is equal to the j-th character of the RegEx
                                    flag = 1;
                                }
                            }
                            if (flag == 1) {                                                            // if that checks if the flag is true
                                j = *length = 0;
                                i++;
                            } else {
                                (*length)++;
                            }
                            break;
                        default:
                            for (; regex[j] != ']'; j++) {                                              // cycle on the RegEx
                                if (regex[j] == src[i + *length]) {                                     // if that checks if the (i + length)-th character of the string is equal to the j-th character of the RegEx
                                    flag = 1;
                                }
                            }
                            if (flag == FALSE) {                                                        // if that checks if the flag is false
                                j = *length = 0;
                                i++;
                            } else {
                                (*length)++;
                            }
                            break;
                    }
                    break;
                default:
                    fprintf(stderr, "\tThe RegEx \"%s\" is incorrect\n", regex);
                    break;
            }
        }
    }
    if(j == 0 || i == srcLength) {                                                                      // if that checks if the RegEx hasn't product an output
        return NULL;
    }
    return &src[i];
}