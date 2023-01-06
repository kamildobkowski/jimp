#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int Gauss_Seidl() {}

double rabs(double a, double b){
    double result = a - b;
    return result >= 0 ? result : -result;
}

int close(double a, double b) {
    return rabs(a, b) > 1e-8;
}

int allclose(double *a, double * b, int size){
    for(int i = 0; i < size; i++){

    }
}

int main() {
    FILE * mA = fopen("dane.txt", "r");
    FILE * mB = fopen("b.txt", "r");
    matrix_t *a = read_matrix(mA);
    matrix_t *a = read_matrix(mB);
    fclose(mA);
    fclose(mB);

    matrix_t *x = make_matrix(1, b->cn);
    double result = 0;
    for (int i = 0; i < 1000; i++){
        printf("Current solution: %f", 0);
        matrix_t * new_x = make_matrix(1, b->cn);
        for(int i = 0; i < a->cn; i++){
            double s1 = dot1(a, i, new_x);
            double s2 = dot2(a, i, new_x);
            new_x[i] = (b->e[i] - s1 -s2) / A[i,i];
        }
        if(allclose(result, ))
    }
}
