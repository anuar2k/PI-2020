#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool reached;
    int distance;
} vertex;

typedef struct {
    bool exists;
    int weight;
} edge;

typedef struct {
    int n;
    edge **edges;
    vertex *vertices;
} graph;

void initialize_single_source(graph *graph, int source) {
    for (int i = 0; i < graph->n; i++) {
        graph->vertices[i].reached = false;
    }
    graph->vertices[source].reached = true;
    graph->vertices[source].distance = 0;
}

void relax(graph *graph, int u, int v) {
    int newDistance = graph->vertices[u].distance + graph->edges[u][v].weight;
    if (!graph->vertices[v].reached || graph->vertices[v].distance > newDistance) {
        graph->vertices[v].reached = true;
        graph->vertices[v].distance = newDistance;
    }
}

bool bellman_ford(graph *graph, int source) {
    initialize_single_source(graph, source);
    for (int i = 0; i < graph->n - 1; i++) {
        for (int u = 0; u < graph->n; u++) {
            for (int v = 0; v < graph->n; v++) {
                if (graph->edges[u][v].exists) {
                    relax(graph, u, v);
                }
            }
        }
    }
    for (int u = 0; u < graph->n; u++) {
        for (int v = 0; v < graph->n; v++) {
            if (graph->edges[u][v].exists) {
                if (graph->vertices[v].reached &&
                    graph->vertices[v].distance > graph->vertices[u].distance + graph->edges[u][v].weight) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    graph graph;
    int k, source, target;
    scanf("%d %d %d %d", &graph.n, &k, &source, &target);

    graph.edges = malloc(graph.n * sizeof(*graph.edges));
    edge *memBlock = malloc(graph.n * graph.n * sizeof(*memBlock));
    graph.vertices = malloc(graph.n * sizeof(*graph.vertices));

    for (int i = 0; i < graph.n; i++) {
        graph.edges[i] = memBlock + i * graph.n;
        
        for (int j = 0; j < graph.n; j++) {
            graph.edges[i][j].exists = false;
        }
    }

    for (int i = 0; i < k; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        graph.edges[u][v].exists = true;
        graph.edges[u][v].weight = weight;
    }

    if (bellman_ford(&graph, source)) {
        if (graph.vertices[target].reached) {
            printf("%d\n", graph.vertices[target].distance);
        }
        else {
            printf("NO\n");
        }
    }
    else {
        printf("CYCLE\n");
    }

    free(graph.vertices);
    free(memBlock);
    free(graph.edges);
}