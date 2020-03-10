#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N1 = 5;
const int N2 = 7;

//utils
void printArr(int[], int);
void swap(int*, int*);
int rand10(void);

//zadania
void reverse(int[], int);
void sort(int[], int);
int one_two(int[], int, int[], int, int[]);

int rand10(void) {
  return (rand() % 10) + 1;
}

int main(void) {
  srand(time(NULL));
    
  int t1[N1];
  int t2[N2];

  int T[N1 + N2];

  for (int i = 0; i < N1; i++) {
    t1[i] = rand10();
  }

  for (int i = 0; i < N2; i++) {
    t2[i] = rand10();
  }

  printArr(t1, N1);
  reverse(t1, N1);
  printArr(t1, N1);
  
  sort(t1, N1);
  printArr(t1, N1);
  sort(t2, N2);
  printArr(t2, N2);

  int final_size = one_two(t1, N1, t2, N2, T);
  printf("Rozmiar: %d\n", final_size);
  printArr(T, final_size);
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void reverse(int t[], int size) {
  int half = size / 2;
  for (int i = 0; i < half; i++) {
    swap(&t[i], &t[size - i - 1]);
  }
}

void printArr(int t[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", t[i]);
  }
  printf("\n");
}

void sort(int t[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (t[j] > t[j + 1]) {
	swap(&t[j], &t[j + 1]);
      }
    }
  }
}

int one_two(int a[], int sizeA, int b[], int sizeB, int result[]) {
  int idxA = 0;
  int idxB = 0;
  int idxResult = 0;
  int lastVal;
  char first = 1;
  while (idxA != sizeA || idxB != sizeB) {
    if (idxB == sizeB || (idxA != sizeA && a[idxA] < b[idxB])) {
      if (a[idxA] > lastVal || first) {
	result[idxResult++] = a[idxA];
	lastVal = a[idxA];
      }
      idxA++;
    }
    else {
      if (b[idxB] > lastVal || first) {
	result[idxResult++] = b[idxB];
	lastVal = b[idxB];
      }
      idxB++;
    }
    first = 0;
  }

  return idxResult;
}
