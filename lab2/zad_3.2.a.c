#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 4;
const int MINVAL = 0;
const int MAXVAL = 9;

const int SPAN = MAXVAL - MINVAL + 1;

//utils
void printArr(int[], int);
int getRand(void);

int getRand(void) {
  return (rand() % SPAN) + MINVAL;
}

int main(void) {
  srand(time(NULL));
  
  int T[N][N];
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      T[i][j] = getRand();
    }
  }

  int sumDiag = 0;
  int sumVer[N];
  int sumHor[N];
  int sum = 0;
  
  for (int i = 0; i < N; i++) {
    sumVer[i] = 0;
    sumHor[i] = 0;
    
    sumDiag += T[i][i];

    for (int j = 0; j < N; j++) {
      sumVer[i] += T[j][i];
      sumHor[i] += T[i][j];
    }

    sum += sumVer[i];
  }

  for (int i = 0; i < N; i++) {
    printArr(T[i], N);
  }
  
  printf("Suma: %d\n", sum);
  printf("Suma na przekatnej: %d\n", sumDiag);

  for (int i = 0; i < N; i++) {
    printf("Suma w kol. %d: %d\n", i, sumVer[i]);
    printf("Suma w wier. %d: %d\n", i, sumHor[i]);
  }
}


void printArr(int t[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", t[i]);
  }
  printf("\n");
}
