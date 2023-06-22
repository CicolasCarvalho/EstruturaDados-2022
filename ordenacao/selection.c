#include <stdio.h>

#define TAMANHO 8

int selection_sort(int arr[TAMANHO]);

int main(void) {
    int arr[TAMANHO] = {
        // 2, 7, 1, 3, 4, 6, 5, 9, 8, 0
        9, 8, 7, 6, 5, 4, 3, 2
    };

    printf("em %i iteracoes\n", selection_sort(arr));

    for (int i = 0; i < TAMANHO; i++) {
        printf("%i, ", arr[i]);
    }

    return 0;
}

void swap(int* a, int* b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int selection_sort(int arr[TAMANHO]) {
    int iteracoes = 0;

    for (int i = 0; i < TAMANHO-1; i++) {
        for (int j = i; j < TAMANHO; j++) {
            if (arr[j] < arr[i]) {
                swap(&arr[j], &arr[i]);
                iteracoes++;
            }
        }
    }

    return iteracoes;
}