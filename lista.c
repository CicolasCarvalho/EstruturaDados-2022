// Ní­colas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 02 02 2023

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int valor;
    struct node* prox;
} node;

typedef struct node* list;

void printLista(list lista);
int getLenLista(list lista);
int getInLista(list lista, int pos);
node* getNodeLista(list l, int pos);

void insertLista(list* lista, int pos, list value);
void insertValor(list* lista, int pos, int value);
void pushLista(list* lista, list value);
void pushValor(list* lista, int value);

node* popLista(list* lista);
node* shiftLista(list* lista);
node* removeLista(list* lista, int pos);

void clearLista(list* l);
void clonarLista(list* l, list origem);

int main(void) {
    list p = NULL,
         q = NULL;
         // popl = NULL,
         // shiftl = NULL;

    pushValor(&p, 1);
    pushValor(&p, 2);
    pushValor(&p, 3);
    insertValor(&p, 3, 5);

    pushValor(&q, 10);
    pushValor(&q, 11);
    pushValor(&q, 12);

    printLista(p);
    printf("---\n");
    printLista(q);
    printf("---\n");
    insertLista(&p, 1, q);
    printLista(p);
    printf("---\n");
    printLista(q);
    printf("---\n");
    removeLista(&q, 0);
    printLista(q);

    return 0;
}

void printLista(list lista) {
    if (lista == NULL) return;

    printf("%i\n", lista->valor);
    printLista(lista->prox);
}

int getLenLista(list lista) {
    if (lista == NULL)
        return 0;
    return getLenLista(lista->prox)+1;
}

void pushLista(list* lista, list value) {
    if (*lista == NULL) {                   // se o ponteiro que aponta para o primeiro elemento for nulo
        *lista = value;
        return;
    }

    if ((*lista)->prox == NULL) {           // se o proximo elemento for nulo o proximo recebe o valor
        (*lista)->prox = value;
        return;
    }

    pushLista(&((*lista)->prox), value);
}

void pushValor(list* lista, int value) {
    node* valNode = malloc(sizeof(node));
    valNode->valor = value;
    valNode->prox = NULL;
    pushLista(lista, valNode);
}

int getInLista(list lista, int pos) {
    assert(pos >= 0 && lista != NULL && pos <= getLenLista(lista));

    if (pos == 0)
        return lista->valor;

    getInLista(lista->prox, pos-1);

    return 1;
}

node* getNodeLista(list l, int pos) {
    assert(pos >= 0 && l != NULL && pos <= getLenLista(l));

    if (pos == 0)
        return l;

    return getNodeLista(l->prox, pos-1);
}

void insertLista(list* lista, int pos, list value) {
    assert(pos >= 0 && lista != NULL && pos <= getLenLista(*lista));

    list clonedList = NULL;
    clonarLista(&clonedList, value);
    node* last = getNodeLista(clonedList, getLenLista(value)-1);

    if (pos == 0) {
        last->prox = (*lista);
        *lista = clonedList;
        return;
    }

    if (pos == 1) {
        last->prox = (*lista)->prox;
        (*lista)->prox = clonedList;
        return;
    }

    insertLista(&(*lista)->prox, pos-1, value);
}

void insertValor(list* lista, int pos, int value){
    node* valNode = malloc(sizeof(node));
    valNode->valor = value;
    valNode->prox = NULL;
    insertLista(lista, pos, valNode);
}

node* popLista(list* lista) {
    if ((*lista) == NULL)
        return NULL;

    if ((*lista)->prox == NULL) {
        return NULL;
        assert(false);
    }

    if ((*lista)->prox->prox == NULL) {
        node* ptr = (*lista)->prox;
        (*lista)->prox = NULL;

        return ptr;
    }

    return popLista(&(*lista)->prox);
}

node* shiftLista(list* lista) {
    if ((*lista) == NULL)
        return NULL;

    node* ptr = (*lista);
    (*lista) = (*lista)->prox;

    ptr->prox = NULL;
    return ptr;
}

node* removeLista(list* lista, int pos) {
    assert(pos >= 0 && lista != NULL && pos <= getLenLista(*lista));

    node* ptr = NULL;
    if (pos == 0) {
        ptr = (*lista);
        *lista = (*lista)->prox;
        ptr->prox = NULL;
        return ptr;
    }

    if (pos == 1) {
        ptr = (*lista)->prox;
        (*lista)->prox = (*lista)->prox->prox;
        ptr->prox = NULL;
        return ptr;
    }

    return removeLista(&(*lista)->prox, pos-1);
}

void clearLista(list* l) {
    if ((*l) == NULL)
        return;

    clearLista(&(*l)->prox);
    free(*l);
    (*l) = NULL;
}

void clonarLista(list* l, list origem) {
    clearLista(l);
    (*l) = NULL;
    node* ptr = origem;
    while (ptr != NULL) {
        pushValor(l, ptr->valor);

        ptr = ptr->prox;
    }
}