#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define CLOSE -1

typedef struct {
    int day, month, year;
} date;             // the date
typedef struct {
    char code[5 + 1], name[50 + 1], surname[50 + 1], street[50 + 1], city[50 + 1];
    int cap;
    date birth;
} item;             // the collection of data relative to one person
typedef struct nodo node,*link;        // the node of the list
struct nodo {
    item data;
    link next, previous;
};
typedef struct {
    int length;
    link head, tail;
} list, *List;      // the list
typedef enum {
    new,
    search,
    delete,
    print,
    quit,
    error
} menu;               // the principal menu
typedef enum {
    byStandardInput,
    byFile,
    back,
    close,
    fatal
} addMenu;            // the menu that add a person to the log
typedef enum {
    ofOneElement,
    ofAnInterval,
    retro,
    finish,
    fail
} removeMenu;         // the menu that remove a person from the log

int compare(item x, item y);
link insert(link head, item data);
link newNode(item data, link next, link previous);
void printOnFilePointer(list log, FILE *filePointer);
list read();
addMenu readAddCommand();
link readByFilePointer(link head, FILE *filePointer);
menu readCommand();
removeMenu readRemoveCommand();
link searchByCode(list log, char *code);
link searchByDate(list log, item threshold);
int selectionAddMenu(List log, addMenu command);
int selectionMenu(List log, menu command);
int selectionRemoveMenu(List log, removeMenu command);

int main() {
    list log;                                           // the list
    int flag;                                           // the flag
    menu command;                                       // the user's command

    log = read();
    for(flag = 1; flag != FALSE && flag != CLOSE;) {    // loop
        command = readCommand();
        flag = selectionMenu(&log, command);
    }
    return 0;
}

