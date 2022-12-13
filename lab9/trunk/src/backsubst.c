#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
void backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    /**
     * Tutaj należy umieścić właściwą implemntację.
     */

    int n = mat->r-1;
	double sum = 0.0;
	x->data[n][0] = b->data[n][0] / mat->data[n][n];
	for(int i = n - 1; i >= 0; i--){
		sum = 0;
		for(int j = i + 1; j <= n; j++)
			sum += mat->data[i][j]*x->data[j][0];
		x->data[i][0] = (b->data[i][0] - sum ) / mat->data[i][i];
	}
}
