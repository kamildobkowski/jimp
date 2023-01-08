#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tworzenie nowej macierzy rn-liczba wierszy, cn-liczba kolumn
matrix_t *make_matrix(int rn, int cn) {
  matrix_t *new_mat = malloc(sizeof *new_mat);  // alokacja miejsca
  // sprawdzanie czy dobrze zaalokowalo
  if (new_mat == NULL) return NULL;
  // alokowanie miejsca na cala macierz i sprawdzanie czy sie dobrze
  // zaalokowalo
  if ((new_mat->e = malloc((size_t)rn * (size_t)cn * sizeof *new_mat->e)) ==
      NULL) {
    free(new_mat);
    return NULL;
  }
  // zapisywanie ilosci wierszy i kolumn
  new_mat->rn = rn;
  new_mat->cn = cn;
  // ustawianie calej macierzy na 0
  memset(new_mat->e, 0, (size_t)(rn * (size_t)cn * sizeof *new_mat->e));
  return new_mat;  // zwracanie macierzy
}
// zwalnianie pamieci
void free_matrix(matrix_t *m) {
  free(m->e);
  free(m);
}
// dodawanie wartosci do macierzy i-wiersz, j-kolumna, val-wartosc
void put_entry_matrix(matrix_t *m, int i, int j, double val) {
  if (i >= 0 && i < m->rn && j >= 0 && j <= m->cn) m->e[i * m->cn + j] = val;
}
// dodawanie liczby do elementu macierzy
void add_to_entry_matrix(matrix_t *m, int i, int j, double val) {
  if (i >= 0 && i < m->rn && j >= 0 && j <= m->cn) m->e[i * m->cn + j] += val;
}
// zwraca wartosc m(i,j) macierzy
double get_entry_matrix(matrix_t *m, int i, int j) {
  if (i >= 0 && i < m->rn && j >= 0 && j <= m->cn)
    return m->e[i * m->cn + j];
  else
    return -999;
}
// czytanie macierzy z pliku
matrix_t *read_matrix(FILE *in) {
  int rn, cn;  // liczba wierszy i kolumn
  int i, j;
  matrix_t *new_mat;
  // obsluga bledow
  if (fscanf(in, "%d %d", &rn, &cn) != 2) return NULL;
  // inicjalizacja macierzy
  if ((new_mat = make_matrix(rn, cn)) == NULL) return NULL;
  // dopisywanie elementu (i,j) do macierzy
  for (i = 0; i < rn; i++)
    for (j = 0; j < cn; j++)
      // obsluga bledow
      if (fscanf(in, "%lf", &new_mat->e[i * cn + j]) != 1) {
        free_matrix(new_mat);
        return NULL;
      }
  return new_mat;
}
// wypisywanie macierzy do pliku (format jest taki sam jak w przypadku
// wczytywania)
void write_matrix(matrix_t *m, FILE *out) {
  int i, j;
  if (m == NULL) {
    fprintf(out, "Matrix is NULL\n");
    return;
  }
  fprintf(out, "%d %d\n", m->rn, m->cn);  // wypisanie rozmiaru macierzy
  for (i = 0; i < m->rn; i++) {
    for (j = 0; j < m->cn - 1; j++) fprintf(out, "%8.5f ", m->e[i * m->cn + j]);
    fprintf(out, "%8.5f\n", m->e[i * m->cn + j]);
  }
}
// tworzenie kopii macierzy
matrix_t *copy_matrix(matrix_t *s) {
  matrix_t *d = NULL;
  if (s != NULL) d = make_matrix(s->rn, s->cn);
  if (d != NULL) {
    memcpy(d->e, s->e, s->rn * s->cn * sizeof *s->e);

    /* int i;
       for( i= 0; i < s->rn*s->cn; i++ )
       *(d->e+i)= *(s->e+i);
     */
    /* d->rn= s->rn; d->cn= s->cn; done in make_matrix */
  }
  return d;
}
// transpozycja macierzy
matrix_t *transpose_matrix(matrix_t *s) {
  matrix_t *d = NULL;
  if (s != NULL) d = make_matrix(s->rn, s->cn);
  if (d != NULL) {
    int i, j;
    for (i = 0; i < s->rn; i++)
      for (j = 0; j < s->cn; j++)
        *(d->e + j * d->cn + i) = *(s->e + i * s->cn + j);
    /* d->rn= s->cn; d->cn= s->rn; done in make_matrix */
  }
  return d;
}

