#include <stdio.h>

#define TAMANHO 8

int bubble_sort(int arr[TAMANHO]);

int main(void) {
    int arr[TAMANHO] = {
        1, 2, 3, 4, 5, 6, 7, 8
        // 2, 7, 1, 3, 4, 6, 5, 0
        // 9, 8, 7, 6, 5, 4, 3, 2,
    };

    printf("em %i iteracoes\n", bubble_sort(arr));

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

int bubble_sort(int arr[TAMANHO]) {
    int iteracoes = 0;

    int i = TAMANHO-1;
    int trocou = 1;

    while (i > 0 && trocou) {
        trocou = 0;

        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                trocou = 1;
                iteracoes++;
            }
        }

        i--;
    }

    return iteracoes;
}