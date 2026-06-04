#include <stdio.h>

typedef struct
{
    char cpf[15];
    char nome[100];
    char dataNascimento[11];

} Dependente; // nessesario outro struct pq a pessoa pode ter mais de 1 dependente!!

typedef struct
{
    // Dados do titular
    char cpf[15];
    char nome[100];
    int sexo;
    char email[100];
    char dataNascimento[11];
    char telefone[15];

    // Dependentes
    Dependente dependentes[10];
    int qtdDependentes;

    int plano;
    float valorPlano;
    char vencimentoPlano[11];

} Cliente;

void cadastrarCliente()
{
    Cliente cliente;

    printf("\n===== CADASTRO DE CLIENTE =====\n");

    printf("CPF: ");
    scanf("%s", cliente.cpf);

    printf("Nome: ");
    scanf(" %s", cliente.nome);

    printf("Sexo (1-Feminino / 2-Masculino): ");
    scanf("%d", &cliente.sexo);

    printf("Email: ");
    scanf("%s", cliente.email);

    printf("Data de nascimento (dd/mm/aaaa): ");
    scanf("%s", cliente.dataNascimento);

    printf("Telefone: ");
    scanf("%s", cliente.telefone);

    printf("\nQuantidade de dependentes: ");
    scanf("%d", &cliente.qtdDependentes);

    if (cliente.qtdDependentes > 10)
    {
        cliente.qtdDependentes = 10;
    }

    for (int i = 0; i < cliente.qtdDependentes; i++)
    {
        printf("\n===== DEPENDENTE %d =====\n", i + 1);

        printf("CPF: ");
        scanf("%s", cliente.dependentes[i].cpf);

        printf("Nome: ");
        scanf(" %s", cliente.dependentes[i].nome);

        printf("Data de nascimento: ");
        scanf("%s", cliente.dependentes[i].dataNascimento);
    }

    printf("\n===== PLANO DE SAUDE =====\n");

    printf("1 - Ouro\n");
    printf("2 - Diamante\n");
    printf("3 - Prata\n");
    printf("4 - Esmeralda\n");

    printf("Escolha o plano: ");
    scanf("%d", &cliente.plano);

    printf("Data de vencimento do plano: ");
    scanf("%s", cliente.vencimentoPlano);

    printf("\nCliente cadastrado com sucesso!\n");
}

int buscarCPF()
{
    return 0;
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
    return 0;
}

void mostrarRelatorios()
{
}

void menu()
{
    int opcao = -1;

    while (opcao != 0)
    {
        printf("\n===== NUCLEO SAUDE =====\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Editar Cliente\n");
        printf("3 - Remover Cliente\n");
        printf("4 - Listagem Geral\n");
        printf("5 - Listagem por Plano\n");
        printf("6 - Listagem dos Vencimentos do Plano de Saude do Mes\n");
        printf("0 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarCliente();
            break;

        case 2:
            editarCliente();
            break;

        case 3:
            removerCliente();
            break;

        case 4:
            listarClientes();
            break;

        case 5:
            mostrarRelatorios();
            break;

        case 6:
            printf("\nFuncao ainda nao implementada.\n");
            break;

        case 0:
            printf("\nEncerrando sistema...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }
    }
}

int main()
{
    menu();
    return 0;
}