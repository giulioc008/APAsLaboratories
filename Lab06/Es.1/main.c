#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numberOfArch;
    int numberOfVertex;
    int *vertex;
    int **arch;
} graph;            // the graph

int isVertexCover(int *sol, int n, graph grafo);
void powerset(int *val, int k, int *sol, graph grafo);
void powersetR(int *val, int k, int *sol, int n, int pos, int start, graph grafo);
graph read();

int main() {
    graph grafo;                                                            // the graph
    int *solution;                                                          // the solution
    int i;                                                                  // the index

    grafo = read();
    solution = (int *) malloc(grafo.numberOfVertex * sizeof(int));
    fprintf(stdout, "The possible Vertex Cover are:\n");
    powerset(grafo.vertex, grafo.numberOfVertex, solution, grafo);
    free(solution);
    for (i = 0; i < grafo.numberOfArch; i++) {                              // cycle on the arches
        free(grafo.arch[i]);
    }
    free(grafo.arch);
    free(grafo.vertex);
    return 0;
}

int isVertexCover(int *sol, int n, graph grafo) {
    int i, j;                                                                       // the indexes
    int flag;                                                                       // the flag

    flag = 1;
    for (i = 0; i < grafo.numberOfArch && flag == 1; i++) {                         // cycle on the arches
        flag = 0;
        for (j = 0; j < n && flag == 0; j++) {                                      // cycle on the possible vertex cover
            if(grafo.arch[i][0] == sol[j] || grafo.arch[i][1] == sol[j]) {          // if that checks if sol contains a vertex cover
                flag = 1;
            }
        }
    }
    return flag;
}
void powerset(int *val, int k, int *sol, graph grafo) {
    int i;                                  // the index

    for(i = 1; i < k + 1; i++){             // cycle on the value of k
        powersetR(val, k, sol, i, 0, 0, grafo);
    }

}
void powersetR(int *val, int k, int *sol, int n, int pos, int start, graph grafo) {
    int i;                                                                                      // the index

    if (pos == n){                                                                              // if that checks the terminal case (vector full up to the n-th element)
        if(isVertexCover(sol, n, grafo) == 1) {
            for (i = 0; i < n; i++) {                                                           // cycle on the solution
                fprintf(stdout, "%s%d%s", i == 0 ? "\t{" : "", sol[i], i == n - 1 ? "}\n" : " ");
            }
        }
        return;
    }
    for (i = start; i < k; i++) {                                                               // cycle on the vertexes from the start-th element to the end
        sol[pos] = val[i];
        powersetR(val, k, sol, n, pos + 1, i + 1, grafo);                                       // recursion
    }
}
graph read() {
    FILE *filePointer;                                                                  // the file
    graph grafo;                                                                        // the graph
    int i;                                                                              // the index

    filePointer = fopen("grafo.txt", "r");
    fscanf(filePointer, "%d %d", &grafo.numberOfVertex, &grafo.numberOfArch);           // reading the file
    grafo.vertex = (int *) malloc(grafo.numberOfVertex * sizeof(int));
    assert(grafo.vertex != NULL);
    grafo.arch = (int **) malloc(grafo.numberOfArch * sizeof(int *));
    assert(grafo.arch != NULL);
    for (i = 0; i < grafo.numberOfVertex; i++) {                                        // cycle on the vertexes
        grafo.vertex[i] = i;
    }
    for (i = 0; i < grafo.numberOfArch; i++) {                                          // cycle on the arches
        grafo.arch[i] = (int *) malloc(2 * sizeof(int));
        assert(grafo.arch[i] != NULL);
        fscanf(filePointer, "%d %d", &grafo.arch[i][0], &grafo.arch[i][1]);
    }
    fclose(filePointer);
    return grafo;
}