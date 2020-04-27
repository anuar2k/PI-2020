#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int n;
    int pos;
    bool **edges;
    int *result;
} graph;

void dfsVisit(graph *graph, int v) {
    for (int u = 0; u < graph->n; u++) {
        if (graph->edges[v][u]) {
            graph->edges[v][u] = false;
            graph->edges[u][v] = false;
            dfsVisit(graph, u);
        }
    }
    graph->result[graph->pos++] = v;
}

int main() {
    int Z;
    scanf("%d", &Z);

    while (Z--) {
        graph graph;
        int m;

        scanf("%d %d", &graph.n, &m);
        graph.pos = 0;

        bool *memBlock = malloc(graph.n * graph.n * sizeof(*memBlock));
        graph.edges = malloc(graph.n * sizeof(*graph.edges));
        graph.result = malloc(graph.n * sizeof(*graph.result));

        for (int i = 0; i < graph.n; i++) {
            graph.edges[i] = memBlock + i * graph.n;

            for (int j = 0; j < graph.n; j++) {
                graph.edges[i][j] = false;
            }
        }

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);

            a--;
            b--;
            graph.edges[a][b] = true;
            graph.edges[b][a] = true;
        }
        int start = 0;
        for (int i = 0; i < graph.n; i++) {
            int count = 0;
            for (int j = 0; j < graph.n; j++) {
                if (graph.edges[i][j]) {
                    count++;
                }
            }
            if (count % 2 == 1) {
                start = i;
                break;
            }
        }

        dfsVisit(&graph, start);

        printf("1\n%d ", graph.n);
        for (int i = 0; i < graph.n; i++) {
            printf("%d ", graph.result[i] + 1);
        }
        printf("\n");
        free(graph.edges);
        free(memBlock);

    }
}