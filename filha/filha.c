#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pilha.h"

typedef struct {
    pilha *esquerda;
    pilha *direita;
} filha;

filha* filha_init(void);
int filha_insere(filha *f, char c);
int filha_remove(filha *f, char *c);
void transfere_pilha(pilha *p, pilha *q);
int filha_vazia(filha *f);

int main(void) {
    filha* f = filha_init();
    char c;

    // filha_insere(f, 'a');
    // filha_insere(f, 'b');
    // filha_insere(f, 'c');
    // filha_remove(f, &c);
    // printf("%c ", c);
    // filha_insere(f, 'd');
    // filha_remove(f, &c);
    // printf("%c ", c);
    // filha_remove(f, &c);
    // printf("%c ", c);
    // filha_remove(f, &c);
    // printf("%c ", c);

    // printf("f->esquerda:\n");
    // pilha_print(*(f->esquerda));
    // printf("f->direita:\n");
    // pilha_print(*(f->direita));

    return 0;
}

filha* filha_init(void) {
    filha* f = malloc(sizeof(filha));
    f->esquerda = pilha_init();
    f->direita = pilha_init();
    return f;
}

int filha_insere(filha* f, char c) {
    if (!pilha_vazia(f->direita))
        transfere_pilha(f->direita, f->esquerda);

    return pilha_empilha(f->esquerda, c);
}

int filha_remove(filha *f, char *c) {
    if (filha_vazia(f)) {
        fprintf(stderr, "ERRO: TENTOU REMOVER DE UMA FILA VAZIA");
        assert(0);
    }

    if (!pilha_vazia(f->esquerda))
        transfere_pilha(f->esquerda, f->direita);

    return pilha_desempilha(f->direita, c);
}

void transfere_pilha(pilha *p, pilha *q) {
    char v;

    while(!pilha_vazia(p)) {
        pilha_desempilha(p, &v);
        pilha_empilha(q, v);
    }
}

int filha_vazia(filha *f) {
    return pilha_vazia(f->esquerda) && pilha_vazia(f->direita);
}