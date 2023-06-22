#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

pilha* pilha_init(void) {
    pilha* p = malloc(sizeof(pilha));
    p->vetor = malloc(sizeof(pilha_tipo)*TAM_MAX);
    p->tamanho = TAM_MAX;
    p->quantidade = 0;

    return p;
}

int pilha_empilha(pilha *p, pilha_tipo valor) {
    if (p->quantidade >= p->tamanho) return 0;

    p->vetor[p->quantidade] = valor;
    p->quantidade++;
    return 1;
}

int pilha_desempilha(pilha *p, pilha_tipo *valor) {
    if (p->quantidade == 0) return 0;

    *valor = p->vetor[p->quantidade-1];
    p->quantidade--;

    return 1;
}

void pilha_print(pilha p) {
    for(int i = 0; i < p.quantidade; i++) {
        printf("%c ", p.vetor[i]);
    }
    printf("\n");
}

void pilha_apaga(pilha *p) {
    free(p->vetor);
    free(p);
}

pilha* pilha_inverte(pilha *p) {
    pilha_tipo val;
    pilha* temp = pilha_init();

    while (pilha_desempilha(p, &val)) {
        pilha_empilha(temp, val);
    }

    return temp;
}

int pilha_empilha_pilha(pilha *base, pilha *empilhando) {
    empilhando = pilha_inverte(empilhando);

    pilha_tipo val;

    while (pilha_desempilha(empilhando, &val)) {
        pilha_empilha(base, val);
    }

    return 1;
}

int pilha_vazia(pilha *p) {
    return p->quantidade==0;
}