#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "misc.h"

int main(int argc, char *argv) {
  if(argc<2) {
    fprintf(stdout, "Bledne wywolanie programu\nPo wywolaniu podaj 2 nazwy plikow", stderr);
    return 1;
  }
  FILE *mA = fopen(argv[1], "r");
  FILE *mB = fopen(argv[2], "r");
  matrix_t *a = read_matrix(mA);
  matrix_t *b = read_matrix(mB);
  fclose(mA);
  fclose(mB);
  if (a == NULL || b == NULL) {
    fprintf(stdout, "Błąd podczas czytania z pliku!", stderr);
    if (a != NULL) {
      free(a);
    } else if (b != NULL) {
      free(b);
    }
  }
  if(a->cn != a->rn) {
    fprintf(stdout, "Macierz w 1 pliku musi być kwadratowa!", stderr);
    if (a != NULL) {
      free(a);
    } 
    if (b != NULL) {
      free(b);
    }
    return 2;
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
