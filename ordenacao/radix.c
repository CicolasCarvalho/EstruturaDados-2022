#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../palindromo/filadupla.h"

#define TAMANHO 8
#define LOG10(n) (int)(log10(n))

int maior_n_digitos(int arr[TAMANHO]);
void radix_sort(int arr[TAMANHO]);

int main(void) {
    int arr[TAMANHO] = {
        2, 7, 1, 3, 4, 6, 5, 0
    };

    int a = 0;
    scanf("%i", &a);

    printf("%i", LOG10(a));

    return 0;
}

int maior_n_digitos(int arr[TAMANHO]) {
    int maior = 0;

    for (int i = 0; i < TAMANHO; i++) {
        int a = LOG10(arr[i]);
        if (a > maior) {
            maior = a;
        }
    }
}

void radix_sort(int arr[TAMANHO]) {
    int maior = maior_n_digitos(arr);
    fila_dupla* tmp[10] = malloc(sizeof(fila_dupla*)*10);

    for (int i = 0; i < 10; i++) {
        fila_init();
    }
}