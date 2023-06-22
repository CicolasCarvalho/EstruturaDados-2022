// Nícolas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 24 03 2023

#ifndef FILADUPLA_H
#define FILADUPLA_H

//@start defn
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
//@end

#endif