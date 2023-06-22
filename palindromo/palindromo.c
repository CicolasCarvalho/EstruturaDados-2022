// Nícolas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 24 03 2023

//@start incl
//@once io
#include <stdio.h>
//@once lib
#include <stdlib.h>
//@once str
#include <string.h>
//@ignore
#include "filadupla.h"
//@end

//@start defn
int normalizar(char* c);
bool palindromo(fila_dupla* fd);
void transformar_str(char* str, fila_dupla* fd);
void _transformar_str(char* str, char* out);
//@end

int main(void) {
    //@start main
    char str[50];
    char out[50];
    fila_dupla* fd = fila_init();

    fgets(str, 50, stdin);
    str[strlen(str)-1] = '\0';

    _transformar_str(str, out);
    transformar_str(out, fd);
    printf("\n'%s' e palindromo: %i", out, palindromo(fd));
    //@end

    return 0;
}

//@start func
// bool normalizar(char* c) {
//     if (*c < 90) *c += 32;

//     return (*c-97 >= 0 && *c-122 <= 0); // retorna se é uma letra ou não
// }

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

bool normalizar(char* c) {
    if (*c < 90) *c += 32;

    return (*c-97 >= 0 && *c-122 <= 0); // retorna se é uma letra ou não
}

void _transformar_str(char* str, char* out) {
    char c;
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        c = str[i];
        if (normalizar(&c))
            out[j++] = c;
    }

    out[j+1] = '\0';
}
//@end