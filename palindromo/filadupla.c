// Nícolas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 24 03 2023

//@start incl
//@once io
#include <stdio.h>
//@once lib
#include <stdlib.h>
//@once assert
#include <assert.h>
//@ignore
#include "filadupla.h"
//@end

//@start func
fila_dupla* fila_init(void) {
    fila_dupla* fd = malloc(sizeof(fila_dupla));
    fd->c = ' ';
    fd->esquerda = NULL;
    fd->direita = NULL;
    return fd;
}

bool fila_vazia(fila_dupla* fd) {
    return (fd == NULL || (fd->direita == NULL && fd->esquerda == NULL));
}

bool fila_insere_direita(fila_dupla* fd, char c) {
    if (fd == NULL) {
        printf("ERRO: fila deveria ter uma cabeça (tente inicializar a fila antes de inserir)\n");
        assert(0);
        return false;
    }

    if (fd->direita != NULL) {
        return fila_insere_direita(fd->direita, c);
    }

    fd->direita = fila_init();
    fd->direita->c = c;
    fd->direita->esquerda = fd;
    return true;
}

bool fila_remove_direita(fila_dupla* fd, char* c) {
    if (fila_vazia(fd)) return false;

    if (fd->direita != NULL) {
        return fila_remove_direita(fd->direita, c);
    }

    *c = fd->c;
    fd->esquerda->direita = NULL;
    free(fd);
    return true;
}

bool fila_insere_esquerda(fila_dupla* fd, char c) {
    if (fd == NULL) {
        printf("ERRO: fila deveria ter uma cabeca  (tente inicializar a fila antes de inserir)\n");
        assert(0);
        return false;
    }
    fila_dupla* nova = fila_init();
    fila_dupla* velha = fd->direita;

    fd->direita = nova;

    nova->direita = velha;
    nova->esquerda = fd;
    nova->c = c;

    if(velha != NULL)
        velha->esquerda = nova;

    return true;
}

bool fila_remove_esquerda(fila_dupla* fd, char* c) {
    if (fila_vazia(fd)) return false;

    fila_dupla* removido = fd->direita;
    fd->direita = fd->direita->direita;

    *c = removido->c;
    free(removido);

    if (fd->direita != NULL)
        fd->direita->esquerda = fd;

    return true;
}

bool fila_esquerda(fila_dupla* fd, char* c) {
    if (fila_vazia(fd)) return false;

    *c = fd->direita->c;
    return true;
}

bool fila_direita(fila_dupla* fd, char* c) {
    if (fila_vazia(fd)) return false;

    if (fd->direita == NULL) {
        *c = fd->c;
        return true;
    }

    return fila_direita(fd->direita, c);
}
//@end