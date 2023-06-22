#ifndef PILHA_H
#define PILHA_H

#define TAM_MAX 100

typedef struct struct_pilha pilha;
typedef char pilha_tipo;

struct struct_pilha {
    pilha_tipo *vetor;

    int tamanho,
        quantidade;
};

pilha* pilha_init(void);

int pilha_empilha(pilha *p, pilha_tipo valor);

int pilha_desempilha(pilha *p, pilha_tipo *valor);

void pilha_print(pilha p);

void pilha_apaga(pilha *p);

int pilha_empilha_pilha(pilha *base, pilha *empilhando);

pilha *pilha_inverte(pilha *p);

int pilha_vazia(pilha *p);

#endif