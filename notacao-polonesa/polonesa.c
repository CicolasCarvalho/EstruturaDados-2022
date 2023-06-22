#include <stdio.h>
#include <string.h>
#include "pilha.h"

pilha* tokenizer(char* s);
int operador(char c);
pilha* RPN(pilha *c);

int main(void) {
    pilha *p = pilha_init();
    char str[] = "(1+2*3)"; // a+b == (a+b)

    printf("%s\n\n", str);
    pilha *pilha_token = tokenizer(str);

    pilha_print(*pilha_token);
    printf("\n");

    pilha *aux;

    while ((aux = RPN(pilha_token)) != NULL) {
        pilha_empilha_pilha(p, aux);
    }

    pilha_print(*p);
    pilha_apaga(p);
    return 0;
}


int operador(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') return 1;
    return 0;
}

pilha* tokenizer(char* s) {
    // char *cstr;
    // strncpy(cstr, s, 1);
    // printf("%i", strlen(s));

    // char c = cstr[0];
    // pilha* p = pilha_init();

    // if (c == ')') {
    //     return NULL;
    // } else if (c == '(') {
    //     pilha *aux;
    //     while ((aux = tokenizer(pilha_caracteres, s)) != NULL) {
    //         pilha_empilha_pilha(p, aux);
    //     }

    //     if (s[1] == '*') pilha_empilha(pilha_caracteres, '(');
    //     pilha_empilha_pilha(pilha_caracteres, p);
    // } else if (c == '*') {
    //     pilha_empilha(pilha_caracteres, '*');
    //     pilha_empilha_pilha(pilha_caracteres, tokenizer(pilha_caracteres, s));
    //     pilha_empilha(pilha_caracteres, ')');
    // } else {
    //     if (s[1] == '*') pilha_empilha(pilha_caracteres, '(');
    //     pilha_empilha(pilha_caracteres, s[0]);
    // }

    // TODO: Adicionar parenteses entre * e /
    pilha* pilha_caracteres = pilha_init();

    for (size_t i = 0; i < strlen(s); i++) {
        if (s[i] != ' ') {
            pilha_empilha(pilha_caracteres, s[i]);
        }
    }

    pilha_tipo val;
    pilha_tipo val_temp;
    pilha* temp = pilha_init();
    pilha* temp_direita = pilha_init();
    pilha* temp_esquerda = pilha_init();
    int prioridade = 0;

    while (pilha_desempilha(pilha_caracteres, &val)) {
        if (operador(val) && prioridade) {
            while (!operador(val_temp)) {
                pilha_empilha(temp_direita, val_temp);
                if (!pilha_desempilha(temp, &val_temp)) break;
            }
            pilha_desempilha(temp, &val_temp);
            // pilha_empilha(temp_direita, '(');

            pilha_empilha_pilha(temp, temp_esquerda);
            pilha_empilha(temp, '*');
            pilha_empilha_pilha(temp, temp_direita);
            prioridade = 0;
        }

        if (val == '*') {
            // pilha_empilha(temp_esquerda, ')');
            pilha_desempilha(temp, &val_temp);
            while (!operador(val_temp)) {
                pilha_empilha(temp_esquerda, val_temp);
                if (!pilha_desempilha(temp, &val_temp)) break;
            }
            // pilha_empilha(temp, val_temp);

            pilha_empilha(temp, val);
            // pilha_empilha_pilha(temp, temp_esquerda);
            prioridade = 1;
        }

        else pilha_empilha(temp, val);
    }

    // pilha_caracteres = pilha_inverte(pilha_caracteres);

    return temp;
}

pilha* RPN(pilha* p) {
    pilha* pilha_return = pilha_init();

    char c;
    if (pilha_desempilha(p, &c) == 0) return NULL;

    if (c == ')') {
        return NULL;
    } else if (c == '(') {
        pilha *aux;
        while ((aux = RPN(p)) != NULL) {
            pilha_empilha_pilha(pilha_return, aux);
        }
    } else if (c == '+') {
        pilha_empilha_pilha(pilha_return, RPN(p));
        pilha_empilha(pilha_return, c);
    } else if (c == '*') {
        pilha_empilha_pilha(pilha_return, RPN(p));
        pilha_empilha(pilha_return, c);
    } else {
        pilha_empilha(pilha_return, c);
    }

    return pilha_return;
}