// Ní­colas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 30 03 2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifndef bool
    typedef int bool;
    #define true 1;
    #define false 0;
#endif

typedef struct FD fila_dupla;

struct FD {
    fila_dupla *esquerda;
    fila_dupla *direita;
    char c;
};

fila_dupla* fila_init(void);

bool fila_vazia(fila_dupla* fd);
bool fila_insere_direita(fila_dupla* fd, char c);
bool fila_remove_direita(fila_dupla* fd, char* c);
bool fila_insere_esquerda(fila_dupla* fd, char c);
bool fila_remove_esquerda(fila_dupla* fd, char* c);
bool fila_esquerda(fila_dupla* fd, char* c);
bool fila_direita(fila_dupla* fd, char* c);
int normalizar(char* c);
bool palindromo(fila_dupla* fd);
void transformar_str(char* str, fila_dupla* fd);

int main(void) {
    char str[50];
    fila_dupla* fd = fila_init();

    fgets(str, 50, stdin);
    str[strlen(str)-1] = '\0';

    transformar_str(str, fd);
    printf("\n'%s' e palindromo: %i", str, palindromo(fd));

    return 0;
}

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
        printf("ERRO: fila deveria ter uma cabeÃ§a (tente inicializar a fila antes de inserir)\n");
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
bool normalizar(char* c) {
    if (*c < 90) *c += 32;

    return (*c-97 >= 0 && *c-122 <= 0); // retorna se Ã© uma letra ou nÃ£o
}

// se fila pop retornar que a fila estava vazia
// o que significa que ela era par e acabou
// se fila shift retornar que a fila estava vazia apos fila pop
// significa que a frase era impar o que significa que a frase e palindromo
bool palindromo(fila_dupla* fd) {
    char dir, esq;
    if (!(fila_remove_direita(fd, &dir) && fila_remove_esquerda(fd, &esq))) return true;
    return dir == esq && palindromo(fd);
}

void transformar_str(char* str, fila_dupla* fd) {
    char c;
    for (int i = 0; i < strlen(str); i++) {
        c = str[i];
        if (normalizar(&c))
            fila_insere_direita(fd, c);
    }
}
