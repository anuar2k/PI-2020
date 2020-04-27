#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool visited;
    bool recurCall;
} vertex;

typedef struct {
    int n;
    int time;
    bool **edges;
    vertex *vertices;
    int *order;
} graph;

int dfsVisit(graph *graph, int v) {
    graph->vertices[v].visited = true;
    graph->vertices[v].recurCall = true;

    for (int u = 0; u < graph->n; u++) {
        if (graph->edges[v][u] && 
           (graph->vertices[u].recurCall || (!graph->vertices[u].visited && dfsVisit(graph, u)))) {
            return true;
        }
    }

    graph->vertices[v].recurCall = false;
    graph->order[--graph->time] = v;
    return false;
}

int main() {
    graph graph;
    int k;

    scanf("%d %d", &graph.n, &k);
    graph.time = graph.n;

    bool *memBlock = malloc(graph.n * graph.n * sizeof(*memBlock));
    graph.edges = malloc(graph.n * sizeof(*graph.edges));
    graph.vertices = malloc(graph.n * sizeof(*graph.vertices));
    graph.order = malloc(graph.n * sizeof(*graph.order));

    for (int i = 0; i < graph.n; i++) {
        graph.edges[i] = memBlock + i * graph.n;

        graph.vertices[i].visited = false;
        graph.vertices[i].recurCall = false;
        for (int j = 0; j < graph.n; j++) {
            graph.edges[i][j] = false;
        }
    }

    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        graph.edges[a][b] = true;
    }

    bool ok = true;
    for (int v = 0; v < graph.n; v++) {
        if (!graph.vertices[v].visited) {
            if (dfsVisit(&graph, v)) {
                ok = false;
                break;
            }
        }
    }

    if (ok) {
        printf("OK\n");
        for (int i = 0; i < graph.n; i++) {
            printf("%d\n", graph.order[i]);
        }
    }
    else {
        printf("CYCLE\n");
    }

    free(graph.order);
    free(graph.vertices);
    free(graph.edges);
    free(memBlock);
}