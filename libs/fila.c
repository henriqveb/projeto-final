#include "fila.h"

Fila *criar_fila()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));

    if (f != NULL)
    {
        f->inicio = NULL;
        f->fim = NULL;
    }

    return f;
}

void liberar_fila(Fila *f)
{
    if (f != NULL)
    {
        NoFila *no = f->inicio;

        while (no != NULL)
        {
            NoFila *remover = no;
            no = no->proximo;
            free(remover);
        }

        free(f);
    }
}

int enfileirar(Fila *f, Processo processo)
{
    if (f == NULL)
    {
        return 0; // Fila não foi criada
    }

    NoFila *novo_no = (NoFila *)malloc(sizeof(NoFila));
    if (novo_no == NULL)
    {
        return 0; // Erro de alocação de memória
    }

    novo_no->processo = processo;
    novo_no->proximo = NULL;

    if (f->fim == NULL)
    {
        f->inicio = novo_no;
        f->fim = novo_no;
    }
    else
    {
        f->fim->proximo = novo_no;
        f->fim = novo_no;
    }

    // Retorna 1 para indicar sucesso
    return 1;
}

int desenfileirar(Fila *f, Processo *processo_removido)
{
    if (f == NULL || esta_vazia_fila(f))
    {
        return 0;
    }

    NoFila *no = f->inicio;
    *processo_removido = no->processo;

    f->inicio = f->inicio->proximo;

    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    free(no);

    // Retorna 1 para indicar sucesso
    return 1;
}

int esta_vazia_fila(Fila *f)
{
    if (f == NULL)
    {
        return 1;
    }

    return (f->inicio == NULL);
}

void imprimir_fila(Fila *f)
{
    if (esta_vazia_fila(f))
    {
        printf("Fila de processos esta vazia.\n");
        return;
    }

    NoFila *no = f->inicio;
    printf("--- Fila de Processos para Analise ---\n");
    while (no != NULL)
    {
        printf("ID: %d | Interessado: %s | Assunto: %s\n",
               no->processo.id,
               no->processo.interessado,
               no->processo.assunto);
        no = no->proximo;
    }
    printf("--------------------------------------\n");
}