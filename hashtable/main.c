#include <stdio.h>
#include <stdlib.h>
#define M 14

typedef struct TipoLetra {
    char letra[1];
} TipoLetra;

typedef struct Celula {
    TipoLetra Letra;
    struct Celula *Prox;
} Celula;

typedef struct TipoLista {
    struct Celula *Inicio;
    int tam;
} TipoLista;

void Inicializa_Tabela(TipoLista *Tabela[M]);

int main(void) {
    TipoLista* Tabela[M];

    Inicializa_Tabela(Tabela);
    return 0;
}

void Inicializa_Tabela(TipoLista *Tabela[M]) {
    for (int i = 0; i < 14; i++) {
        // TipoLista*
        Tabela[i] = malloc(sizeof(TipoLista));
        Tabela[i]->Inicio = NULL;
    }
    printf("pao\n");
}

