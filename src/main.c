#include <stdio.h>
#include "../include/cliente.h"

void menu ()
{
    printf("---BEM VINDO AO NUCLEO SAUDE---\n");

    int options = 0;

    while (options != 7)
    {

        printf("Opcao 1 (Cadastrar Cliente)\n");
        printf("Opcao 2 (Editar Cliente)\n");
        printf("Opcao 3 (Remover Cliente)\n");
        printf("Opcao 4 (Listagem Geral)\n");
        printf("Opcao 5 (Listagem do Plano)\n");
        printf("Opcao 6 (Listagem dos Vencimentos do Plano de Saude do Mes)\n");
        printf("Opcao 7 (Sair)\n");

        printf("ESCOLHA: ");
        scanf("%d", &options);

        switch (options)
        {
            case 1:
            {
                int opcoes = 0;

                printf("\n---MENU DE CADASTRO---\n");

                while (opcoes != 4)
                {
                    printf("Opcao 1 (Cadastrar cliente titular)\n");
                    printf("Opcao 2 (Cadastrar cliente terceiro)\n");
                    printf("Opcao 3 (Cadastrar plano)\n");
                    printf("Opcao 4 (Sair)\n");

                    printf("ESCOLHA: ");
                    scanf("%d", &opcoes);

                    if (opcoes == 1)
                    {
                        cadastrarCliente();
                    }

                    if (opcoes == 2)
                    {
                        cadastro_cliente_terceiro();
                    }

                    if (opcoes == 3)
                    {
                        cadastrar_plano();
                    }

                    if (opcoes == 4)
                    {
                        printf("\nRetornando ao menu principal...\n");
                    }
                }

                break;
            }

            default:
                break;
        }
    }
}

int main()
{
    menu();
    return 0;
}