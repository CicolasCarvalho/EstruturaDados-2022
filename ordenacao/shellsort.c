#include <stdio.h>

#define TAMANHO 8

int shell_sort(int arr[TAMANHO]);
int bubble_sort(int arr[], int tam);

int main(void) {
    int arr[TAMANHO] = {
        1, 2, 3, 4, 5, 6, 8, 7
        // 2, 7, 1, 3, 4, 6, 5, 0
        // 9, 8, 7, 6, 5, 4, 3, 2,
    };

    printf("em %i iteracoes\n", shell_sort(arr));

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

int shell_sort(int arr[TAMANHO]) {
    int iteracoes = 0;

    for (int espaco = TAMANHO/2; espaco > 0; espaco /= 2) {
        for (int i = 0; i < espaco; i++) {
            int m = TAMANHO - (espaco - i);
            int trocou = 1;

            while (m > 0 && trocou) {
                trocou = 0;

                for (int j = i; j < m; j += espaco) {
                    if (arr[j] > arr[j+espaco]) {
                        swap(&arr[j], &arr[j+espaco]);
                        trocou = 1;
                        iteracoes++;
                    }
                }

                m -= espaco;
            }
        }
    }

    return iteracoes;
}