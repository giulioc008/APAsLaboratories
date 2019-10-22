#ifndef LAB10_3_GRAPH_H
#define LAB10_3_GRAPH_H

#include <stdio.h>
#include "symbolTable.h"

#define FALSE 0
#define MAXLENGTH 30 + 1

typedef struct {
    int vertexV, vertexW, weight;
} Edge;
typedef struct _graph *Graph;

void GRAPHedges(Graph G, Edge *x);
int GRAPHedgesOfVertex(Graph G, Edge *x, int vertexV);
void GRAPHfree(Graph G);
void GRAPHinit(Graph G);
void GRAPHinsertEdge(Graph G, int vertexV, int vertexW, int weight);
void GRAPHlistOfAdjacencies(Graph G);
int GRAPHnumberOfEdges(Graph G);
int GRAPHnumberOfVertex(Graph G);
void GRAPHreadEdge(Graph G, FILE *filePointer);
void GRAPHreadVertex(Graph G, FILE *filePointer);
Graph GRAPHpartialInit(int E);
void GRAPHremoveEdge(Graph G, int vertexV, int vertexW, int weight);
int GRAPHsearchEdgeMatrixOfAdjacencies(Graph G, int vertexV, int vertexW);
int GRAPHsearchEdgeListOfAdjacencies(Graph G, int vertexV, int vertexW);
ST GRAPHsymbolTable(Graph G);
void GRAPHwrite(Graph G);

#endif //LAB10_3_GRAPH_H