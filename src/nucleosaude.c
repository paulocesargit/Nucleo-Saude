#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"
#define CIANO "\033[36m"
#define RESET "\033[0m"

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

    float valorBase = valor;

    if (cliente.sexo == 1 && cliente.idade >= 13 && cliente.idade < 35)
        valor += valorBase * 0.30;

    if (cliente.qtdDependentes > 1)
        valor -= valorBase * 0.20;

    if (cliente.idade < 13)
        valor -= valorBase * 0.30;

    if (cliente.idade >= 60)
        valor += valorBase * 0.40;

    return valor;
}

void cadastrarCliente()
{

    Cliente cliente;

    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "       CADASTRO DE CLIENTE             \n" RESET);
    printf(CIANO "====================================\n\n" RESET);

    do
    {
        printf("CPF: ");
        scanf("%s", cliente.cpf);

        if (strlen(cliente.cpf) != 11)
        {
            printf(AMARELO "CPF invalido! Digite 11 numeros.\n" RESET);
        }

    } while (strlen(cliente.cpf) != 11);

    printf("Nome: ");
    scanf("%s", cliente.nome);

    do
    {
        printf("Sexo (1-Feminino / 2-Masculino): ");
        scanf("%d", &cliente.sexo);

        if (cliente.sexo != 1 && cliente.sexo != 2)
        {
            printf(AMARELO "Opcao invalida! Digite 1 ou 2.\n" RESET);
        }

    } while (cliente.sexo != 1 && cliente.sexo != 2);

    printf("Email: ");
    scanf("%s", cliente.email);

    do
    {
        printf("Idade: ");
        scanf("%d", &cliente.idade);

        if (cliente.idade < 1 || cliente.idade > 120)
        {
            printf(AMARELO "Idade invalida!\n" RESET);
        }

    } while (cliente.idade < 1 || cliente.idade > 120);

    do
    {
        printf("Telefone: ");
        scanf("%s", cliente.telefone);

        if (strlen(cliente.telefone) != 11)
        {
            printf(AMARELO "Telefone invalido!\n" RESET);
        }

    } while (strlen(cliente.telefone) != 11);

    do
    {
        printf("\nQuantidade de dependentes: ");
        scanf("%d", &cliente.qtdDependentes);

        if (cliente.qtdDependentes < 0 || cliente.qtdDependentes > 10)
        {
            printf(AMARELO "Quantidade invalida! Digite entre 0 e 10.\n" RESET);
        }

    } while (cliente.qtdDependentes < 0 || cliente.qtdDependentes > 10);
    system("cls");

    for (int i = 0; i < cliente.qtdDependentes; i++)
    {

        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "           DEPENDENTE %d           \n" RESET, i + 1);
        printf(CIANO "====================================\n\n" RESET);

        printf("CPF: ");
        scanf("%s", cliente.dependentes[i].cpf);

        printf("Nome: ");
        scanf(" %s", cliente.dependentes[i].nome);

        printf("Data de nascimento: ");
        scanf("%s", cliente.dependentes[i].dataNascimento);
        system("cls");
    }

    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "         PLANO DE SAUDE              \n" RESET);
    printf(CIANO "====================================\n\n" RESET);

    printf("1 - Ouro\n");
    printf("2 - Diamante\n");
    printf("3 - Prata\n");
    printf("4 - Esmeralda\n");

    do
    {

        printf("Escolha o plano: ");
        scanf("%d", &cliente.plano);

        if (cliente.plano < 1 || cliente.plano > 4)
        {
            printf(AMARELO "Opcao invalida! Digite de 1 a 4.\n" RESET);
        }

    } while (cliente.plano < 1 || cliente.plano > 4);

    cliente.valorPlano = calcularPlano(cliente);

    do
    {
        printf("Data de vencimento (DDMMAAAA): ");
        scanf("%s", cliente.vencimentoPlano);

        if (strchr(cliente.vencimentoPlano, '/') != NULL)
        {
            printf(VERMELHO "Nao use barras!\n" RESET);
        }

        if (!validarData(cliente.vencimentoPlano))
        {
            printf(AMARELO "Data invalida!\n" RESET);
        }

    } while (!validarData(cliente.vencimentoPlano));

    FILE *dados = fopen(DADOS, "ab");

    if (dados == NULL)
    {
        printf(VERMELHO "\nErro ao abrir arquivo!\n" RESET);
        return;
    }

    fwrite(&cliente, sizeof(Cliente), 1, dados);

    fclose(dados);

    printf(VERDE "\nCliente cadastrado com sucesso!\n" RESET);
    printf("Valor final do plano: R$ %.2f\n", cliente.valorPlano);

    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    getchar();

    system("cls");
}

