#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
// Struktura macierzy
typedef struct {
  // Ilość wierszy
  int rn;
  // Ilość kolumn
  int cn;
  // tablica wartości
  double *e;
} matrix_t;

matrix_t *make_matrix(int rn, int cn);

matrix_t *read_matrix(FILE *in);

void write_matrix(matrix_t *, FILE *out);

void put_entry_matrix(matrix_t *, int i, int j, double val);

void add_to_entry_matrix(matrix_t *, int i, int j, double val);

double get_entry_matrix(matrix_t *, int i, int j);

matrix_t *copy_matrix(matrix_t *s);

matrix_t *transpose_matrix(matrix_t *s);

void xchg_rows(matrix_t *m, int i, int j);

void xchg_cols(matrix_t *m, int i, int j);

matrix_t *mull_matrix(matrix_t *, matrix_t *);

matrix_t *ge_matrix(matrix_t *);

int bs_matrix(matrix_t *);

matrix_t *pivot_ge_matrix(matrix_t *, int *row_per);

void pivot_ge_in_situ_matrix(matrix_t *);

matrix_t *symm_pivot_ge_matrix(matrix_t *, int *per);

int *pivot_get_inv_per(matrix_t *, int *row_per);
double dot1(matrix_t *a, int ai, matrix_t *b);
double dot2(matrix_t *a, int ai, matrix_t *b);
matrix_t *multiply_matrix(matrix_t *a, int ai, matrix_t *b);
void freeMatrix(matrix_t *m);

#endif