int compare(item x, item y) {
    if(x.birth.year > y.birth.year) {
        return 1;
    } else if(x.birth.year == y.birth.year) {
        if(x.birth.month > y.birth.month) {
            return 1;
        } else if(x.birth.month == y.birth.month) {
            if(x.birth.day > y.birth.day) {
                return 1;
            } else if(x.birth.day == y.birth.day) {
                return 0;
            }
        }
    }
    return -1;
}
link insert(link head, item data) {
    link x;                                                                                            // the index
    link p;                                                                                            // the previous element of the index

    if(head == NULL || compare(head -> data, data) < 0) {                                              // if that checks if the ist is empty or if the item data must be insert in head
        x = newNode(data, head, NULL);
        if(head != NULL) {
            head -> previous = x;
        }
        return x;
    }
    for(x = head -> next, p = head; x != NULL && compare(data, x -> data) < 0; p = x, x = x -> next);  // cycle on the list
    p -> next = newNode(data, x, p);
    if(x != NULL) {
        x -> previous = p -> next;
    }
    return head;
}
link newNode(item data, link next, link previous) {
    link x;                             // the node

    x = (link) malloc(sizeof(node));
    if(x != NULL) {                     // if that checks if the node is correctly allocated
        x -> data = data;
        x -> next = next;
        x -> previous = previous;
    }
    return x;
}
void printOnFilePointer(list log, FILE *filePointer) {
    link x;                                             // the index

    for(x = log.head; x != NULL; x = x -> next) {       // cycle on the list
        if(x -> next == NULL) {
            fprintf(filePointer, "%s %s %s %02d/%02d/%04d %s %s %d", x->data.code, x->data.name, x->data.surname, x->data.birth.day, x->data.birth.month, x->data.birth.year, x->data.street, x->data.city, x->data.cap);
        } else {
            fprintf(filePointer, "%s %s %s %02d/%02d/%04d %s %s %d\n", x->data.code, x->data.name, x->data.surname, x->data.birth.day, x->data.birth.month, x->data.birth.year, x->data.street, x->data.city, x->data.cap);
        }
    }
}
list read() {
    FILE *filePointer;                              // the file
    item x;                                         // the auxiliary data
    list log;                                       // the list

    log.length = 0;
    log.head = log.tail = NULL;
    filePointer = fopen("example.txt", "r");
    for(; feof(filePointer) == FALSE;) {
        fscanf(filePointer, "%s %s %s %d/%d/%d %s %s %d", x.code, x.name, x.surname, &x.birth.day, &x.birth.month, &x.birth.year, x.street, x.city, &x.cap);
        log.head = insert(log.head, x);
        log.length++;
    }
    fclose(filePointer);
    return log;
}
addMenu readAddCommand() {
    char string[21 + 2];                                                                                                // string that read the command
    char table[4][21 + 1] = {"By the Standard Input",                                                                   // matrix that contains the string of the command
                             "By a file",
                             "Return",
                             "Exit"};
    int j;                                                                                                              // index used for cycling on the table
    addMenu index;                                                                                                      // index used for cycling on the subMenu

    fprintf(stdout, "\tChoose the source.\n\tThe possibilities are:");
    for(j = 0; j < 4; j++) {                                                                                            // cycle on the table
        fprintf(stdout, "\n\t\t%s", table[j]);
    }
    fprintf(stdout, "\n\tCommand: ");
    fgets(string, 21 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = byStandardInput, j = 0; index < fatal && j < 4 && stricmp(string, table[j]) != 0; index++, j++);        // cycle on the table and the menu
    return index;
}
link readByFilePointer(link head, FILE *filePointer) {
    item x;                                             // the auxiliary item
    link y;                                             // the auxiliary node

    fscanf(filePointer, "%s %s %s %d/%d/%d %s %s %d", x.code, x.name, x.surname, &x.birth.day, &x.birth.month, &x.birth.year, x.street, x.city, &x.cap);
    y = insert(head, x);
    return y;
}
menu readCommand() {
    char string[20 + 2];                                                                                    // string that read the command
    char table[5][20 + 1] = {"Add an element",                                                              // matrix that contains the string of the command
                             "Search of an element",
                             "Extract an element",
                             "Print of the list",
                             "Exit"};
    int j;                                                                                                  // index used for cycling on the table
    menu index;                                                                                             // index used for cycling on the subMenu

    fprintf(stdout, "Choose the operation.\nThe possibilities are:");
    for(j = 0; j < 5; j++) {                                                                                // cycle on the table
        fprintf(stdout, "\n\t%s", table[j]);
    }
    fprintf(stdout, "\nCommand: ");
    fgets(string, 20 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = new, j = 0; index < error && j < 5 && stricmp(string, table[j]) != 0; index++, j++);        // cycle on the table and the menu
    return index;
}
removeMenu readRemoveCommand() {
    char string[45 + 2];                                                                                                // string that read the command
    char table[4][45 + 1] = {"Remove an element",                                                                       // matrix that contains the string of the command
                             "Remove all the element in an interval of time",
                             "Return",
                             "Exit"};
    int j;                                                                                                              // index used for cycling on the table
    removeMenu index;                                                                                                   // index used for cycling on the subMenu

    fprintf(stdout, "\tChoose the operation.\n\tThe possibilities are:");
    for(j = 0; j < 4; j++) {                                                                                            // cycle on the table
        fprintf(stdout, "\n\t\t%s", table[j]);
    }
    fprintf(stdout, "\n\tCommand: ");
    fgets(string, 45 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = ofOneElement, j = 0; index < fail && j < 4 && stricmp(string, table[j]) != 0; index++, j++);            // cycle on the table and the menu
    return index;
}
link searchByCode(list log, char *code) {
    link x;                                             // the index

    for(x = log.head; x != NULL; x = x -> next) {       // cycle on the list
        if(stricmp(x -> data.code, code) == 0) {
            return x;
        }
    }
    return NULL;
}
link searchByDate(list log, item threshold) {
    link x;                                                                                  // the index

    for(x = log.head; x != NULL && compare(x -> data, threshold) >= 0; x = x -> next);       // cycle on the list
    if(x != NULL) {
        x = x -> previous;
    }
    return x;
}
int selectionAddMenu(List log, addMenu command) {
    char string[30 + 1];                                        // the string that contains the name of the file
    FILE *filePointer;                                          // the file

    switch (command) {                                          // switch that choose the operation
        case byStandardInput:
            fprintf(stdout, "\tInsert the data in the format <code> <name> <surname> <date of birth>(DD/MM/YYYY) <street> <city> <cap>: ");
            log->head = readByFilePointer(log->head, stdin);
            log->length++;
            break;
        case byFile:
            fprintf(stdout, "\tInsert the name of the file: ");
            fgets(string, 30 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            filePointer = fopen(string, "r");
            for(; feof(filePointer) == FALSE;) {
                log->head = readByFilePointer(log->head, filePointer);
                log->length++;
            }
            fclose(filePointer);
            break;
        case back:
            return FALSE;
        case close:
            return CLOSE;
        case fatal:
            fprintf(stderr, "\tError\n");
            break;
        default:
            return FALSE;
    }
    return 1;
}
int selectionMenu(List log, menu command) {
    addMenu addCommand;                                         // the command relative to the submenu that add a new person to the log
    char string[30 + 1];                                        // the string that contains the name of the file
    FILE *filePointer;                                          // the file
    int flag;                                                   // the flag that regulates the exit
    link x;                                                     // the auxiliary node
    removeMenu removeCommand;                                   // the command relative to the submenu that remove a person from the log

    switch (command) {                                          // switch that choose the operation
        case new:
            for(flag = 1; flag != FALSE && flag != CLOSE;) {    // loop
                addCommand = readAddCommand();
                flag = selectionAddMenu(log, addCommand);
            }
            if(flag == CLOSE) {                                 // if that checks the flag
                return flag;
            }
            break;
        case search:
            fprintf(stdout, "\tInsert the code to search: ");
            fgets(string, 30 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            x = searchByCode(*log, string);
            if(x != NULL) {                                     // if that checks if the search has an output
                fprintf(stdout, "\tThe output of the search is: %s %s %02d/%02d/%04d %s %s %d\n", x -> data.name, x -> data.surname, x -> data.birth.day, x -> data.birth.month, x -> data.birth.year, x -> data.street, x -> data.city, x -> data.cap);
            } else {
                fprintf(stdout, "\tThe search hasn't an output\n");
            }
            break;
        case delete:
            for(flag = 1; flag != FALSE && flag != CLOSE;) {    // loop
                removeCommand = readRemoveCommand();
                flag = selectionRemoveMenu(log, removeCommand);
            }
            if(flag == CLOSE) {                                 // if that checks the flag
                return flag;
            }
            break;
        case print:
            fprintf(stdout, "\tInsert the name of the file: ");
            fgets(string, 30 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            filePointer = fopen(string, "w");
            printOnFilePointer(*log, filePointer);
            fclose(filePointer);
            break;
        case quit:
            return CLOSE;
        case error:
            fprintf(stderr, "\tError\n");
            break;
        default:
            return FALSE;
    }
    return 1;
}
int selectionRemoveMenu(List log, removeMenu command) {
    char string[30 + 1];                                                                   // the string that contains the name of the file
    item y;                                                                                // the auxiliary item
    link x, z;                                                                             // the auxiliary nodes

    switch (command) {                                                                     // switch that choose the operation
        case ofOneElement:
            fprintf(stdout, "\tInsert the code to delete: ");
            fgets(string, 30 + 2, stdin);
            string[strlen(string) - 1] = '\0';
            x = searchByCode(*log, string);
            if(x != NULL) {                                                                // if that checks if the search has an output
                fprintf(stdout, "\tThe person who has been removed is: %s %s %02d/%02d/%04d %s %s %d\n", x -> data.name, x -> data.surname, x -> data.birth.day, x -> data.birth.month, x -> data.birth.year, x -> data.street, x -> data.city, x -> data.cap);
                if(x == log->head) {                                                       // if that checks if the node x is the head of the list
                    x -> next -> previous = NULL;
                    log->head = x -> next;
                } else {
                    x -> previous -> next = x -> next;
                    x -> next -> previous = x -> previous;
                }
                free(x);
                log->length--;
            } else {
                fprintf(stderr, "\tThis code doesn't exists\n");
            }
            break;
        case ofAnInterval:
            fprintf(stdout, "\tInsert the first date with the format DD/MM/YYYY: ");
            fscanf(stdin, "%d/%d/%d", &y.birth.day, &y.birth.month, &y.birth.year);
            x = searchByDate(*log, y);
            if(x != NULL) {                                                                // if that checks if the search has an output
                fprintf(stdout, "\tInsert the second date with the format DD/MM/YYYY: ");
                fscanf(stdin, "%d/%d/%d", &y.birth.day, &y.birth.month, &y.birth.year);
                if(x == log->head) {                                                       // if that checks if the node x is the head of the list
                    fprintf(stdout, "\tThe person who has been removed is: %s %s %02d/%02d/%04d %s %s %d\n", x -> data.name, x -> data.surname, x -> data.birth.day, x -> data.birth.month, x -> data.birth.year, x -> data.street, x -> data.city, x -> data.cap);
                    x -> next -> previous = NULL;
                    log->head = x -> next;
                    free(x);
                    log->length--;
                } else {
                    fprintf(stdout, "\tThe people who have been removed are:\n");
                    for(; x != NULL && compare(x -> data, y) <= 0; x = z) {                // cycle on the list
                        fprintf(stdout, "\t\t%s %s %s %02d/%02d/%04d %s %s %d\n", x -> data.code, x -> data.name, x -> data.surname, x -> data.birth.day, x -> data.birth.month, x -> data.birth.year, x -> data.street, x -> data.city, x -> data.cap);
                        if(x -> previous != NULL) {
                            x -> previous -> next = x -> next;
                            x -> next -> previous = x -> previous;
                        }
                        z = x -> previous;
                        free(x);
                        log->length--;
                    }
                }
            } else {
                fprintf(stderr, "\tThere isn't a person that is born after this date\n");
            }
            break;
        case retro:
            return FALSE;
        case finish:
            return CLOSE;
        case fail:
            fprintf(stderr, "\tError\n");
            break;
        default:
            return FALSE;
    }
    return 1;
}