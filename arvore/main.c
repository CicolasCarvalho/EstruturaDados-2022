#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int identico(arvore* T1, arvore* T2);

int main(void) {
    arvore* arv = arvore_init();
    arvore* arv2 = arvore_init();
    arv->valor = 10;
    arv2->valor = 10;

    arvore_inserir(arv, 11);
    arvore_inserir(arv, 69);
    arvore_inserir(arv, 5);
    arvore_inserir(arv, 32);

    arvore_inserir(arv2, 11);
    arvore_inserir(arv2, 69);
    arvore_inserir(arv2, 5);
    arvore_inserir(arv2, 32);

    arvore_print(arv);
    printf("\n--------------\n");
    arvore_print(arv2);
    printf("\n--------------\n");
    printf("%i", identico(arv, arv2));
}

int identico(arvore* T1, arvore* T2) {
    if (T1 == T2) return 1;
    if (T1 == NULL || T2 == NULL) return 0;
    if (T1->valor != T2->valor) return 0;

    return identico(T1->esquerda, T2->esquerda) && identico(T1->direita, T2->direita);
}
