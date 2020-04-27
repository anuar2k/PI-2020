#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool reached;
    bool extracted;
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
        graph->vertices[i].extracted = false;
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

void dijkstra(graph *graph, int source) {
    initialize_single_source(graph, source);
    for (int i = 0; i < graph->n; i++) {
        int u = -1;
        for (int v = 0; v < graph->n; v++) {
            if (!graph->vertices[v].extracted) {
                if (u == -1 || 
                    !graph->vertices[u].reached || 
                    (graph->vertices[v].reached && graph->vertices[u].distance > graph->vertices[v].distance)) {
                    u = v;
                }
            }
        }
        graph->vertices[u].extracted = true;

        for (int v = 0; v < graph->n; v++) {
            if (graph->edges[u][v].exists && !graph->vertices[v].extracted) {
                relax(graph, u, v);
            }
        }
    }
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
        if (graph.edges[u][v].exists && weight > graph.edges[u][v].weight) {
            weight = graph.edges[u][v].weight;
        }
        graph.edges[u][v].exists = true;
        graph.edges[u][v].weight = weight;
        graph.edges[v][u].exists = true;
        graph.edges[v][u].weight = weight;
    }

    dijkstra(&graph, source);
    printf("%d\n", graph.vertices[target].distance);

    free(graph.vertices);
    free(memBlock);
    free(graph.edges);
}