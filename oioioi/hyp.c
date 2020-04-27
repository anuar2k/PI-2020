#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool visited;
    int connGraphNo;
} vertex;

typedef struct {
    int n;
    bool **edges;
    vertex *vertices;
} graph;

void dfsVisit(graph graph, int connGraphNo, int v) {
    graph.vertices[v].visited = true;
    graph.vertices[v].connGraphNo = connGraphNo;

    for (int u = 0; u < graph.n; u++) {
        if (graph.edges[v][u] && !graph.vertices[u].visited) {
            dfsVisit(graph, connGraphNo, u);
        }
    }
}

int main() {
    graph graph;
    int k, p;

    scanf("%d %d %d", &graph.n, &k, &p);

    bool *memBlock = malloc(graph.n * graph.n * sizeof(*memBlock));
    graph.edges = malloc(graph.n * sizeof(*graph.edges));
    graph.vertices = malloc(graph.n * sizeof(*graph.vertices));

    for (int i = 0; i < graph.n; i++) {
        graph.edges[i] = memBlock + i * graph.n;

        graph.vertices[i].visited = false;
        for (int j = 0; j < graph.n; j++) {
            graph.edges[i][j] = false;
        }
    }

    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        graph.edges[a][b] = true;
        graph.edges[b][a] = true;
    }

    int connGraphNo = 0;
    for (int v = 0; v < graph.n; v++) {
        if (!graph.vertices[v].visited) {
            dfsVisit(graph, connGraphNo++, v);
        }
    }

    for (int i = 0; i < p; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        graph.vertices[a].connGraphNo == graph.vertices[b].connGraphNo ? printf("YES\n") : printf("NO\n");
    }

    free(graph.vertices);
    free(graph.edges);
    free(memBlock);
}