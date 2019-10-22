#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOSE -1
#define FALSE 0

typedef struct {
    char code[30 + 1], departure[30 + 1], arrival[30 + 1], date[10 + 1], departureHour[8 + 1], arrivalHour[8 + 1];
    int delay;
} cell, *Cell;            // the cell of the vector
typedef struct {
    Cell vector, **multiOrderVector;
    int length;
} log, *Log;              // the struct that contains the data
typedef enum {
    date,
    departure,
    arrival,
    delay,
    totalDelay,
    print,
    order,
    search,
    reading,
    finish,
    error
} menu;                     // the principal menu
typedef enum {
    orderByDateAndTime,
    orderByCode,
    orderByDeparture,
    orderByArrival,
    retro,
    terminate,
    fail
} orderMenu;                // the submenu relative to the order
typedef enum {
    standard,
    file,
    back,
    quit,
    crash
} printMenu;                // the submenu relative to the print
typedef enum {
    searchByDeparture,
    behind,
    close,
    fatal
} searchMenu;               // the submenu relative to the search
typedef enum {
    none,
    byDateAndTime,
    byCode,
    byDeparture,
    byArrival,
    aback,
    out,
    death
} subPrintMenu;             // the submenu relative to vector to print

void intervalOfDateAndDelay(log logging, menu command);
void merge(Cell *vector, Cell *auxiliary, int l, int r, int q, orderMenu command);
void mergeSort(log logging, orderMenu command);
void mergeSortR(Cell *vector, int l, int r, orderMenu command);
void place(log logging, menu command);
void printOnFilePointer(Cell *vector, int length, FILE *filePointer, subPrintMenu command);
log read(char *fileName);
menu readCommand();
orderMenu readOrderCommand();
printMenu readPrintCommand();
searchMenu readSearchCommand();
subPrintMenu readSubPrintCommand();
void searchDeparture(log logging, char *place);
int selectionMenu(Log logging, menu command);
int selectionOrderMenu(log logging, orderMenu command);
int selectionPrintMenu(log logging, printMenu command);
int selectionSearchMenu(log logging, searchMenu command);
void selectionSubPrintMenu(log logging, subPrintMenu command, FILE *filePointer);
void totalsDelay(log logging);

int main() {
    int flag;                                           // the flag that regulates the exit
    log logging;                                        // the log
    menu command;                                       // the user's command

    logging = read("log.txt");
    for(flag = 1; flag != FALSE && flag != CLOSE;) {    // cycle that acquires data
        command = readCommand();
        flag = selectionMenu(&logging, command);
    }
    return 0;
}

