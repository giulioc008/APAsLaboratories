#include <assert.h>
#include "graph.h"
#include "list.h"
#include <limits.h>
#include "symbolTable.h"
#include <stdlib.h>

#define MAXWEIGHT INT_MAX

typedef struct _graph {
    int E, V, **matrixAdj;
    link *listAdj;
    ST symbolTable;
} graph;

static Edge EDGEcreate(int vertexV, int vertexW, int weight) {
    Edge x;

    x.vertexV = vertexV;
    x.vertexW = vertexW;
    x.weight = weight;
    return x;
}
static void insertE(Graph G, Edge e) {
    if(G->matrixAdj[e.vertexV][e.vertexW] == MAXWEIGHT && G->matrixAdj[e.vertexW][e.vertexV] == MAXWEIGHT) {
        G->E++;
        G->matrixAdj[e.vertexV][e.vertexW] = G->matrixAdj[e.vertexW][e.vertexV] = e.weight;
    }
}
static int **MATRIXinit(int row, int column) {
    int i, j;                                                                                                           // the indexes
    int **matrix;                                                                                                       // the matrix

    matrix = (int **) malloc(row * sizeof(int *));
    assert(matrix != NULL);
    for(i = 0; i < row; i++) {                                                                                          // cycle on the row
        matrix[i] = (int *) malloc(column * sizeof(int));
        assert(matrix[i] != NULL);
        for(j = 0; j < column; j++) {                                                                                   // cycle on the column
            matrix[i][j] = MAXWEIGHT;
        }
    }
    return matrix;
}
static void removeE(Graph G, Edge e)  {
    if(G->matrixAdj[e.vertexV][e.vertexW] != MAXWEIGHT && G->matrixAdj[e.vertexW][e.vertexV] != MAXWEIGHT) {
        G->E--;
        G->matrixAdj[e.vertexV][e.vertexW] = G->matrixAdj[e.vertexW][e.vertexV] = MAXWEIGHT;
    }
}
void GRAPHedges(Graph G, Edge *x) {
    int i, j, E;                                                                                                        // the indexes

    E = 0;
    for(i = 0; i < G->V; i++) {                                                                                         // cycle on the row
        for(j = i + 1; j < G->V; j++) {                                                                                 // cycle on the column
            if(G->matrixAdj[i][j] != MAXWEIGHT) {                                                                       // if that checks if exists the edge
                x[E++] = EDGEcreate(i, j, G->matrixAdj[i][j]);
            }
        }
    }
}
int GRAPHedgesOfVertex(Graph G, Edge *x, int vertexV) {
    int i, E;                                                                                                           // the indexes

    E = 0;
    for(i = 0; i < G->V; i++) {                                                                                         // cycle on the row
        if(G->matrixAdj[vertexV][i] != MAXWEIGHT) {                                                                     // if that checks if exists the edge
            x[E++] = EDGEcreate(vertexV, i, G->matrixAdj[vertexV][i]);
        }
    }
    return E;
}
void GRAPHfree(Graph G) {
    int i;                                                                                                              // the index

    STfree(G->symbolTable);
    for(i = 0; i < G->V; i++) {                                                                                         // cycle on the matrix of the adjacencies
        free(G->matrixAdj[i]);
    }
    free(G->matrixAdj);
    if(G->listAdj != NULL) {
        for (i = 0; i < G->V; i ++) {                                                                                   // cycle on the list of the adjacencies
            LISTfree(&G->listAdj[i]);
        }
        free(G->listAdj);
    }
    free(G);
}
void GRAPHinit(Graph G) {
    STrealloc(G->symbolTable);
    STorder(G->symbolTable);
    G->E = 0;
    G->V = STlength(G->symbolTable);
    G->matrixAdj = MATRIXinit(G->V, G->V);
    G->listAdj = NULL;
}
void GRAPHinsertEdge(Graph G, int vertexV, int vertexW, int weight) {
    insertE(G, EDGEcreate(vertexV, vertexW, weight));
}
void GRAPHlistOfAdjacencies(Graph G) {
    int i, j;                                                                                                           // the indexes

    if(G->listAdj != NULL) {                                                                                            // if that checks if the list is empty
        for(i = 0; i < G->V; i++){                                                                                      // cycle on the list of the adjacencies
            LISTfree(&G->listAdj[i]);
        }
        free(G->listAdj);
    }
    G->listAdj = (link *) malloc(G->V * sizeof(link));
    assert(G->listAdj != NULL);
    for(i = 0; i < G->V; i++) {                                                                                         // cycle on the list of the adjacencies
        G->listAdj[i] = NULL;
    }
    for(i = 0; i < G->V; i++) {                                                                                         // cycle on the row
        for(j = 0; j < G->V; j++) {                                                                                     // cycle on the column
            if(G->matrixAdj[i][j] != MAXWEIGHT) {                                                                       // if that checks if exists the edge
                LISTinsertHeadPointer(&G->listAdj[i], j, G->matrixAdj[i][j]);
                LISTinsertHeadPointer(&G->listAdj[j], i, G->matrixAdj[i][j]);
            }
        }
    }
    fprintf(stdout, "\tThe list of the adjacencies was created\n");
}
int GRAPHnumberOfEdges(Graph G) {
    return G->E;
}
int GRAPHnumberOfVertex(Graph G) {
    return G->V;
}
void GRAPHreadEdge(Graph G, FILE *filePointer) {
    char buffer1[MAXLENGTH];                                                                                            // the buffer
    int weight, x, y;                                                                                                   // the auxiliary parameters

    for(; feof(filePointer) == FALSE;) {                                                                                // cycle on the file
        fscanf(filePointer,"%s %*s", buffer1);
        x = STsearchByName(G->symbolTable, buffer1);
        fscanf(filePointer,"%s %*s %d", buffer1, &weight);
        y = STsearchByName(G->symbolTable, buffer1);
        insertE(G, EDGEcreate(x, y, weight));
    }
}
void GRAPHreadVertex(Graph G, FILE *filePointer) {
    char buffer1[MAXLENGTH], buffer2[MAXLENGTH];                                                                        // the buffers

    for(; feof(filePointer) == FALSE;) {                                                                                // cycle on the file
        fscanf(filePointer,"%s %s", buffer1, buffer2);
        STinsert(G->symbolTable, buffer1, buffer2);
        fscanf(filePointer,"%s %s %*d", buffer1, buffer2);
        STinsert(G->symbolTable, buffer1, buffer2);
    }
}
Graph GRAPHpartialInit(int E) {
    Graph G;

    G = (Graph) malloc(sizeof(graph));
    assert(G != NULL);
    G->symbolTable = STinit(2 * E);
    return G;
}
void GRAPHremoveEdge(Graph G, int vertexV, int vertexW, int weight) {
    removeE(G, EDGEcreate(vertexV, vertexW, weight));
}
int GRAPHsearchEdgeMatrixOfAdjacencies(Graph G, int vertexV, int vertexW) {
    if(G->matrixAdj[vertexV][vertexW] != MAXWEIGHT &&G->matrixAdj[vertexW][vertexV] != MAXWEIGHT ) {                    // if that checks if there are the edge
        return 1;
    }
    return FALSE;
}
int GRAPHsearchEdgeListOfAdjacencies(Graph G, int vertexV, int vertexW) {
    if(LISTsearch(G->listAdj[vertexV], vertexW) != FALSE && LISTsearch(G->listAdj[vertexW], vertexV) != FALSE) {        // if that checks if there are the edge
        return 1;
    }
    return FALSE;
}
ST GRAPHsymbolTable(Graph G) {
    return G->symbolTable;
}
void GRAPHwrite(Graph G) {
    char buffer[MAXLENGTH];                                                                                             // the buffer
    Edge x[G->E];                                                                                                       // the vector of the edges
    FILE *filePointer;                                                                                                  // the file
    int i;                                                                                                              // the index

    printf("Output file name: ");
    scanf("%s", buffer);
    filePointer = fopen(buffer, "w");
    assert(filePointer != NULL);
    GRAPHedges(G, x);
    for(i = 0; i < G->E; i++) {                                                                                         // cycle on the edges
        fprintf(filePointer,"%s  %s %d\n", STsearchByIndex(G->symbolTable, x[i].vertexV), STsearchByIndex(G->symbolTable, x[i].vertexW), x[i].weight);
    }
    fclose(filePointer);
}