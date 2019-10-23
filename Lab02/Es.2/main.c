#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

typedef struct {
    char code[30 + 1], departure[30 + 1], arrival[30 + 1], date[10 + 1], departureHour[8 + 1], arrivalHour[8 + 1];
    int delay;
} log, *Log;
typedef enum {
    date,
    departure,
    arrival,
    delay,
    totalDelay,
    finish,
    error
} menu;

void arrivals(Log logging, int length, char place[30 + 2]);
void departures(Log logging, int length, char place[30 + 2]);
void intervalOfDateAndDelay(Log logging, int length, menu command);
Log read(int *n);
menu readCommand();
int selection(Log logging, int length, menu command);
void totalsDelay(Log logging, int length, char code[30 + 2]);

int main() {
    int length;                                         // the length of the vector
    int flag;                                           // the flag that regulates the exit
    Log logging;                                        // the vector
    menu command;                                       // the user's command

    logging = read(&length);
    for(flag  = 1; flag != FALSE;) {                    // cycle that acquires data
        command = readCommand();
        flag = selection(logging, length, command);
    }
    return 0;
}

void arrivals(Log logging, int length, char place[30 + 2]) {
    int i;                                                                      // index

    fprintf(stdout, "The travel that arrives in %s are:\n", place);
    for(i = 0; i < length; i++){                                                // cycling on the vector
        if(stricmp(logging[i].arrival, place) == 0) {                           // if that checks if the arrival of the travel is equal to place
            fprintf(stdout, "\t%s %s %s %s %s %d\n", logging[i].code, logging[i].departure, logging[i].date, logging[i].departureHour, logging[i].arrivalHour, logging[i].delay);
        }
    }
}
void departures(Log logging, int length, char place[30 + 2]) {
    int i;                                                          // index

    fprintf(stdout, "The travel that leaves %s are:\n", place);
    for(i = 0; i < length; i++){                                    // cycling on the vector
        if(stricmp(logging[i].departure, place) == 0) {             // if that checks if the departure of the travel is equal to place
            fprintf(stdout, "\t%s %s %s %s %s %d\n", logging[i].code, logging[i].arrival, logging[i].date, logging[i].departureHour, logging[i].arrivalHour, logging[i].delay);
        }
    }
}
void intervalOfDateAndDelay(Log logging, int length, menu command) {
    char dates[2][10 + 2];                                                                                                           // vector contains the dates
    int i;                                                                                                                           // index

    for(i = 0; i < 2; i++) {                                                                                                         // acquisition of dates
        fprintf(stdout, "Insert the %d date with the format AAAA/MM/DD: ", i + 1);
        fgets(dates[i], 10 + 2, stdin);
        dates[i][strlen(dates[i]) - 1] = '\0';
    }
    fprintf(stdout, "The travel that starts in the interval between %s and %s and that having a delay are:\n", dates[0], dates[1]);
    for(i = 0; i < length; i++) {                                                                                                    // cycling on the vector
        if(strcmp(logging[i].date, dates[0]) >= 0 && strcmp(logging[i].date, dates[1]) <= 0) {                                       // if that checks if the date is in the interval
            if(command == date) {                                                                                                    // if that checks the command
                fprintf(stdout, "\t%s %s %s %s %s %s %d\n", logging[i].code, logging[i].departure, logging[i].arrival, logging[i].date, logging[i].departureHour, logging[i].arrivalHour, logging[i].delay);
            } else {
                if (logging[i].delay != 0) {                                                                                         // if that checks if the travel has a delay
                    fprintf(stdout, "\t%s %s %s %s %s %s %d\n", logging[i].code, logging[i].departure, logging[i].arrival, logging[i].date, logging[i].departureHour, logging[i].arrivalHour, logging[i].delay);
                }
            }
        }
    }
}
Log read(int * n) {
    FILE *filePointer;                                                       // the file
    int i;                                                                   // index
    Log logging;                                                             // the vector

    filePointer = fopen("log.txt", "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d", n);                                            // reading the file
    assert(*n <= 1000);
    logging = (Log) malloc(*n * sizeof(log));
    assert(logging != NULL);
    for (i = 0; i < *n; i++) {                                               // cycle on the vector
        fscanf(filePointer, "%s %s %s %s %s %s %d", logging[i].code, logging[i].departure, logging[i].arrival, logging[i].date, logging[i].departureHour, logging[i].arrivalHour, &logging[i].delay);
    }
    fclose(filePointer);
    return logging;
}
menu readCommand() {
    char string[11 + 2];                                                                                // string that read the command
    char table[6][11 + 1] = {"Date", "Departure", "Arrival", "Delay", "Total delay", "Exit"};           // matrix that contains the command
    int j;                                                                                              // index used for cycling on the table
    menu index;                                                                                         // index used for cycling on the menu

    fprintf(stdout, "Choose the instruction to execute.\nThe instruction are:");
    for(j = 0; j < 6; j++) {                                                                            // cycle on the table
        fprintf(stdout, "\n\t%s", table[j]);
    }
    fprintf(stdout, "\nCommand: ");
    fgets(string, 11 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = date, j = 0; index < error && j < 6 && stricmp(string, table[j]) != 0; index++, j++);   // cycle on the table and the menu
    return index;
}
int selection(Log logging, int length, menu command) {
    char string[30 + 2];                                                                    // string that rappresents the place of the departure or of the arrival and the code of the travel

    switch(command) {                                                                       // switch between the various command
        case date:
            intervalOfDateAndDelay(logging, length, command);
            break;
        case departure:
            fprintf(stdout, "Insert the place of the departure: ");
            fgets(string, 30 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            departures(logging, length, string);
            break;
        case arrival:
            fprintf(stdout, "Insert the place of the arrival: ");
            fgets(string, 30 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            arrivals(logging, length, string);
            break;
        case delay:
            intervalOfDateAndDelay(logging, length, command);
            break;
        case totalDelay:
            fprintf(stdout, "Insert the code of the travel: ");
            fgets(string, 30 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            totalsDelay(logging, length, string);
            break;
        case finish:
            return FALSE;
        case error:
            fprintf(stderr, "\n\tFatal Error\n");
            return FALSE;
        default:
            return FALSE;
    }
    fprintf(stdout, "\n");
    return 1;
}
void totalsDelay(Log logging, int length, char code[30 + 2]) {
    int i;                                                                          // index
    int total;                                                                      // the total delay of the travel

    for(i = total = 0; i < length; i++){                                            // cycling on the vector
        if(stricmp(logging[i].code, code) == 0) {                                   // if thats checks if the code of the travel is equal to code
            total += logging[i].delay;
        }
    }
    fprintf(stdout, "The total delay of the taxi %s is: %d min.\n", code, total);
}