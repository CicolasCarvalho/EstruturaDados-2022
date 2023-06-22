#ifndef ARVORE_H
#define ARVORE_H

typedef struct node arvore;

struct node {
    arvore* esquerda;
    arvore* direita;
    int valor;
};

arvore* arvore_init(void);

int arvore_vazia(arvore* arv);

void arvore_print(arvore* arv);

void arvore_inserir(arvore* arv, int n);

void arvore_remover(arvore* arv, int n);

arvore* arvore_busca(arvore* arv, int n);

#endif