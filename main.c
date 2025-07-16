#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/fila.h"
#include "libs/pilha.h"

// Função para resolver problemas de leitura do scanf e evitar seleção de opções erradas
void limpar_entrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu()
{
    printf("\n--- Sistema de Gerenciamento de Processos Administrativos ---\n");
    printf("1. Adicionar novo processo na fila de analise\n");
    printf("2. Analisar proximo processo da fila\n");
    printf("3. Reanalisar processo da pilha de pendencias\n");
    printf("4. Visualizar fila de processos atual\n");
    printf("5. Visualizar pilha de processos pendentes\n");
    printf("6. Sair\n");
    printf("----------------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Fila *fila_de_processos = criar_fila();
    Pilha *pilha_de_pendencias = criar_pilha();

    if (fila_de_processos == NULL || pilha_de_pendencias == NULL)
    {
        printf("Nao foi possivel alocar memoria para as estruturas.\n");
        return 1;
    }

    int opcao;
    int proximo_id = 1;

    do
    {
        exibir_menu();
        scanf("%d", &opcao);
        limpar_entrada();

        switch (opcao)
        {
        case 1:
        {
            Processo novo_processo;
            novo_processo.id = proximo_id++;

            printf("Digite o nome do interessado: ");
            scanf("%99s", novo_processo.interessado);

            printf("Digite o assunto do processo: ");
            scanf("%149s", novo_processo.assunto);

            if (enfileirar(fila_de_processos, novo_processo))
            {
                printf("\nProcesso %d adicionado com sucesso.\n", novo_processo.id);
            }
            else
            {
                printf("\nErro ao adicionar processo.\n");
            }
            break;
        }

        case 2:
        {
            Processo processo_analisado;
            if (desenfileirar(fila_de_processos, &processo_analisado))
            {
                printf("\n--- Analisando Processo ---\n");
                printf("ID: %d\nInteressado: %s\nAssunto: %s\n",
                       processo_analisado.id, processo_analisado.interessado, processo_analisado.assunto);
                printf("---------------------------\n");

                char resultado;
                printf("Qual o resultado da analise? ((A)provado, (P)endente): ");
                scanf(" %c", &resultado);
                limpar_entrada();

                if (resultado == 'P' || resultado == 'p')
                {
                    empilhar(pilha_de_pendencias, processo_analisado);
                    printf("Processo movido para pendencias.\n");
                }
                else
                {
                    printf("Processo %d finalizado e arquivado.\n", processo_analisado.id);
                }
            }
            else
            {
                printf("\nNao ha processos para analisar.\n");
            }
            break;
        }

        case 3:
        {
            Processo processo_reanalisado;
            if (desempilhar(pilha_de_pendencias, &processo_reanalisado))
            {
                printf("Processo %d (%s) foi corrigido e aprovado.\n",
                       processo_reanalisado.id, processo_reanalisado.assunto);
            }
            else
            {
                printf("\nNao ha processos pendentes.\n");
            }
            break;
        }

        case 4:
            imprimir_fila(fila_de_processos);
            break;

        case 5:
            imprimir_pilha(pilha_de_pendencias);
            break;

        case 6:
            break;

        default:
            printf("\nOpcao invalida.\n");
            break;
        }

    } while (opcao != 6);

    liberar_fila(fila_de_processos);
    liberar_pilha(pilha_de_pendencias);

    return 0;
}