#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

arvore* arvore_init(void) {
    arvore* arv = malloc(sizeof(arvore));
    arv->esquerda = NULL;
    arv->direita = NULL;
    return arv;
}

int arvore_vazia(arvore* arv) {
    return arv == NULL;
}

void arvore_print(arvore* arv) {
    if (!arvore_vazia(arv)) {
        arvore_print(arv->esquerda);
        printf("%i, ", arv->valor);
        arvore_print(arv->direita);
    }
}

void arvore_inserir(arvore* arv, int n) {
    if(arvore_vazia(arv)) {
        arv = arvore_init();
        arv->valor = n;
        return;
    }

    if (n > arv->valor) {
        if (arv->direita == NULL) {
            arvore *novo = arvore_init();
            novo->valor = n;

            arv->direita = novo;
        } else {
            arvore_inserir(arv->direita, n);
        }
    }
    else if (n < arv->valor) {
        if (arv->esquerda == NULL) {
            arvore *novo = arvore_init();
            novo->valor = n;

            arv->esquerda = novo;
        } else {
            arvore_inserir(arv->esquerda, n);
        }
    }
    else {
        // implementar n == arv->valor
    }
}

// void arvore_remover(arvore* arv, int n) {
    // if (arvore_vazia(arv)) return;

    // if (!arvore_vazia(arv->direita) && !arvore_vazia(arv->esquerda)) {

    // } else {
    // }
// }

arvore* arvore_busca(arvore* arv, int n) {
    if (arvore_vazia(arv)) return NULL;

    if (n == arv->valor) return arv;
    if (n > arv->valor) return arvore_busca(arv->direita, n);
    if (n < arv->valor) return arvore_busca(arv->esquerda, n);
}