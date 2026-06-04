#include <stdio.h>

typedef struct
{
    // variaveis cliente_titular
    char nome_titular[100];
    char cpf_titular[15];
    int idade;
    int sexo;
    char telefone[15];
    char data_cascimento_titular[10];
    char email[20];

    // variaveis cliente_terceiro
    char nome_terceiro[100];
    char cpf_terceiro[15];
    char data_nasci_terceiro[10];

    // Variaveis planos
    int plano;
    float valorPlano;

} Cliente;

void cadastrarCliente()
{
    Cliente cliente; // variavel cliente para conectar os campos de variaveis e cadastro!

    printf("\n--- CADASTRO CLIENTE ---\n");

    printf("\nInforme o nome do cliente: ");
    scanf("%s", cliente.nome_titular);

    printf("\nInforme o CPF do cliente (so os numeros): ");
    scanf("%s", cliente.cpf_titular);

    printf("\nInforme a idade do cliente: \n");
    scanf("%d", &cliente.idade);

    printf("\nInforme o sexo do cliente (1-maculino / 2-feminino): ");
    scanf("%d", &cliente.sexo);

    printf("\nInforme o telefone do cliente: ");
    scanf("%s", cliente.telefone);

    printf("\nInforme a data de nascimento do cliente: ");
    scanf("%s", cliente.data_cascimento_titular);

    printf("\nInforme o E-mail do cliente: ");
    scanf("%s", cliente.email);
}

void cadastro_cliente_terceiro()
{
    Cliente terceiro;

    printf("\n--- CADASTRO CLIENTE TERCEIRO ---\n");

    printf("\nInforme o nome do cliente: ");
    scanf("%s", terceiro.nome_terceiro);

    printf("\nInforme o CPF do cliente (so os numeros): ");
    scanf("%s", terceiro.cpf_terceiro);

    printf("\nInforme a data de nascimento do cliente: ");
    scanf("%s", terceiro.data_nasci_terceiro);
}

void cadastrar_plano()
{
    Cliente planos;

    printf("\n--- CADASTRAR PLANOS ---\n");

    printf("\nInforme o valor do plano de saude: ");
    scanf("%f", &planos.valorPlano);

    printf("\nInforme a data de vencimento do plano de saude: ");
    scanf("%d", &planos.plano);
}

int buscarCPF()
{
}

void listarClientes()
{
}

void editarCliente()
{
}

void removerCliente()
{
}

float calcularPlano()
{
}

void mostrarRelatorios()
{
}

void menu()
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