int buscarCPF(char cpf[])
{
    FILE *dados = fopen(DADOS, "rb");

    if (dados == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return -1;
    }

    Cliente cliente;
    int pos = 0;

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        if (strcmp(cliente.cpf, cpf) == 0)
        {
            printf("\nCliente encontrado!\n");
            printf("Nome: %s\n", cliente.nome);

            fclose(dados);
            return pos;
        }

        pos++;
    }

    printf("\nCliente nao cadastrado!\n");

    fclose(dados);
    return -1;
}

void listarClientes()
{
}

void editarCliente()
{
    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "         Editar cliente              \n" RESET);
    printf(CIANO "====================================\n\n" RESET);

    char cpf[11];

    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    int pos = buscarCPF(cpf);

    if (pos == -1)
    {
        return;
    }

    FILE *dados = fopen(DADOS, "r+b");

    if (dados == NULL)
    {
        printf(VERMELHO "Erro ao abrir arquivo!\n" RESET);
        return;
    }

    Cliente cliente;

    fseek(dados, pos * sizeof(Cliente), SEEK_SET);

    fread(&cliente, sizeof(Cliente), 1, dados);

    system("cls");

    int op;

    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "    ESCOLHA UMA OPCAO PARA ALTERAR\n    " RESET);
    printf(CIANO "=======================================\n" RESET);
    printf("1 - Nome\n");
    printf("2 - Idade\n");
    printf("3 - Email\n");
    printf("4 - Telefone\n");
    printf("Opcao: ");
    scanf("%d", &op);

    system("cls");

    switch (op)
    {
    case 1:

        printf("Novo nome: ");
        scanf("%s", cliente.nome);
        break;

    case 2:
        printf("Nova idade: ");
        scanf("%d", &cliente.idade);
        break;

    case 3:
        printf("Novo email: ");
        scanf("%s", cliente.email);
        break;

    case 4:
        printf("Novo telefone: ");
        scanf("%s", cliente.telefone);
        break;

    default:
        printf("Opcao invalida!\n");
        fclose(dados);
        return;
    }

    fseek(dados, pos * sizeof(Cliente), SEEK_SET);

    fwrite(&cliente, sizeof(Cliente), 1, dados);

    fclose(dados);

    printf(VERDE "\nCliente atualizado com sucesso!\n" RESET);
    printf("Pressione ENTER para Continuar....\n ");

    getchar();
    getchar();

    system("cls");
}

void removerCliente()
{
    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "         REMOVER CLIENTE              \n" RESET);
    printf(CIANO "====================================\n\n" RESET);

    char cpf[11];

    printf("Digite o CPF do cliente que deseja remover: ");
    scanf("%s", cpf);

    if (buscarCPF(cpf) == -1)
    {
        printf("Cliente nao encontrado!\n");
        return;
    }

    FILE *dados = fopen(DADOS, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (dados == NULL || temp == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    Cliente cliente;

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        if (strcmp(cliente.cpf, cpf) != 0)
        {
            fwrite(&cliente, sizeof(Cliente), 1, temp);
        }
    }

    fclose(dados);
    fclose(temp);

    remove(DADOS);
    rename("temp.dat", DADOS);

    printf("\nCliente removido com sucesso!\n");
}

