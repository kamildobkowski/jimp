#include "misc.h"
#include "matrix.h"

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