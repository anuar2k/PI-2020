#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 10;
const int MINVAL = -10;
const int MAXVAL = 10;

const int SPAN = MAXVAL - MINVAL + 1;

//utils
void printArr(int[], int);
int getRand(void);

int getRand(void) {
  return (rand() % SPAN) + MINVAL;
}

int main(void) {
  srand(time(NULL));
  
  int T[N];
  int hist[SPAN];
  for (int i = 0; i < SPAN; i++) {
    hist[i] = 0;
  }
  
  for (int i = 0; i < N; i++) {
    T[i] = getRand();
    hist[T[i] - MINVAL] += 1;
  }

  printArr(T, N);

  for (int i = 0; i < SPAN; i++) {
    printf("%d wystepuje %d razy (%f%%)\n", i + MINVAL, hist[i], hist[i] * 100.0 / N);
  }
}
void printArr(int t[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", t[i]);
  }
  printf("\n");
}