void listarVencimentosMes()
{
    int mes;

    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "           DIGITE O MES (1-12)           \n" RESET);
    printf(CIANO "====================================\n\n" RESET);
    do
    {
        printf("\nDigite: ");
        scanf("%d", &mes);

        if (mes < 1 || mes > 12)
        {
            printf(AMARELO "Digite um mes valido" RESET);
        }

    } while (mes < 1 || mes > 12);

    FILE *dados = fopen(DADOS, "rb");

    if (dados == NULL)
    {
        printf(VERMELHO "\nDados nao encontrado.\n" RESET);
        return;
    }
    system("cls");
    char *meses[] = {
        "", "JANEIRO", "FEVEREIRO", "MARCO",
        "ABRIL", "MAIO", "JUNHO",
        "JULHO", "AGOSTO", "SETEMBRO",
        "OUTUBRO", "NOVEMBRO", "DEZEMBRO"};
    Cliente cliente;
    int dia, mesVenc, ano;
    int encontrou = 0;
    int contador = 1;

    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "     VENCIMENTOS DE %s      \n" RESET, meses[mes]);
    printf(CIANO "====================================\n\n" RESET);

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        sscanf(cliente.vencimentoPlano, "%2d%2d%4d", &dia, &mesVenc, &ano);

        if (mesVenc == mes)
        {
            printf("\nCliente %d\n", contador);
            printf("\nNome: %s", cliente.nome);
            printf("\nCPF: %s", cliente.cpf);
            printf("\nVencimento: %s\n", cliente.vencimentoPlano);
            printf("\n------------------------------------\n");

            contador++;
            encontrou = 1;
        }
    }

    fclose(dados);

    printf("\nTotal de vencimentos encontrados: %d\n", contador - 1);

    if (!encontrou)
    {
        printf(VERMELHO "\nNenhum vencimento encontrado.\n" RESET);
    }

    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    getchar();

    system("cls");
}

void listarporplano()
{

    int plano;

    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "           PLANO DESEJADO           \n" RESET);
    printf(CIANO "====================================\n\n" RESET);

    printf("\n1 - Ouro");
    printf("\n2 - Diamante");
    printf("\n3 - Prata");
    printf("\n4 - Esmeralda\n");

    do
    {

        printf("\nEscolha: ");
        scanf("%d", &plano);

        if (plano < 1 || plano > 4)
        {
            printf(AMARELO "Opcao invalida! Digite de 1 a 4.\n" RESET);
        }

    } while (plano < 1 || plano > 4);

    FILE *dados = fopen(DADOS, "rb");

    if (dados == NULL)
    {
        printf(VERMELHO "\nDados nao encontrado.\n" RESET);
        return;
    }
    system("cls");

    switch (plano)
    {
    case 1:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "            PLANO OURO             \n" RESET);
        printf(CIANO "====================================\n\n" RESET);
        break;

    case 2:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "          PLANO DIAMANTE           \n" RESET);
        printf(CIANO "====================================\n\n" RESET);
        break;

    case 3:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "            PLANO PRATA            \n" RESET);
        printf(CIANO "====================================\n\n" RESET);
        break;

    case 4:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "          PLANO ESMERALDA          \n" RESET);
        printf(CIANO "====================================\n\n" RESET);
        break;

    default:
        printf(VERMELHO "\nPlano invalido!\n" RESET);
        return;
    }

    Cliente cliente;
    int encontrou = 0;
    int contador = 1;

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        if (cliente.plano == plano)
        {
            printf("\nCliente %d\n", contador);
            printf("\nCPF: %s", cliente.cpf);
            printf("\nNome: %s", cliente.nome);
            printf("\nValor: %.2f\n", cliente.valorPlano);

            printf("\n------------------------------------\n");

            contador++;
            encontrou = 1;
        }
    }

    fclose(dados);

    if (!encontrou)
        printf(AMARELO "\nNenhum cliente encontrado.\n" RESET);

    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    getchar();

    system("cls");
}

void menu()
{
    int opcao = -1;

    while (opcao != 0)
    {
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "         NUCLEO SAUDE              \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        printf(VERDE "1" RESET " - Cadastrar Cliente\n");
        printf(VERDE "2" RESET " - Editar Cliente\n");
        printf(VERDE "3" RESET " - Remover Cliente\n");
        printf(VERDE "4" RESET " - Listagem Geral\n");
        printf(VERDE "5" RESET " - Listagem por Plano\n");
        printf(VERDE "6" RESET " - Vencimentos do Mes\n");
        printf(AMARELO "0" RESET " - Sair\n");

        printf(CIANO "\n====================================\n\n" RESET);

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        system("cls");

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