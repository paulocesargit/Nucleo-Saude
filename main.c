#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int cpfJaCadastrado(char cpf[])
{
    FILE *dados = fopen(DADOS, "rb");

    if (dados == NULL)
        return 0;

    Cliente cliente;

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        if (strcmp(cliente.cpf, cpf) == 0)
        {
            fclose(dados);
            return 1;
        }
    }

    fclose(dados);
    return 0;
}

int validarCPF(char cpf[])
{
    if (strlen(cpf) != 11)
    {
        return 0;
    }

    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
        {
            return 0;
        }
    }

    return 1;
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

        if (!validarCPF(cliente.cpf))
        {
            printf("CPF invalido! Digite apenas numeros e exatamente 11 digitos.\n");
        }

        if (cpfJaCadastrado(cliente.cpf))
        {
            printf(VERMELHO "CPF ja cadastrado! Digite outro.\n" RESET);
            continue;
        }

        break;

    } while (1);

    printf("Nome: ");
    scanf(" %[^\n]", cliente.nome);

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

        int cpfInvalido;

        do
        {

            cpfInvalido = 0;

            printf("CPF: ");
            scanf("%s", cliente.dependentes[i].cpf);

            if (strlen(cliente.dependentes[i].cpf) != 11)
            {
                printf(AMARELO "CPF invalido! Digite 11 numeros.\n" RESET);
                cpfInvalido = 1;
            }

            if (strcmp(cliente.dependentes[i].cpf, cliente.cpf) == 0)
            {
                printf(VERMELHO "O dependente nao pode ter o mesmo CPF do titular!\n" RESET);
                cpfInvalido = 1;
            }

            if (cpfJaCadastrado(cliente.dependentes[i].cpf))
            {
                printf(VERMELHO "CPF ja cadastrado no sistema!\n" RESET);
                cpfInvalido = 1;
            }

            for (int j = 0; j < i; j++)
            {
                if (strcmp(cliente.dependentes[i].cpf,
                           cliente.dependentes[j].cpf) == 0)
                {
                    printf(VERMELHO "CPF de dependente ja informado!\n" RESET);
                    cpfInvalido = 1;
                    break;
                }
            }

        } while (cpfInvalido);

        printf("Nome: ");
        scanf(" %s", cliente.dependentes[i].nome);

        do
        {
            printf("Data de nascimento (DDMMAAAA): ");
            scanf("%s", cliente.dependentes[i].dataNascimento);

            if (!validarData(cliente.dependentes[i].dataNascimento))
            {
                printf(AMARELO "Data invalida!\n" RESET);
            }

        } while (!validarData(cliente.dependentes[i].dataNascimento));

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

    printf(AMARELO "\nCliente nao cadastrado!\n" RESET);
    printf("Pressione ENTER para tentar novamente...");
    getchar();
    getchar();

    system("cls");

    fclose(dados);
    return -1;
}

void listarClientes()
{

    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "         LISTAGEM GERAL              \n" RESET);
    printf(CIANO "====================================\n\n" RESET);

    Cliente cliente;

    FILE *dados = fopen(DADOS, "rb");

    printf(CIANO "===============================================================================================================================================\n" RESET);
    printf(CIANO "%-12s %-25s %-8s %-15s %-20s %-6s %-12s %-5s %-10s %-10s\n" RESET,
           "CPF", "NOME", "SEXO", "TELEFONE", "EMAIL",
           "IDADE", "PLANO", "DEP", "VALOR", "VENC.");

    printf(CIANO "====================================================================================================================================================\n" RESET);

    while (fread(&cliente, sizeof(Cliente), 1, dados))
    {
        char sexo[10];
        char plano[15];

        strcpy(sexo, cliente.sexo == 1 ? "Fem." : "Masc.");

        switch (cliente.plano)
        {
        case 1:
            strcpy(plano, "Ouro");
            break;
        case 2:
            strcpy(plano, "Diamante");
            break;
        case 3:
            strcpy(plano, "Prata");
            break;
        case 4:
            strcpy(plano, "Esmeralda");
            break;
        }

        printf("%-12s %-25s %-8s %-15s %-20s %-6d %-12s %-5d R$%-8.2f %-10s\n",
               cliente.cpf,
               cliente.nome,
               sexo,
               cliente.telefone,
               cliente.email,
               cliente.idade,
               plano,
               cliente.qtdDependentes,
               cliente.valorPlano,
               cliente.vencimentoPlano);
    }
    printf(CIANO "=====================================================================================================================================================\n" RESET);

    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    getchar();

    fclose(dados);

    system("cls");
}

