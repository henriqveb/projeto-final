#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char interessado[100];
    char assunto[150];
} Processo;

typedef struct no_fila
{
    Processo processo;
    struct no_fila *proximo;
} NoFila;

typedef struct
{
    NoFila *inicio;
    NoFila *fim;
} Fila;

Fila *criar_fila();
void liberar_fila(Fila *f);
int enfileirar(Fila *f, Processo processo);
int desenfileirar(Fila *f, Processo *processo_removido);
int esta_vazia_fila(Fila *f);
void imprimir_fila(Fila *f);

#endif
