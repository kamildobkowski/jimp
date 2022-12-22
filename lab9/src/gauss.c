#include "gauss.h"

#include <math.h>

#include "backsubst.h"
#include "mat_io.h"

void eliminate(Matrix *mat, Matrix *b) {
    int size = mat->r;

    for (int k = 0; k < size - 1; k++) {
        int kmax = k;
        for (int w = k + 1; w < size; w++) {
            if (fabs(mat->data[w][k]) > fabs(mat->data[kmax][k])) kmax = w;
        }
        if (kmax != k) {  // swap
            double *tmp = mat->data[k];
            mat->data[k] = mat->data[kmax];
            mat->data[kmax] = tmp;
            double *btmp = b->data[k];
            b->data[k] = b->data[kmax];
            b->data[kmax] = btmp;
        }
        for (int w = k + 1; w < size; w++) {
            if (mat->data[k][k] == 0) {
                return size + k;
            }
            double m = mat->data[w][k] / mat->data[k][k];
            for (int i = k; i < size; i++) {
                mat->data[w][i] -= m * mat->data[k][i];
            }
            b->data[w][0] -= m * b->data[k][0];
        }
    }
}