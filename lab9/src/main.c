#include <stdio.h>
#include <stdlib.h>

#include "backsubst.h"
#include "gauss.h"
#include "mat_io.h"

int main(int argc, char** argv) {
    Matrix* A = readFromFile(argv[1]);
    Matrix* b = readFromFile(argv[2]);
    Matrix* x;

    if (A == NULL) return -1;
    if (b == NULL) return -2;
    printToScreen(A);
    printToScreen(b);

    eliminate(A, b);
    x = createMatrix(b->r, 1);
    if (x != NULL) {
        backsubst(x, A, b);

        printToScreen(x);
        freeMatrix(x);
    } else {
        fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
    }

    freeMatrix(A);
    freeMatrix(b);

    return 0;
}