// Adrian: Swapuje wiersz 'i' i 'j' w macierzy m (na postawie )
// pivot_ge_matrix
// X CHANGE ROWS
void xchg_rows(matrix_t *m, int i, int j) {
  if (m != NULL && i >= 0 && i < m->rn && j >= 0 && j < m->rn) {
    int k;
    double tmp;
    for (k = 0; k < m->cn; k++) {
      tmp = *(m->e + i * m->cn + k);
      *(m->e + i * m->cn + k) = *(m->e + j * m->cn + k);
      *(m->e + j * m->cn + k) = tmp;
    }
  }
}

// Analogicznie pewnie
void xchg_cols(matrix_t *m, int i, int j) {
  if (m != NULL && i >= 0 && i < m->cn && j >= 0 && j < m->cn) {
    int k;
    double tmp;
    for (k = 0; k < m->rn; k++) {
      tmp = *(m->e + k * m->cn + i);
      *(m->e + k * m->cn + i) = *(m->e + k * m->cn + j);
      *(m->e + k * m->cn + j) = tmp;
    }
  }
}
matrix_t *multiply_matrix(matrix_t *a, int ai, matrix_t *b) {
  double s;
  int i, j;
  if (a->cn != b->cn || a->rn != b->cn) return NULL;
  matrix_t *c = make_matrix(a->cn, a->rn);
  for (i = 0; i < c->cn; i++) {
    for (j = 0; j < c->rn; j++) {
      s = *(a->e + i * a->cn + j) * *(b->e + i * a->cn + j);
      *(c->e + i * c->cn + j) = s;
    }
  }
  return c;
}
/*int suma += a->e[i][do i - 1] * b->e[1][do i - 1];
int suma = a->e[i][od i + 1 do końca] * b->e[1][od i + 1 do końca];*/
double dot1(matrix_t *a, int ai, matrix_t *b) {
  double suma = 0;
  for (int i = 0; i < ai; i++) {
    suma += a->e[a->rn * ai + i] * b->e[i];
  }
  return suma;
}
double dot2(matrix_t *a, int ai, matrix_t *b) {
  double suma = 0;
  for (int i = ai + 1; i < a->rn; i++) {
    suma += a->e[a->rn * ai + i] * b->e[i];
  }
  return suma;
}
matrix_t *mull_matrix(matrix_t *a, matrix_t *b) {
  if (a == NULL || b == NULL || a->cn != b->rn)
    return NULL;
  else {
    matrix_t *c = make_matrix(a->rn, b->cn);
    int i, j, k;
    if (c == NULL) return NULL;
    for (i = 0; i < c->rn; i++) {
      for (j = 0; j < c->cn; j++) {
        double s = 0;
        for (k = 0; k < a->cn; k++)
          s += *(a->e + i * a->cn + k) * *(b->e + k * b->cn + j);
        *(c->e + i * c->cn + j) = s;
      }
    }
    return c;
  }
}

matrix_t *ge_matrix(matrix_t *a) {
  matrix_t *c = copy_matrix(a);
  if (c != NULL) {
    int i, j, k;
    int cn = c->cn;
    int rn = c->rn;
    double *e = c->e;
    for (k = 0; k < rn - 1; k++) {   /* eliminujemy (zerujemy) kolumnę nr k */
      for (i = k + 1; i < rn; i++) { /* pętla po kolejnych
                                        wierszach poniżej diagonalii k,k */
        double d = *(e + i * cn + k) / *(e + k * cn + k);
        for (j = k; j < cn; j++) *(e + i * cn + j) -= d * *(e + k * cn + j);
      }
    }
  }
  return c;
}

int bs_matrix(matrix_t *a) {
  if (a != NULL) {
    int r, c, k;
    int cn = a->cn;
    int rn = a->rn;
    double *e = a->e;

    for (k = rn; k < cn; k++) {         /* pętla po prawych stronach */
      for (r = rn - 1; r >= 0; r--) {   /* petla po niewiadomych */
        double rhs = *(e + r * cn + k); /* wartość prawej strony */
        for (c = rn - 1; c > r;
             c--) /* odejmujemy wartości już wyznaczonych niewiadomych *
                     pomnożone przed odpowiednie współczynniki */
          rhs -= *(e + r * cn + c) * *(e + c * cn + k);
        *(e + r * cn + k) =
            rhs / *(e + r * cn +
                    r); /* nowa wartość to prawa strona / el. diagonalny */
      }
    }
    return 0;
  } else
    return 1;
}

void freeMatrix(matrix_t *m) {
  free(m->e);
  free(m);
}