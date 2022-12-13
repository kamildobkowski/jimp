#include "gauss.h"

#include "backsubst.h"
#include "mat_io.h"
/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int h = mat->r;
    for (int l = 0; l < h - 1; l++) {
        for (int w = l + 1; w < h; w++) {
            if (mat->data[l][l] == 0) return 1;
            double m = mat->data[w][l] / mat->data[l][l];
            for (int i = l; i < h; i++) mat->data[w][i] -= m * mat->data[l][i];
            b->data[w][0] -= m * b->data[l][0];
        }
    }
    return 0;
}