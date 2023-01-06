#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int Gauss_Seidl() {}

double rabs(double a, double b) {
  double result = a - b;
  return result >= 0 ? result : -result;
}

int close(double a, double b) {
  return rabs(a, b) > 1e-8;
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
    printf(" %f", sol[i]);
  }
  printf(" ]");
}

int main() {
  FILE *mA = fopen("data/a", "r");
  FILE *mB = fopen("data/b", "r");
  matrix_t *a = read_matrix(mA);
  matrix_t *b = read_matrix(mB);
  fclose(mA);
  fclose(mB);

  matrix_t *x = make_matrix(1, b->cn);
  printf("Current solution: \n");
  exit(1);

  for (int i = 0; i < 1000; i++) {
    printf("Current solution: \n");
    printSollution(x->e, x->cn);
    matrix_t *new_x = make_matrix(1, b->cn);
    for (int i = 0; i < a->cn; i++) {
      double s1 = dot1(a, i, new_x);
      double s2 = dot2(a, i, new_x);
      new_x->e[i] = (b->e[i] - s1 - s2) / a->e[i * a->cn + i];
    }
    if (allclose(x->e, new_x->e, x->cn)) break;
    x = new_x;
  }

  printf("Soluution: \n");
  printSollution(x->e, x->cn);
}
