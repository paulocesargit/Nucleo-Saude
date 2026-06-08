#include <stdio.h>
#include <string.h>

#define DADOS "clientes.txt"
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
    int idade;
    char telefone[15];

    // Dependentes
    Dependente dependentes[10];
    int qtdDependentes;

    int plano;
    float valorPlano;
    char vencimentoPlano[11];

} Cliente;

int validarData(char data[])
{
    int dia, mes, ano, maxDias;

    if (strlen(data) != 8)
        return 0;

    sscanf(data, "%2d%2d%4d", &dia, &mes, &ano);

    if (mes == 2)
    {

        maxDias = 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {

        maxDias = 30;
    }
    else
    {

        maxDias = 31;
    }

    if (dia < 1 || dia > maxDias)
    {
        return 0;
    }
    if (mes < 1 || mes > 12)
    {
        return 0;
    }

    if (ano < 2026 || ano > 2030)
    {
        return 0;
    }

    return 1;
}

float calcularPlano(Cliente cliente)
{
    float valor = 0;

    switch (cliente.plano)
    {
    case 1:
        valor = 300.00;
        break;

    case 2:
        valor = 400.00;
        break;

    case 3:
        valor = 200.00;
        break;

    case 4:
        valor = 500.00;
        break;
    }

    if (cliente.sexo == 1 && cliente.idade >= 13 && cliente.idade <= 35)
        valor += valor * 0.30;

    if (cliente.qtdDependentes > 1)
        valor -= valor * 0.20;

    if (cliente.idade < 13)
        valor -= valor * 0.30;

    if (cliente.idade >= 60)
        valor += valor * 0.40;

    return valor;
}

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

    printf("Idade: ");
    scanf("%d", &cliente.idade);

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

    cliente.valorPlano = calcularPlano(cliente);

    do
    {
        printf("Data de vencimento (DDMMAAAA): ");
        scanf("%s", cliente.vencimentoPlano);

        if (strchr(cliente.vencimentoPlano, '/') != NULL)
        {
            printf("Nao use barras!\n");
        }

        if (!validarData(cliente.vencimentoPlano))
            printf("Data invalida!\n");

    } while (!validarData(cliente.vencimentoPlano));

    FILE *dados = fopen(DADOS, "ab");

    if (dados == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
        return;
    }

    fwrite(&cliente, sizeof(Cliente), 1, dados);

    fclose(dados);

    printf("\nCliente cadastrado com sucesso!\n");
    printf("Valor final do plano: R$ %.2f\n", cliente.valorPlano);
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

void listarVencimentosMes()
{
    int mes;

    printf("\nDigite o mes (1-12): ");
    scanf("%d", &mes);

    FILE *dados = fopen(DADOS, "rb");

    if (dados == NULL)
    {
        printf("\nDados nao encontrado.\n");
        return;
    }

    Cliente cliente;
    int dia, mesVenc, ano;
    int encontrou = 0;

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        sscanf(cliente.vencimentoPlano, "%2d%2d%4d", &dia, &mesVenc, &ano);

        if (mesVenc == mes)
        {
            printf("\nNome: %s", cliente.nome);
            printf("\nCPF: %s", cliente.cpf);
            printf("\nVencimento: %s\n", cliente.vencimentoPlano);
            encontrou = 1;
        }
    }

    fclose(dados);

    if (!encontrou)
    {
        printf("\nNenhum vencimento encontrado.\n");
    }
}

void listarporplano()
{

    int plano;

    printf("\n1 - Ouro");
    printf("\n2 - Diamante");
    printf("\n3 - Prata");
    printf("\n4 - Esmeralda");

    printf("\n\nPlano desejado: ");
    scanf("%d", &plano);

    FILE *dados = fopen(DADOS, "rb");

    if (dados == NULL)
    {
        printf("\nDados nao encontrado.\n");
        return;
    }

    Cliente cliente;
    int encontrou = 0;

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        if (cliente.plano == plano)
        {
            printf("\nCPF: %s", cliente.cpf);
            printf("\nNome: %s", cliente.nome);
            printf("\nValor: %.2f\n", cliente.valorPlano);

            encontrou = 1;
        }
    }

    fclose(dados);

    if (!encontrou)
        printf("\nNenhum cliente encontrado.\n");
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
            listarporplano();
            break;

        case 6:
            listarVencimentosMes();
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