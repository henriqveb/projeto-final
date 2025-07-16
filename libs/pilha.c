#include "pilha.h"

Pilha *criar_pilha()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));

    if (p != NULL)
    {
        p->topo = NULL;
    }

    return p;
}

void liberar_pilha(Pilha *p)
{
    if (p != NULL)
    {
        NoFila *no;

        while (p->topo != NULL)
        {
            no = p->topo;
            p->topo = p->topo->proximo;
            free(no);
        }

        free(p);
    }
}

int empilhar(Pilha *p, Processo processo)
{
    if (p == NULL)
    {
        return 0; // Pilha não foi criada
    }

    NoFila *no = (NoFila *)malloc(sizeof(NoFila));
    if (no == NULL)
    {
        return 0; // Erro de alocação de memória
    }

    no->processo = processo;
    no->proximo = p->topo;
    p->topo = no;

    return 1;
}

int desempilhar(Pilha *p, Processo *processo_removido)
{
    if (p == NULL || esta_vazia_pilha(p))
    {
        return 0; // Pilha não existe ou está vazia
    }

    NoFila *no = p->topo;
    *processo_removido = no->processo;
    p->topo = p->topo->proximo;

    free(no);
    return 1;
}

int esta_vazia_pilha(Pilha *p)
{
    if (p == NULL)
    {
        return 1;
    }
    return (p->topo == NULL);
}

void imprimir_pilha(Pilha *p)
{
    if (esta_vazia_pilha(p))
    {
        printf("Pilha de processos esta vazia.\n");
        return;
    }

    NoFila *no_atual = p->topo;
    printf("--- Pilha de Processos com Pendencia (para reanalise) ---\n");
    while (no_atual != NULL)
    {
        printf("ID: %d | Interessado: %s | Assunto: %s\n",
               no_atual->processo.id,
               no_atual->processo.interessado,
               no_atual->processo.assunto);
        no_atual = no_atual->proximo;
    }
    printf("----------------------------------------------------------\n");
}
