#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int Gauss_Seidl() {}

double rabs(double a, double b) {
  double result = a - b;
  return result >= 0 ? result : -result;
}

int close(double a, double b) {
  return rabs(a, b) < 1e-8;
  // AAA
}

int allclose(double *a, double *b, int size) {
  for (int i = 0; i < size; i++) {
    if (!close(a[i], b[i])) return 0;
  }
  return 1;
}

void printSollution(double *sol, int size) {
  printf("[");
  for (int i = 0; i < size; i++) {
    printf(" %.8f", sol[i]);
  }
  printf(" ]\n");
}

int main() {
  FILE *mA = fopen("data/a2", "r");
  FILE *mB = fopen("data/b2", "r");
  matrix_t *a = read_matrix(mA);
  matrix_t *b = read_matrix(mB);
  fclose(mA);
  fclose(mB);
  if (a == NULL || b == NULL) {
    printf("Błąd podczas czytania z pliku!!");
    if (a != NULL) {
      free(a);
    } else if (b != NULL) {
      free(b);
    }
  }
  matrix_t *x = make_matrix(1, b->cn);

  for (int i = 0; i < 1000; i++) {
    printf("Current solution: ");
    printSollution(x->e, x->cn);
    matrix_t *new_x = make_matrix(1, b->cn);
    for (int i = 0; i < a->cn; i++) {
      double s1 = dot1(a, i, new_x);
      double s2 = dot2(a, i, x);
      new_x->e[i] = (b->e[i] - s1 - s2) / a->e[i * a->cn + i];
    }
    if (allclose(x->e, new_x->e, x->cn) == 1) {
      freeMatrix(new_x);
      break;
    }
    freeMatrix(x);
    x = copy_matrix(new_x);
    freeMatrix(new_x);
  }

  printf("Solution: \n");
  printSollution(x->e, x->cn);
  freeMatrix(a);
  freeMatrix(b);
  freeMatrix(x);
}