void intervalOfDateAndDelay(log logging, menu command) {
    char dates[2][10 + 2];                                                                                                           // vector contains the dates
    int i;                                                                                                                           // index

    for(i = 0; i < 2; i++) {                                                                                                         // acquisition of dates
        fprintf(stdout, "\tInsert the %d date with the format AAAA/MM/DD: ", i + 1);
        fgets(dates[i], 10 + 2, stdin);
        dates[i][strlen(dates[i]) - 1] = '\0';
    }
    fprintf(stdout, "\tThe travel that starts in the interval between %s and %s and that having a delay are:\n", dates[0], dates[1]);
    for(i = 0; i < logging.length; i++) {                                                                                            // cycling on the vector
        if(strcmp(logging.vector[i].date, dates[0]) >= 0 && strcmp(logging.vector[i].date, dates[1]) <= 0) {                                   // if that checks if the date is in the interval
            if(command == date) {                                                                                                    // if that checks the command
                fprintf(stdout, "\t\t%s %s %s %s %s %s %d\n", logging.vector[i].code, logging.vector[i].departure, logging.vector[i].arrival, logging.vector[i].date, logging.vector[i].departureHour, logging.vector[i].arrivalHour, logging.vector[i].delay);
            } else {
                if (logging.vector[i].delay != 0) {                                                                                       // if that checks if the travel has a delay
                    fprintf(stdout, "\t\t%s %s %s %s %s %s %d\n", logging.vector[i].code, logging.vector[i].departure, logging.vector[i].arrival, logging.vector[i].date, logging.vector[i].departureHour, logging.vector[i].arrivalHour, logging.vector[i].delay);
                }
            }
        }
    }
}
void merge(Cell *vector, Cell *auxiliary, int l, int r, int q, orderMenu command) {
    int i;                                                                                          // index of the left subvector
    int j;                                                                                          // index of the right subvector
    int k;                                                                                          // index of the auxiliary vector

    switch(command) {                                                                               // switch between the various command
        case orderByDateAndTime:
            for(i = k = l, j = q + 1; k <= r; k++) {                                                // cycling on the vector
                if(i > q) {                                                                         // if that checks if the left subvector is empty
                    auxiliary[k] = vector[j++];
                } else if(j > r) {                                                                  // if that checks if the right subvector is empty
                    auxiliary[k] = vector[i++];
                } else {
                    switch (strcmp(vector[i] -> date, vector[j] -> date)) {                         // switch that checks if the left element is less, equal or greater then the right element
                        case -1:
                            auxiliary[k] = vector[i++];
                            break;
                        case 0:
                            switch (strcmp(vector[i] -> departureHour, vector[j] -> departureHour)) {
                                case -1:
                                    auxiliary[k] = vector[i++];
                                    break;
                                case 0:
                                    switch (strcmp(vector[i] -> arrivalHour, vector[j] -> arrivalHour)) {
                                        case -1:
                                        case 0:
                                            auxiliary[k] = vector[i++];
                                            break;
                                        case 1:
                                            auxiliary[k] = vector[j++];
                                            break;
                                        default:
                                            fprintf(stderr, "\n\t\tFatal Error\n");
                                            break;
                                    }
                                    break;
                                case 1:
                                    auxiliary[k] = vector[j++];
                                    break;
                                default:
                                    fprintf(stderr, "\n\t\tFatal Error\n");
                                    break;
                            }
                            break;
                        case 1:
                            auxiliary[k] = vector[j++];
                            break;
                        default:
                            fprintf(stderr, "\n\t\tFatal Error\n");
                            break;
                    }
                }
            }
            break;
        case orderByCode:
            for(i = k = l, j = q + 1; k <= r; k++) {                                                // cycling on the vector
                if(i > q) {                                                                         // if that checks if the left subvector is empty
                    auxiliary[k] = vector[j++];
                } else if(j > r) {                                                                  // if that checks if the right subvector is empty
                    auxiliary[k] = vector[i++];
                } else if(stricmp(vector[i] -> code, vector[j] -> code) <= 0) {                     // if that checks if the left element is less or equal to the right element
                    auxiliary[k] = vector[i++];
                } else {
                    auxiliary[k] = vector[j++];
                }
            }
            break;
        case orderByDeparture:
            for(i = k = l, j = q + 1; k <= r; k++) {                                                // cycling on the vector
                if(i > q) {                                                                         // if that checks if the left subvector is empty
                    auxiliary[k] = vector[j++];
                } else if(j > r) {                                                                  // if that checks if the right subvector is empty
                    auxiliary[k] = vector[i++];
                } else if(stricmp(vector[i] -> departure, vector[j] -> departure) <= 0) {           // if that checks if the left element is less or equal to the right element
                    auxiliary[k] = vector[i++];
                } else {
                    auxiliary[k] = vector[j++];
                }
            }
            break;
        case orderByArrival:
            for(i = k = l, j = q + 1; k <= r; k++) {                                                // cycling on the vector
                if(i > q) {                                                                         // if that checks if the left subvector is empty
                    auxiliary[k] = vector[j++];
                } else if(j > r) {                                                                  // if that checks if the right subvector is empty
                    auxiliary[k] = vector[i++];
                } else if(stricmp(vector[i] -> arrival, vector[j] -> arrival) <= 0) {               // if that checks if the left element is less or equal to the right element
                    auxiliary[k] = vector[i++];
                } else {
                    auxiliary[k] = vector[j++];
                }
            }
            break;
        case retro:
        case terminate:
        case fail:
        default:
            fprintf(stderr, "\n\t\tError\n");
            break;
    }
    for(k = l; k <= r; k++) {                                                                   // cycling on the vector
        vector[k] = auxiliary[k];
    }
}
void mergeSort(log logging, orderMenu command) {
    int l;                                                                                  // the left extreme
    int r;                                                                                  // the right extreme

    l = 0;
    r = logging.length - 1;
    mergeSortR(logging.multiOrderVector[command], l, r, command);
}
void mergeSortR(Cell *vector, int l, int r, orderMenu command) {
    Cell *auxiliary;                            // the auxiliary vector
    int q;                                      // the index of the middle element

    if(r <= l) {
        return;
    }
    auxiliary = (Cell *) malloc((r - l + 1) * sizeof(Cell));
    assert(auxiliary != NULL);
    q = (l + r) / 2;
    mergeSortR(vector, l, q, command);
    mergeSortR(vector, q + 1, r, command);
    merge(vector, auxiliary, l, r, q, command);
    free(auxiliary);
}
void place(log logging, menu command) {
    int i;                                                                  // index
    char place[30 + 2];                                                     // string that rappresents the place of the departure or of the arrival

    if(command == departure) {                                              // if that checks the command
        fprintf(stdout, "\tInsert the place of the departure: ");
    } else {
        fprintf(stdout, "\tInsert the place of the arrival: ");
    }
    fgets(place, 30 + 2, stdin);
    place[strlen(place) - 1] = '\0';
    if(command == departure) {                                              // if that checks the command
        fprintf(stdout, "\tThe travel that leaves %s are:\n", place);
    } else {
        fprintf(stdout, "\tThe travel that arrives in %s are:\n", place);
    }
    for(i = 0; i < logging.length; i++){                                    // cycling on the vector
        if(command == departure) {                                          // if that checks the command
            if(stricmp(logging.vector[i].departure, place) == 0) {               // if that checks if the departure of the travel is equal to place
                fprintf(stdout, "\t\t%s %s %s %s %s %d\n", logging.vector[i].code, logging.vector[i].arrival, logging.vector[i].date, logging.vector[i].departureHour, logging.vector[i].arrivalHour, logging.vector[i].delay);
            }
        } else {
            if(stricmp(logging.vector[i].arrival, place) == 0) {                 // if that checks if the arrival of the travel is equal to place
                fprintf(stdout, "\t\t%s %s %s %s %s %d\n", logging.vector[i].code, logging.vector[i].departure, logging.vector[i].date, logging.vector[i].departureHour, logging.vector[i].arrivalHour, logging.vector[i].delay);
            }
        }
    }
}
void printOnFilePointer(Cell *vector, int length, FILE *filePointer, subPrintMenu command) {
    int i;                                                                   // index

    fprintf(filePointer, "%d\n", length);                                    // writing the file
    for (i = 0; i < length; i++) {                                           // cycle on the vector
        if(command == none) {                                                // if that checks the command
            fprintf(filePointer, "%s %s %s %s %s %s %d\n", (*vector)[i].code, (*vector)[i].departure, (*vector)[i].arrival, (*vector)[i].date, (*vector)[i].departureHour, (*vector)[i].arrivalHour, (*vector)[i].delay);
        } else {
            fprintf(filePointer, "%s %s %s %s %s %s %d\n", vector[i] -> code, vector[i] -> departure, vector[i] -> arrival, vector[i] -> date, vector[i] -> departureHour, vector[i] -> arrivalHour, vector[i] -> delay);
        }
    }
}
log read(char * fileName) {
    FILE *filePointer;                                                       // the file
    int i, j;                                                                // indexes
    log logging;                                                             // the log

    filePointer = fopen(fileName, "r");
    assert(filePointer != NULL);
    fscanf(filePointer, "%d", &logging.length);                              // reading the file
    assert(logging.length <= 1000);
    logging.vector = (Cell) malloc(logging.length * sizeof(cell));
    assert(logging.vector != NULL);
    for (i = 0; i < logging.length; i++) {                                   // cycle on the vector
        fscanf(filePointer, "%s %s %s %s %s %s %d", logging.vector[i].code, logging.vector[i].departure, logging.vector[i].arrival, logging.vector[i].date, logging.vector[i].departureHour, logging.vector[i].arrivalHour, &logging.vector[i].delay);
    }
    fclose(filePointer);
    logging.multiOrderVector = (Cell **) malloc(retro * sizeof(Cell *));
    assert(logging.multiOrderVector != NULL);
    for (i = 0; i < retro; i++) {                                           // cycle on the multiorder vector
        logging.multiOrderVector[i] = (Cell *) malloc(logging.length * sizeof(Cell));
        assert(logging.multiOrderVector[i] != NULL);
        for (j = 0; j < logging.length; j++) {                              // cycle on the multiorder vector
            logging.multiOrderVector[i][j] = &logging.vector[j];
        }
    }
    return logging;
}
menu readCommand() {
    char string[11 + 2];                                                                                // string that read the command
    char table[10][11 + 1] = {"Date",                                                                    // matrix that contains the string of the command
                             "Departure",
                             "Arrival",
                             "Delay",
                             "Total delay",
                             "Print",
                             "Order",
                             "Search",
                             "Read",
                             "Exit"};
    int j;                                                                                              // index used for cycling on the table
    menu index;                                                                                         // index used for cycling on the menu

    fprintf(stdout, "Choose the instruction to execute.\nThe instruction are:");
    for(j = 0; j < 10; j++) {                                                                            // cycle on the table
        fprintf(stdout, "\n\t%s", table[j]);
    }
    fprintf(stdout, "\nCommand: ");
    fgets(string, 11 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = date, j = 0; index < error && j < 10 && stricmp(string, table[j]) != 0; index++, j++);   // cycle on the table and the menu
    return index;
}
orderMenu readOrderCommand() {
    char string[22 + 2];                                                                                             // string that read the command
    char table[6][22 + 1] = {"Order by date and time",                                                               // matrix that contains the string of the command
                             "Order by code",
                             "Order by departure",
                             "Order by arrival",
                             "Return",
                             "Exit"};
    int j;                                                                                                           // index used for cycling on the table
    orderMenu index;                                                                                                 // index used for cycling on the subMenu

    fprintf(stdout, "\tChoose the type of the order.\n\tThe possibilities are:");
    for(j = 0; j < 6; j++) {                                                                                         // cycle on the table
        fprintf(stdout, "\n\t\t%s", table[j]);
    }
    fprintf(stdout, "\n\tCommand: ");
    fgets(string, 22 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = orderByDateAndTime, j = 0; index < fail && j < 6 && stricmp(string, table[j]) != 0; index++, j++);   // cycle on the table and the menu
    return index;
}
printMenu readPrintCommand() {
    char string[22 + 2];                                                                                    // string that read the command
    char table[4][22 + 1] = {"On the standard output",                                                      // matrix that contains the string of the command
                             "On a file",
                             "Return",
                             "Exit"};
    int j;                                                                                                  // index used for cycling on the table
    printMenu index;                                                                                        // index used for cycling on the subMenu

    fprintf(stdout, "\tChoose the type of the output.\n\tThe possibilities are:");
    for(j = 0; j < 4; j++) {                                                                                // cycle on the table
        fprintf(stdout, "\n\t\t%s", table[j]);
    }
    fprintf(stdout, "\n\tCommand: ");
    fgets(string, 22 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = standard, j = 0; index < crash && j < 4 && stricmp(string, table[j]) != 0; index++, j++);   // cycle on the table and the menu
    return index;
}
searchMenu readSearchCommand() {
    char string[19 + 2];                                                                                             // string that read the command
    char table[3][19 + 1] = {"Search by departure",                                                                  // matrix that contains the string of the command
                             "Return",
                             "Exit"};
    int j;                                                                                                           // index used for cycling on the table
    searchMenu index;                                                                                                // index used for cycling on the subMenu

    fprintf(stdout, "\tChoose the type of the search.\n\tThe possibilities are:");
    for(j = 0; j < 3; j++) {                                                                                         // cycle on the table
        fprintf(stdout, "\n\t\t%s", table[j]);
    }
    fprintf(stdout, "\n\tCommand: ");
    fgets(string, 19 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = searchByDeparture, j = 0; index < fatal && j < 3 && stricmp(string, table[j]) != 0; index++, j++);   // cycle on the table and the menu
    return index;
}
subPrintMenu readSubPrintCommand() {
    char string[16 + 2];                                                                                    // string that read the command
    char table[7][16 + 1] = {"None",                                                                        // matrix that contains the string of the command
                             "By date and time",
                             "By code",
                             "By departure",
                             "By arrival",
                             "Return",
                             "Exit"};
    int j;                                                                                                  // index used for cycling on the table
    subPrintMenu index;                                                                                     // index used for cycling on the subMenu

    fprintf(stdout, "\tChoose the type of the output.\n\tThe possibilities are:");
    for(j = 0; j < 7; j++) {                                                                                // cycle on the table
        fprintf(stdout, "\n\t\t%s", table[j]);
    }
    fprintf(stdout, "\n\tCommand: ");
    fgets(string, 16 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = none, j = 0; index < death && j < 7 && stricmp(string, table[j]) != 0; index++, j++);       // cycle on the table and the menu
    return index;
}
void searchDeparture(log logging, char *place) {
    int l;                                                                                  // the left extreme
    int r;                                                                                  // the right extreme
    int q;                                                                                  // the index of the middle element

    l = 0;
    r = logging.length - 1;
    for(; l <= r;){                                                                         // cycling on the vector
        q = (l + r) / 2;
        switch(stricmp((*logging.multiOrderVector[q]) -> departure, place)) {               // if that checks if the departure of the travel is equal to place
            case -1:
                r = q - 1;
                break;
            case 0:
                fprintf(stdout, "\tThe search has product the output: %s %s %s %s %s %d\n", (*logging.multiOrderVector[q]) -> code, (*logging.multiOrderVector[q]) -> arrival, (*logging.multiOrderVector[q]) -> date, (*logging.multiOrderVector[q]) -> departureHour, (*logging.multiOrderVector[q]) -> arrivalHour, (*logging.multiOrderVector[q]) -> delay);
                return;
            case 1:
                l = q + 1;
                break;
            default:
                fprintf(stderr, "\n\t\tFatal Error\n");
                break;
        }
    }
    fprintf(stdout, "\tThe search haven't product an output.\n");
}
int selectionMenu(Log logging, menu command) {
    char buffer[30 + 2];                                                                    // string that read the name of the file
    int flag;                                                                               // the flag that regulates the exit
    orderMenu orderCommand;                                                                 // the subcommand for the ordering
    printMenu printCommand;                                                                 // the subcommand for the printing
    searchMenu searchCommand;                                                               // the subcommand for the searching

    switch(command) {                                                                       // switch between the various command
        case date:
            intervalOfDateAndDelay(*logging, command);
            break;
        case departure:
            place(*logging, command);
            break;
        case arrival:
            place(*logging, command);
            break;
        case delay:
            intervalOfDateAndDelay(*logging, command);
            break;
        case totalDelay:
            totalsDelay(*logging);
            break;
        case print:
            for(flag = 1; flag != FALSE && flag != CLOSE;) {
                printCommand = readPrintCommand();
                flag = selectionPrintMenu(*logging, printCommand);
            }
            if(flag == CLOSE) {
                return flag;
            }
            break;
        case order:
            for(flag = 1; flag != FALSE && flag != CLOSE;) {
                orderCommand = readOrderCommand();
                flag = selectionOrderMenu(*logging, orderCommand);
            }
            if(flag == CLOSE) {
                return flag;
            }
            break;
        case search:
            for(flag = 1; flag != FALSE && flag != CLOSE;) {
                searchCommand = readSearchCommand();
                flag = selectionSearchMenu(*logging, searchCommand);
            }
            if(flag == CLOSE) {
                return flag;
            }
            break;
        case reading:
            fprintf(stdout, "\tInsert the place of the departure: ");
            fgets(buffer, 30 + 2, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            *logging = read(buffer);
            break;
        case finish:
            return CLOSE;
        case error:
            fprintf(stderr, "\n\tError\n");
            break;
        default:
            return FALSE;
    }
    fprintf(stdout, "\n");
    return 1;
}
int selectionOrderMenu(log logging, orderMenu command) {
    switch(command) {                                                                       // switch between the various command
        case orderByDateAndTime:
        case orderByCode:
        case orderByDeparture:
        case orderByArrival:
            mergeSort(logging, command);
            break;
        case retro:
            return FALSE;
        case terminate:
            return CLOSE;
        case fail:
            fprintf(stderr, "\n\t\tError\n");
            break;
        default:
            return FALSE;
    }
    return 1;
}
int selectionPrintMenu(log logging, printMenu command) {
    char buffer[30 + 2];                                                                    // string that read the name of the file
    FILE *filePointer;                                                                      // the file
    subPrintMenu subPrintCommand;                                                           // the subcommand for the print of the vector

    switch(command) {                                                                       // switch between the various command
        case standard:
            subPrintCommand = readSubPrintCommand();
            selectionSubPrintMenu(logging, subPrintCommand, stdout);
            fprintf(stdout, "\n");
            break;
        case file:
            fprintf(stdout, "\t\tInsert the name of the file: ");
            fgets(buffer, 30 + 2, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            filePointer = fopen(buffer, "w");
            assert(filePointer != NULL);
            subPrintCommand = readSubPrintCommand();
            selectionSubPrintMenu(logging, subPrintCommand, filePointer);
            fclose(filePointer);
            break;
        case back:
            return FALSE;
        case quit:
            return CLOSE;
        case crash:
            fprintf(stderr, "\n\t\tError\n");
            break;
        default:
            return FALSE;
    }
    return 1;
}
int selectionSearchMenu(log logging, searchMenu command) {
    char buffer[30 + 2];                                                                    // string that read the departure

    switch(command) {                                                                       // switch between the various command
        case searchByDeparture:
            fprintf(stdout, "\tInsert the place of the departure: ");
            fgets(buffer, 30 + 2, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            searchDeparture(logging, buffer);
            break;
        case behind:
            return FALSE;
        case close:
            return CLOSE;
        case fatal:
            fprintf(stderr, "\n\t\tError\n");
            break;
        default:
            return FALSE;
    }
    return 1;
}
void selectionSubPrintMenu(log logging, subPrintMenu command, FILE *filePointer) {
    switch(command) {                                                                       // switch between the various command
        case none:
            printOnFilePointer(&logging.vector, logging.length, filePointer, command);
            break;
        case byDateAndTime:
        case byCode:
        case byDeparture:
        case byArrival:
            printOnFilePointer(logging.multiOrderVector[command - 1], logging.length, filePointer, command);
            break;
        case aback:
        case out:
        case death:
        default:
            fprintf(stderr, "\n\t\tError\n");
            break;
    }
}
void totalsDelay(log logging) {
    int i;                                                                          // index
    int total;                                                                      // the total delay of the travel
    char code[30 + 2];                                                              // string that rappresents the place of the departure or of the arrival and the code of the travel


    fprintf(stdout, "\tInsert the code of the travel: ");
    fgets(code, 30 + 2, stdin);
    code[strlen(code) - 1] = '\0';
    for(i = total = 0; i < logging.length; i++){                                    // cycling on the vector
        if(stricmp(logging.vector[i].code, code) == 0) {                                 // if thats checks if the code of the travel is equal to code
            total += logging.vector[i].delay;
        }
    }
    fprintf(stdout, "\tThe total delay of the taxi %s is: %d min.\n", code, total);
}