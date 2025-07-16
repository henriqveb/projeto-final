#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct
{
    NoFila *topo;
} Pilha;

Pilha *criar_pilha();
void liberar_pilha(Pilha *p);
int empilhar(Pilha *p, Processo processo);
int desempilhar(Pilha *p, Processo *processo_removido);
int esta_vazia_pilha(Pilha *p);
void imprimir_pilha(Pilha *p);

#endif