void editarCliente()
{
    printf(CIANO "\n====================================\n" RESET);
    printf(CIANO "         Editar cliente              \n" RESET);
    printf(CIANO "====================================\n\n" RESET);

    char cpf[11];

    printf("Digite 0 para sair.\n");
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    if (strcmp(cpf, "0") == 0)
    {
        system("cls");
        return;
    }

    int pos = buscarCPF(cpf);

    if (pos == -1)
    {
        editarCliente();
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
    printf(CIANO "      ESCOLHA O DADO A ALTERAR     \n" RESET);
    printf(CIANO "====================================\n\n" RESET);
    printf("1 - Nome\n");
    printf("2 - Idade\n");
    printf("3 - Email\n");
    printf("4 - Telefone\n");
    printf("5 - Sexo\n");
    printf("6 - Plano\n");
    printf("7 - Quantidade de Dependentes\n");
    printf("8 - Vencimento\n");
    printf("9 - CPF\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &op);

    system("cls");

    switch (op)
    {
    case 1:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "          ALTERAR NOME             \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        printf("Novo nome: ");
        scanf(" %[^\n]", cliente.nome);

        system("cls");
        break;

    case 2:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "         ALTERAR IDADE             \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        do
        {
            printf("Nova idade: ");
            scanf("%d", &cliente.idade);

            if (cliente.idade < 1 || cliente.idade > 120)
            {
                printf(AMARELO "Idade invalida!\n" RESET);
            }

        } while (cliente.idade < 1 || cliente.idade > 120);

        cliente.valorPlano = calcularPlano(cliente);

        system("cls");
        break;

    case 3:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "         ALTERAR EMAIL             \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        printf("Novo email: ");
        scanf("%s", cliente.email);

        system("cls");
        break;

    case 4:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "       ALTERAR TELEFONE            \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        printf("Novo telefone: ");
        scanf("%s", cliente.telefone);

        system("cls");
        break;

    case 5:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "         ALTERAR SEXO              \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        do
        {
            printf("1 - Feminino\n");
            printf("2 - Masculino\n");
            printf("Novo sexo: ");
            scanf("%d", &cliente.sexo);

            if (cliente.sexo < 1 || cliente.sexo > 2)
            {
                printf(AMARELO "Opcao invalida!\n" RESET);
            }

        } while (cliente.sexo < 1 || cliente.sexo > 2);

        cliente.valorPlano = calcularPlano(cliente);

        break;

    case 6:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "        ALTERAR PLANO             \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        do
        {
            printf("1 - Ouro\n");
            printf("2 - Diamante\n");
            printf("3 - Prata\n");
            printf("4 - Esmeralda\n");

            printf("Novo plano: ");
            scanf("%d", &cliente.plano);

            if (cliente.plano < 1 || cliente.plano > 4)
            {
                printf(AMARELO "Plano invalido!\n" RESET);
            }

        } while (cliente.plano < 1 || cliente.plano > 4);

        cliente.valorPlano = calcularPlano(cliente);

        break;

    case 7:
    {
        int opDependente;

        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "      GERENCIAR DEPENDENTES        \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        printf("1 - Adicionar dependente\n");
        printf("2 - Remover dependente\n");
        printf("3 - Editar dependente\n");
        printf("0 - Voltar\n");

        printf("\nOpcao: ");
        scanf("%d", &opDependente);

        switch (opDependente)
        {
        case 1:
        {
            int i = cliente.qtdDependentes;

            if (cliente.qtdDependentes >= 10)
            {
                printf(AMARELO "Limite de dependentes atingido!\n" RESET);
                break;
            }

            printf("\nCPF: ");
            scanf("%s", cliente.dependentes[i].cpf);

            getchar();

            printf("Nome: ");
            fgets(cliente.dependentes[i].nome, sizeof(cliente.dependentes[i].nome), stdin);

            cliente.dependentes[i].nome[strcspn(cliente.dependentes[i].nome, "\n")] = '\0';

            printf("idade: ");
            scanf("%s", cliente.dependentes[i].dataNascimento);

            do
            {
                printf("Sexo (1-Feminino / 2-Masculino): ");
                scanf("%d", &cliente.sexo);

                if (cliente.sexo != 1 && cliente.sexo != 2)
                {
                    printf(AMARELO "Opcao invalida! Digite 1 ou 2.\n" RESET);
                }
            } while (cliente.sexo != 1 && cliente.sexo != 2);

            cliente.qtdDependentes++;

            cliente.valorPlano = calcularPlano(cliente);

            printf(VERDE "\nDependente adicionado com sucesso!\n" RESET);

            break;
        }

        case 2:
        {
            if (cliente.qtdDependentes == 0)
            {
                printf(AMARELO "\nNao existem dependentes cadastrados!\n" RESET);
                break;
            }

            printf("\nDEPENDENTES:\n\n");

            for (int i = 0; i < cliente.qtdDependentes; i++)
            {
                printf("%d - %s\n", i + 1, cliente.dependentes[i].nome);
            }

            int indice;

            printf("0 - Sair\n");
            printf("\nDependente para remover: ");
            scanf("%d", &indice);

            if (indice == 0)
            {
                system("cls");
                return;
            }

            indice--;

            if (indice < 0 || indice >= cliente.qtdDependentes)
            {
                printf(VERMELHO "Dependente invalido!\n" RESET);
                break;
            }

            for (int i = indice; i < cliente.qtdDependentes - 1; i++)
            {
                cliente.dependentes[i] = cliente.dependentes[i + 1];
            }

            cliente.qtdDependentes--;

            cliente.valorPlano = calcularPlano(cliente);

            printf(VERDE "\nDependente removido com sucesso!\n" RESET);

            break;
        }

        case 3:
        {
            if (cliente.qtdDependentes == 0)
            {
                printf(AMARELO "\nNao existem dependentes cadastrados!\n" RESET);
                break;
            }

            printf("Digite 0 para sair!");
            printf("\nDEPENDENTES:\n\n");

            for (int i = 0; i < cliente.qtdDependentes; i++)
            {
                printf("%d - %s\n", i + 1, cliente.dependentes[i].nome);
            }

            int indice;

            if (indice == 0)
            {
                system("cls");
                return;
            }

            printf("\nDependente para editar: ");
            scanf("%d", &indice);

            indice--;

            if (indice < 0 || indice >= cliente.qtdDependentes)
            {
                printf(VERMELHO "Dependente invalido!\n" RESET);
                break;
            }

            getchar();

            printf("Novo nome: ");
            fgets(cliente.dependentes[indice].nome, sizeof(cliente.dependentes[indice].nome), stdin);

            cliente.dependentes[indice].nome[strcspn(cliente.dependentes[indice].nome, "\n")] = '\0';

            printf("Novo CPF: ");
            scanf("%s", cliente.dependentes[indice].cpf);

            printf("Nova data de nascimento: ");
            scanf("%s", cliente.dependentes[indice].dataNascimento);

            do
            {
                printf("Novo Sexo (1-Feminino / 2-Masculino): ");
                scanf("%d", &cliente.sexo);

                if (cliente.sexo != 1 && cliente.sexo != 2)
                {
                    printf(AMARELO "Opcao invalida! Digite 1 ou 2.\n" RESET);
                }
            } while (cliente.sexo != 1 && cliente.sexo != 2);

            printf(VERDE "\nDependente atualizado com sucesso!\n" RESET);

            break;
        }

        case 0:
            break;

        default:
            printf(AMARELO "Opcao invalida!\n" RESET);
        }

        break;
    }
    case 8:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "      ALTERAR VENCIMENTO          \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        do
        {
            printf("Novo vencimento (DDMMAAAA): ");
            scanf("%s", cliente.vencimentoPlano);

            if (!validarData(cliente.vencimentoPlano))
            {
                printf(AMARELO "Data invalida!\n" RESET);
            }

        } while (!validarData(cliente.vencimentoPlano));

        break;

    case 9:
        printf(CIANO "\n====================================\n" RESET);
        printf(CIANO "             ALTERAR CPF              \n" RESET);
        printf(CIANO "====================================\n\n" RESET);

        getchar();

        printf("Novo CPF: ");
        fgets(cliente.cpf, sizeof(cliente.cpf), stdin);

        cliente.cpf[strcspn(cliente.cpf, "\n")] = '\0';

        break;

    case 0:
        printf("\nEncerrando sistema...\n");

        system("cls");
        break;

    default:
        printf(AMARELO "Opcao invalida!\n" RESET);
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

    char cpf[12];

    printf("Digite 0 para sair.\n");
    printf("Digite o CPF do cliente que deseja remover: ");
    scanf("%s", cpf);

    if (strcmp(cpf, "0") == 0)
    {
        system("cls");
        return;
    }

    if (buscarCPF(cpf) == -1)
    {
        removerCliente();
        return;
    }

    system("cls");

    if (buscarCPF(cpf) == -1)
    {
        printf(AMARELO "Cliente nao encontrado!\n" RESET);
        return;
    }

    FILE *dados = fopen(DADOS, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (dados == NULL || temp == NULL)
    {
        printf(VERMELHO "Erro ao abrir arquivo!\n" RESET);
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

    printf(VERDE "\nCliente removido com sucesso!\n" RESET);

    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    getchar();

    system("cls");
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
    printf("\n4 - Esmeralda");
    printf("\n0 - Sair\n");

    do
    {

        printf("\nEscolha: ");
        scanf("%d", &plano);

        if (plano == 0)
        {
            system("cls");
            return;
            break;
        }

        if (plano < 1 || plano > 4)
        {
            printf(AMARELO "Opcao invalida! Digite de 1 a 4.\n" RESET);
        }

    } while (plano < 0 || plano > 4);

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
    {
        printf(AMARELO "\nNenhum cliente encontrado.\n" RESET);
    }

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

void boasVindas()
{
    printf(CIANO);
    printf("************************************************************\n");
    printf("*                                                          *\n");
    printf("*                 SEJA BEM-VINDO(A)                        *\n");
    printf("*              SISTEMA NUCLEO SAUDE                        *\n");
    printf("*                                                          *\n");
    printf("************************************************************\n");
    printf(RESET);

    printf("\nPressione ENTER para continuar...");
    getchar();
}

int main()
{
    boasVindas();
    system("cls");

    menu();
    return 0;
}