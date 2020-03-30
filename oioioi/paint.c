#include <stdio.h>
#include <stdlib.h>

typedef struct {
    short x;
    short y;
    short color;
} to_paint;

size_t requestPaint(short **bitmap, int n, to_paint *queue, size_t head, short x, short y, short color) {
    if (x >= 0 && x < n && y >= 0 && y < n && bitmap[x][y] == 0) {
        queue[head].x = x;
        queue[head].y = y;
        queue[head].color = color;
        return (head + 1) % (n * n);
    }
    return head;
}

int main() {
    short n, k;
    scanf("%hd %hd", &n, &k);

    short **bitmap = malloc(n * sizeof(*bitmap));
    short *memBlock = malloc(n * n * sizeof(*memBlock));
    to_paint *queue = malloc(n * n * sizeof(*queue));

    for (int i = 0; i < n; i++) {
        bitmap[i] = memBlock + i * n;
    }

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            scanf("%hd", &bitmap[x][y]);
        }
    }

    while (k--) {
        size_t head = 1;
        size_t tail = 0;
        scanf("%hd %hd %hd", &queue[0].x, &queue[0].y, &queue[0].color);
        while (head != tail) {
            short x = queue[tail].x;
            short y = queue[tail].y;
            short color = queue[tail].color;
            if (bitmap[x][y] == 0) {
                bitmap[x][y] = color;
                head = requestPaint(bitmap, n, queue, head, x    , y - 1, color);
                head = requestPaint(bitmap, n, queue, head, x + 1, y    , color);
                head = requestPaint(bitmap, n, queue, head, x    , y + 1, color);
                head = requestPaint(bitmap, n, queue, head, x - 1, y    , color);
            }
            tail = (tail + 1) % (n * n);
        }
    }

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            printf("%d ", bitmap[x][y]);
        }
        printf("\n");
    }

    free(bitmap);
    free(memBlock);
    free(queue);
}