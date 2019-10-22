#include <assert.h>
#include "graph.h"
#include <stdlib.h>
#include <string.h>

typedef enum {
    edges,
    list,
    vertex,
    finish,
    error
} menu;                                                                                                                 // the menu

menu readMenuCommand();
int selectionMenu(Graph G, menu command);

int main(int argc, char **argv) {
    FILE *filePointer;                                                                                                  // the file
    Graph G;                                                                                                            // the graph
    int i;                                                                                                              // the index
    menu command;                                                                                                       // the command of the menu

    assert(argc == 2);
    filePointer = fopen(argv[1], "r");
    assert(filePointer != NULL);
    for (i = 0; fscanf(filePointer, "%*s %*s %*s %*s %*d") != EOF; i++);
    G = GRAPHpartialInit(i);
    rewind(filePointer);
    GRAPHreadVertex(G, filePointer);
    GRAPHinit(G);
    rewind(filePointer);
    GRAPHreadEdge(G, filePointer);
    fclose(filePointer);
    for(i = 1; i != FALSE;) {                                                                                           // loop
        command = readMenuCommand();
        i = selectionMenu(G, command);
    }
    GRAPHfree(G);
    return 0;
}

menu readMenuCommand() {
    char string[30 + 2];                                                                                                // string that read the command
    char table[4][30 + 1] = {"Print edges",                                                                             // matrix that contains the string of the command
                             "Create list of the adjacencies",
                             "Check 3 vertex",
                             "Exit"};
    int j;                                                                                                              // index used for cycling on the table
    menu index;                                                                                                         // index used for cycling on the menu

    fprintf(stdout, "Choose the operation.\nThe possibilities are:\n");
    for(j = 0; j < 4; j++) {                                                                                            // cycle on the table
        fprintf(stdout, "\t%s\n", table[j]);
    }
    fprintf(stdout, "Command: ");
    fgets(string, 30 + 2, stdin);
    string[strlen(string) - 1] = '\0';
    for(index = edges, j = 0; index < error && j < 4 && stricmp(string, table[j]) != 0; index++, j++);                  // cycle on the table and the menu
    return index;
}
int selectionMenu(Graph G, menu command) {
    char buffer[MAXLENGTH];                                                                                             // the buffer
    Edge *x;                                                                                                            // the vector of the edges
    int i;                                                                                                              // the index
    int j, k;                                                                                                           // the auxiliary variables

    switch(command){                                                                                                    // switch that regulates the operation
        case edges:
            x = (Edge *) malloc(GRAPHnumberOfEdges(G) * sizeof(Edge));
            assert(x != NULL);
            for (i = 0; i < GRAPHnumberOfVertex(G); i++) {                                                              // cycle on the vertex of the graph
                j = GRAPHedgesOfVertex(G, x, i);
                fprintf(stdout, "\tVertex: %s\n", STsearchByIndex(GRAPHsymbolTable(G), i));
                for (k = 0; k < j; k++) {                                                                               // cycle on the vector of edges
                    fprintf(stdout, "\t\tEdge: (%s, %s) Weight: %d\n", STsearchByIndex(GRAPHsymbolTable(G), x[k].vertexV), STsearchByIndex(GRAPHsymbolTable(G), x[k].vertexW), x[k].weight);
                }
            }
            free(x);
            break;
        case list:
            GRAPHlistOfAdjacencies(G);
            break;
        case vertex:
            fprintf(stdout, "\tInsert the name of the first vertex: ");
            fscanf(stdin,"%s", buffer);
            i = STsearchByName(GRAPHsymbolTable(G), buffer);
            if(i == -1) {                                                                                               // if that checks if exists the vertex
                break;
            }
            fprintf(stdout, "\tInsert the name of the second vertex: ");
            fscanf(stdin,"%s", buffer);
            j = STsearchByName(GRAPHsymbolTable(G), buffer);
            if(j == -1) {                                                                                               // if that checks if exists the vertex
                break;
            }
            fprintf(stdout, "\tInsert the name of the third vertex: ");
            fscanf(stdin,"%s", buffer);
            k = STsearchByName(GRAPHsymbolTable(G), buffer);
            if(k == -1) {                                                                                               // if that checks if exists the vertex
                break;
            }
            if(GRAPHsearchEdgeMatrixOfAdjacencies(G, i, j) != FALSE && GRAPHsearchEdgeMatrixOfAdjacencies(G, j, k) != FALSE && GRAPHsearchEdgeMatrixOfAdjacencies(G, k, i) != FALSE) {  // if that checks if the three vertex are forming a completed subgraph
                fprintf(stdout, "\tThe subgraph is completed\n");
            } else {
                fprintf(stdout, "\tThe subgraph isn't completed\n");
            }
            break;
        case finish:
            return FALSE;
        case error:
        default:
            break;
    }
    return 1;
}