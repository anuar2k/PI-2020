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
    int n, q;
    scanf("%d %d %d", &graph.n, &n, &q);

    graph.edges = malloc(graph.n * sizeof(*graph.edges));
    edge *memBlock = malloc(graph.n * graph.n * sizeof(*memBlock));
    graph.vertices = malloc(graph.n * sizeof(*graph.vertices));

    for (int i = 0; i < graph.n; i++) {
        graph.edges[i] = memBlock + i * graph.n;
        
        for (int j = 0; j < graph.n; j++) {
            graph.edges[i][j].exists = false;
        }
    }

    for (int i = 0; i < n; i++) {
        int stations, prev_station;
        scanf("%d %d", &stations, &prev_station);
        while (--stations) {
            int time, next_station;
            scanf("%d %d", &time, &next_station);
            if (graph.edges[prev_station][next_station].exists && time > graph.edges[prev_station][next_station].weight) {
                time = graph.edges[prev_station][next_station].weight;
            }
            graph.edges[prev_station][next_station].exists = true;
            graph.edges[prev_station][next_station].weight = time;
            graph.edges[next_station][prev_station].exists = true;
            graph.edges[next_station][prev_station].weight = time;
            prev_station = next_station;
        }
    }

    for (int i = 0; i < q; i++) {
        int source, target;
        scanf("%d %d", &source, &target);
        dijkstra(&graph, source);
        printf("%d\n", graph.vertices[target].distance);
    }

    free(graph.vertices);
    free(memBlock);
    free(graph.edges);
}