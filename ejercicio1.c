#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para encontrar la secuencia más larga de 1s consecutivos en la matriz
void findLargestLine(int** matrix, int size, int* result) {
    int masLarga = 0;  // Para almacenar la secuencia más larga de 1s
    int actual = 0;    // Contador de 1s consecutivos

    for (int i = 0; i < size; i++) {           // Recorrer filas
        for (int j = 0; j < size; j++) {       // Recorrer columnas
            if (matrix[i][j] == 1) {
                actual++;                      // Incrementar contador si encontramos un 1
            } else {
                if (actual > masLarga) masLarga = actual;  // Actualizar la secuencia más larga
                actual = 0;                    // Reiniciar el contador si encontramos un 0
            }
        }
        // No reiniciamos `actual` al final de la fila para que pueda continuar en la siguiente
    }

    // Asegurarse de que la última secuencia se cuente
    if (actual > masLarga) masLarga = actual;
    *result = masLarga;
}

// Función para reservar la matriz en memoria dinámica
void allocateMatrix(int*** matrix, int size) {
    *matrix = (int**) malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        (*matrix)[i] = (int*) malloc(size * sizeof(int));
    }
}

// Función para llenar la matriz de manera aleatoria con 0s y 1s
void fillMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 2;  // Llenar con 0 o 1 aleatoriamente
        }
    }
}

// Función para imprimir la matriz
void printMatrix(int** matrix, int size) {
    printf("La matriz utilizada corresponde a:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Función para liberar la memoria asignada a la matriz
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Función para calcular la transpuesta de una matriz
void transposeMatrix(int** matrix, int size, int*** transpuesta) {
    allocateMatrix(transpuesta, size);  // Reservar memoria para la matriz transpuesta
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            (*transpuesta)[j][i] = matrix[i][j];  // Asignar el valor transpuesto
        }
    }
}

int main() {
    int size, largestLine, largestLinetranspuesta;
    int** matrix = NULL;
    int** transpuestaMatrix = NULL;

    // Solicitar el tamaño de la matriz al usuario
    printf("Ingrese el tamaño de la matriz (filas y columnas): ");
    scanf("%d", &size);

    // Inicializar la semilla para números aleatorios
    srand(time(0));

    // Reservar memoria para la matriz cuadrada
    allocateMatrix(&matrix, size);

    // Llenar la matriz de manera aleatoria y luego imprimirla
    fillMatrix(matrix, size);
    printMatrix(matrix, size);

    // Encontrar la secuencia más larga de 1s consecutivos en la matriz original
    findLargestLine(matrix, size, &largestLine);
    printf("El tamaño de la secuencia de 1s más grande en la matriz original es: %d\n", largestLine);

    // Calcular la matriz transpuesta
    transposeMatrix(matrix, size, &transpuestaMatrix);
    printf("La matriz transpuesta es:\n");
    printMatrix(transpuestaMatrix, size);

    // Encontrar la secuencia más larga de 1s consecutivos en la matriz transpuesta
    findLargestLine(transpuestaMatrix, size, &largestLinetranspuesta);
    printf("El tamaño de la secuencia de 1s más grande en la matriz transpuesta es: %d\n", largestLinetranspuesta);

    // Liberar la memoria de las matrices
    freeMatrix(matrix, size);
    freeMatrix(transpuestaMatrix, size);

    return 0;
}

