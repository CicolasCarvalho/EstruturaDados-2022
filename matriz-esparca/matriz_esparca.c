/*
    Nícolas dos Santos Carvalho
    Maringá, PR - Brasil
    12/03/2023
    Universidade Estadual de Maringá (UEM)

    Matrizes Esparças

    Este código é a implementação do exercicio 3 na página 59 do livro
    "Projeto de Algoritmos Com Implementações em Pascal e C" de Ziviani
    [Ziv93, página 59, exercício 3].

    obs.: No livro é pedido que implemente em Pascal, porém essa implementação
    foi feita em C.

    https://github.com/Cicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <locale.h>

// teste com macros -> esse macro desconstroi valor indexado
#define ESTENDER(VALOR_INDEXADO) \
    VALOR_INDEXADO.i, VALOR_INDEXADO.j, VALOR_INDEXADO.v
// Constante de controle de quando está rodando sem arquivos externos
// não haverá leitura de arquivos e os 3 vetores serão lidos no console
// Caso desativado durante a aplicação procurará por:
// - ./matrizes/matrizA.txt
// - ./matrizes/matrizB.txt
// - ./matrizes/matrizC.txt
#define STANDALONE 1
// Constante de controle se irá sair da aplicação por erros matemáticos
// como soma de matrizes com tamanhos diferentes ou multiplicação incompativel
#define ERRO_MATEMATICO 0

typedef struct matriz matriz;

struct matriz {
    matriz* direita;
    matriz* abaixo;

    int linha,
        coluna;
    float valor;
};

typedef struct {
    int i, j;
    float v;
} valor_indexado;

typedef struct {
    int largura, altura;
} tamanho_matriz;

matriz* matriz_init(int w, int h);
matriz* matriz_posicao(int i, int j, matriz* m);
tamanho_matriz matriz_tamanho(matriz* m);

matriz* matriz_ler(char* path);
void matriz_apaga(matriz* m);
void matriz_soma(matriz* a, matriz* b, matriz* c);
void matriz_mult(matriz* a, matriz* b, matriz* c);
void matriz_print(matriz* m);
void matriz_insere(int i, int j, float v, matriz* m);

void teste(void) {
    matriz *A, *B, *C;

    A = matriz_ler("./matrizes/matrizA.txt");
    printf("\n---A---\n");
    matriz_print(A);

    B = matriz_ler("./matrizes/matrizB.txt");
    printf("\n---B---\n");
    matriz_print(B);

    C = matriz_init(matriz_tamanho(A).largura, matriz_tamanho(B).altura);
    matriz_soma(A, B, C);
    printf("\n---A+B = C---\n");
    matriz_print(C);
    matriz_apaga(C);

    C = matriz_init(matriz_tamanho(A).largura, matriz_tamanho(B).largura);
    printf("\n---AxB = C---\n");
    matriz_mult(A, B, C);
    matriz_print(C);
    matriz_apaga(B);
    matriz_apaga(C);

    B = matriz_ler("./matrizes/matrizC.txt");
    printf("\n---A---\n");
    matriz_print(A);
    printf("\n---B---\n");
    matriz_print(B);

    C = matriz_init(matriz_tamanho(A).largura, matriz_tamanho(A).largura);
    matriz_soma(A, B, C);
    printf("\n---A+B = C---\n");
    matriz_print(C);

    matriz_mult(A, B, C);
    printf("\n---AxB = C---\n");
    matriz_print(C);

    matriz_mult(B, B, C);
    printf("\n---BxB = C---\n");
    matriz_print(C);

    printf("\n---B---\n");
    matriz_print(B);
    printf("\n---B---\n");
    matriz_print(B);
    printf("\n---C---\n");
    matriz_print(C);

    matriz_apaga(A);
    matriz_apaga(B);
    matriz_apaga(C);
}

int main(void) {
    setlocale(LC_ALL, "portuguese");

    if (STANDALONE) {
        printf(
            "Regras para inserção de matriz:\n"
            "- Primeira linha o tamanho\n"
            "- Demais linhas com 3 argumentos seprados por virgula (i, j, valor)\n\n"
            "Ex.: \n"
            "4, 4 \n"
            "1, 1, 50.0 \n"
            "2, 1, 10.0 \n"
            "2, 3, 20.0 \n"
            "4, 1, -30.0 \n"
            "4, 3, -60.0 \n"
            "4, 4, 5.0 \n\n"
        );
    }

    teste();

    return 0;
}

valor_indexado converter_linha(char* str) {
    valor_indexado valor = {
        .i = -1,
        .j = -1,
        .v = -1
    };

    valor.i = atoi(strtok(str, ","));
    valor.j = atoi(strtok(NULL, ","));
    valor.v = atof(strtok(NULL, ","));

    return valor;
}

tamanho_matriz matriz_tamanho(matriz* m) {
    tamanho_matriz tam = {
        .altura = 0,
        .largura = 0
    };

    matriz* coluna = m->direita;
    matriz* linha = m->abaixo;

    while(coluna != m){
        coluna = coluna->direita;
        tam.largura++;
    }

    while(linha != m){
        linha = linha->abaixo;
        tam.altura++;
    }

    return tam;
}

matriz* matriz_init(int largura, int altura) {
    matriz* p = malloc(sizeof(matriz));
    p->linha = p->coluna = -1;
    matriz* aux = p;

    for (int i = 1; i <= largura; i++) {
        matriz* q = malloc(sizeof(matriz));
        q->abaixo = q;
        q->linha = -1;

        aux->direita = q;
        aux = q;
    }

    aux->direita = p;

    aux = p;
    for (int i = 1; i <= altura; i++) {
        matriz* q = malloc(sizeof(matriz));
        q->direita = q;
        q->coluna = -1;

        aux->abaixo = q;
        aux = q;
    }

    aux->abaixo = p;

    return p;
}

matriz* matriz_ler(char* path) {
    char linha[20];
    valor_indexado valor_linha;

    int largura, altura;
    matriz* m;

    if (!STANDALONE) {
        FILE* arquivo = fopen(path, "r");

        if (arquivo == NULL) {
            printf("ERRO: não foi possivel abrir %s\n\n", path);
            assert(0);
        }

        if (fgets(linha, 20, arquivo) == NULL) {
            printf("ERROR: não há nenhum conteudo no arquivo");
            assert(0);
        }

        valor_linha = converter_linha(linha);
        largura = valor_linha.i;
        altura = valor_linha.j;

        m = matriz_init(largura, altura);

        while (fgets(linha, 20, arquivo) != NULL) {
            valor_linha = converter_linha(linha);

            matriz_insere(ESTENDER(valor_linha), m);
        }

        fclose(arquivo);
        return m;
    }

    printf("Insira o tamanho do vetor:\n");
    fgets(linha, 20, stdin);

    valor_linha = converter_linha(linha);
    largura = valor_linha.i;
    altura = valor_linha.j;
    m = matriz_init(largura, altura);

    printf("Insira os valores do vetor: (c ou C para cancelar)\n");
    fgets(linha, 20, stdin);
    linha[strlen(linha)-1] = '\0';
    while(linha[0] != 'c' && linha[0] != 'C') {
        valor_linha = converter_linha(linha);
        matriz_insere(ESTENDER(valor_linha), m);

        fgets(linha, 20, stdin);
        linha[strlen(linha)-1] = '\0';
    }

    return m;
}

matriz* matriz_posicao(int i, int j, matriz* m) {
    tamanho_matriz tamanho = matriz_tamanho(m);
    int largura = tamanho.largura,
        altura = tamanho.altura;

    if (i > altura || j > largura) assert(0);

    matriz* linha = m;
    matriz* q = NULL;

    for (int y = 0; y < altura; y++) {
        linha = linha->abaixo;
        q = linha;
        for (int x = 0; x < largura; x++) {
            do {
                q = q->direita;
                if(q->coluna == j && q->linha == i) {
                    return q;
                }
            } while(q != linha);
        }
    }

    return NULL;
}

void matriz_print(matriz* m) {
    matriz* q = NULL;
    matriz* linha = m;

    tamanho_matriz tamanho = matriz_tamanho(m);
    int largura = tamanho.largura,
        altura = tamanho.altura;

    for (int i = 0; i < altura; i++) {
        linha = linha->abaixo;
        q = linha;
        for (int j = 0; j < largura; j++) {
            int found = 0;
            float valor = 0.0;
            do {
                q = q->direita;
                if(q->coluna == j+1 && q->linha == i+1) {
                    valor = q->valor;
                    found = 1;
                }
            } while(q != linha);

            printf("%.1f\t", found?valor:0.0);
        }
        printf("\n");
    }
}

void matriz_insere(int i, int j, float v, matriz* m) {
    if (v == 0) return;

    tamanho_matriz tamanho = matriz_tamanho(m);

    int largura = tamanho.largura,
        altura = tamanho.altura;

    if (j > largura || i > altura) {
        printf("ERRO: posicao invalida: (%i, %i)\n\n", i, j);
        assert(0);
    }

    matriz* linha = m;
    matriz* coluna = m;

    for (int x = -1; x < j-1; x++) {
        coluna = coluna->direita;
    }
    for (int y = -1; y < i-1; y++) {
        linha = linha->abaixo;
    }

    matriz* n_ptr = malloc(sizeof(matriz));
    n_ptr->coluna = j;
    n_ptr->linha = i;
    n_ptr->valor = v;

    matriz* l = linha;
    do {
        if  (
                l->coluna < j &&
                (l->direita == linha || l->direita->coluna >= j)
            ) {
                // CASO JÁ TENHA NÃO SERÁ ADICIONADO
                if (l->direita->linha == i && l->direita->coluna == j) {
                    l->direita->valor = v;

                    break;
                }

                n_ptr->direita = l->direita;
                l->direita = n_ptr;
        }

        l = l->direita;
    } while (l != linha);

    matriz* c = coluna;
    do {
        if  (
                c->linha < i &&
                (c->abaixo == coluna || c->abaixo->linha >= i)
            ) {
                // CASO JÁ TENHA NÃO SERÁ ADICIONADO
                if (c->abaixo->linha == i && c->abaixo->coluna == j) break;

                n_ptr->abaixo = c->abaixo;
                c->abaixo = n_ptr;
        }

        c = c->abaixo;
    } while (c != coluna);
}

void matriz_apaga(matriz* m) {
    matriz* p = m;
    matriz* q = NULL;
    matriz* prox_direita = NULL;
    matriz* prox_abaixo = NULL;

    do {
        prox_abaixo = p->abaixo;

        prox_direita = q = p;
        do {
            prox_direita = prox_direita->direita;
            free(q);
            q = NULL;
        } while (prox_direita != p);

        p = prox_abaixo;
    } while (p != m);
}

void matriz_soma(matriz* a, matriz* b, matriz* c) {
    tamanho_matriz tamanho_a = matriz_tamanho(a);
    tamanho_matriz tamanho_b = matriz_tamanho(b);
    tamanho_matriz tamanho_c = matriz_tamanho(c);

    if (
        tamanho_c.largura != (tamanho_a.largura+tamanho_b.largura)/2 &&
        tamanho_c.altura != (tamanho_a.altura+tamanho_b.altura)/2
    ) {
        printf("ERRO: tamanhos incompativeis das matrizes da soma (todas devem ser do mesmo tamanho)\n");
        if (ERRO_MATEMATICO) assert(0);
        else return;
    }

    float v_a = 0.0;
    float v_b = 0.0;

    for (int i = 1; i <= tamanho_b.altura; i++) {
        for (int j = 1; j <= tamanho_a.largura; j++) {
            matriz* temp = matriz_posicao(i, j, a);
            v_a = temp==NULL?0.0:temp->valor;
            temp = matriz_posicao(i, j, b);
            v_b = temp==NULL?0.0:temp->valor;

            matriz_insere(i, j, v_a+v_b, c);
        }
    }
}

void matriz_mult(matriz* a, matriz* b, matriz* c) {
    tamanho_matriz tamanho_a = matriz_tamanho(a);
    tamanho_matriz tamanho_b = matriz_tamanho(b);
    tamanho_matriz tamanho_c = matriz_tamanho(c);

    if (
        tamanho_a.largura != tamanho_b.altura ||
        tamanho_c.largura != tamanho_b.largura ||
        tamanho_c.altura != tamanho_a.altura
    ) {
        printf(
            "ERRO: tamanhos incompativeis das matrizes da multiplicação (largura de A (%i, %i); altura de B (%i, %i); tamanho de C (%i, %i))\n",
            tamanho_a.largura, tamanho_a.altura,
            tamanho_b.largura, tamanho_b.altura,
            tamanho_c.largura, tamanho_c.altura
        );
        if (ERRO_MATEMATICO) assert(0);
        else return;
    }

    float v_a = 0.0;
    float v_b = 0.0;
    float v_c = 0.0;

    for (int i = 1; i <= tamanho_c.altura; i++) {
        for (int j = 1; j <= tamanho_c.largura; j++) {
            v_c = 0.0;

            for (int k = 1; k <= tamanho_a.largura; k++) {
                matriz* temp = matriz_posicao(i, k, a);
                v_a = temp==NULL?0.0:temp->valor;
                temp = matriz_posicao(k, j, b);
                v_b = temp==NULL?0.0:temp->valor;

                v_c += v_a*v_b;
            }

            matriz_insere(i, j, v_c, c);
        }
    }
}