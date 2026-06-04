#include <stdio.h>

typedef struct
{
    int mat;
    char nome[20];
    float med;
} TAluno;

FILE *paluno;

TAluno aluno_aux, aluno_nulo;

void linha()
{
    int i;
    for (i = 1; i <= 40; i++)
        printf("_");
}
void cabec()
{
    linha();
    printf(" FACULDADE SENAC ");
    linha();
}
void abre_arquivo()
{
    paluno = fopen("aluno.txt", "r+b");
    if (paluno == NULL)
        paluno = fopen("aluno.txt", "w+b");
}
void inserir()
{
    int resp;
    do
    {
        cabec();
        printf("\n\nCadastrar novo aluno\n\n");
        printf("\nMatricula: ");
        scanf("%d", &aluno_aux.mat);
        printf("\nNome.....: ");

        scanf("%s", &aluno_aux.nome);
        printf("\nMedia....: ");
        scanf("%f", &aluno_aux.med);
        fseek(paluno, 0, SEEK_END);
        fwrite(&aluno_aux, sizeof(TAluno), 1, paluno);
        printf("\n\nAluno cadastrado com sucesso!\n\n");
        printf("\nDeseja cadastrar outro: (1-sim/0-nao)? ");
        scanf("%d", &resp);
    } while (resp == 1);
}
int procura(int matp)
{
    int p;
    p = 0;
    rewind(paluno);
    fread(&aluno_aux, sizeof(TAluno), 1, paluno);
    while (feof(paluno) == 0)
    {
        if (aluno_aux.mat == matp)
            return p;
        else
        {
            fread(&aluno_aux, sizeof(TAluno), 1, paluno);
            p++;
        }
    }
    return -1;
}
void mostre(int pos)
{
    fseek(paluno, pos * sizeof(TAluno), SEEK_SET);
    fread(&aluno_aux, sizeof(TAluno), 1, paluno);
    printf("\n\n");
    linha();
    printf("\nMatricula    Nome    Media\n");
    linha();
    printf("\n%5d %-15s %3.1f\n", aluno_aux.mat, aluno_aux.nome, aluno_aux.med);
    linha();
}
void consultar()
{
    int resp, matcon, posicao;
    do
    {
        cabec();
        printf("\n\nConsultar Aluno\n\n\n");
        printf("Matricula do aluno: ");
        scanf("%d", &matcon);
        posicao = procura(matcon);
        if (posicao == -1)
            printf("\n\nMatricula nao encontrada!\n\n");
        else
            mostre(posicao);
        printf("\n\nDeseja consultar outro (1-sim/0-nao)? ");
        scanf("%d", &resp);
    } while (resp == 1);
}
void remover()
{
    int matrem, conf, resp, posicao;
    aluno_nulo.mat = 0;
    aluno_nulo.med = 0;
    do
    {
        cabec();
        printf("\n\nRemover aluno\n\n\n");
        printf("Matricula: ");
        scanf("%d", &matrem);
        posicao = procura(matrem);
        if (posicao == -1)
            printf("\nAluno nao encontrado!!");
        else
        {
            mostre(posicao);
            printf("\n\nDeseja remover o aluno(1-sim/0-nao)? ");
            scanf("%d", &conf);
            if (conf == 1)
            {
                fseek(paluno, posicao * sizeof(TAluno), SEEK_SET);
                fwrite(&aluno_nulo, sizeof(TAluno), 1, paluno);
                printf("\n\nAluno removido com sucesso!");
            }
            else
                printf("\nRemocao cancelada!");
        }
        printf("\n\n\nDeseja remover outro(1-sim/0-nao)? ");
        scanf("%d", &resp);
    } while (resp == 1);
}
void alterar()
{
    int matalt, conf, resp, posicao;
    do
    {
        cabec();
        printf("\n\nAlterar media do aluno\n\n\n");
        printf("Matricula que deseja alterar a media: ");
        scanf("%d", &matalt);
        posicao = procura(matalt);
        if (posicao == -1)
            printf("\nAluno,nao encontrado!!");
        else
        {
            mostre(posicao);
            printf("\n\nAlterar a media do aluno(1-sim/0-nao)? ");
            scanf("%d", &conf);
            if (conf == 1)
            {
                printf("\nNova media: ");
                scanf("%f", &aluno_aux.med);
                printf("\nMedia alterada com sucesso! \n\n");
                fseek(paluno, posicao * sizeof(TAluno), SEEK_SET);
                fwrite(&aluno_aux, sizeof(TAluno), 1, paluno);
                mostre(posicao);
            }
            else
                printf("\n\nAlteracao cancelada!\n\n");
        }
        printf("\n\nDeseja alterar outro (1-sim/0-nao)? ");
        scanf("%d", &resp);
    } while (resp == 1);
}
void listagem()
{
    cabec();
    printf("\n\nListagem Geral\n\n\n");
    linha();
    printf("\nMatricula    Nome     Media\n");
    linha();
    rewind(paluno);
    fread(&aluno_aux, sizeof(TAluno), 1, paluno);
    while (feof(paluno) == 0)
    {
        if (aluno_aux.mat != 0)
            printf("\n%5d %-15s %3.1f\n", aluno_aux.mat, aluno_aux.nome, aluno_aux.med);
        fread(&aluno_aux, sizeof(TAluno), 1, paluno);
    }
    linha();
    printf("\ntecle enter para voltar ao menu...");
}
int main()
{
    int op;
    abre_arquivo();
    do
    {
        cabec();
        printf("\n\nOpcoes: \n\n\n");
        printf(" 1- Cadastrar novo aluno\n\n");
        printf(" 2- Remover aluno\n\n");
        printf(" 3- Consultar aluno por matricula\n\n");
        printf(" 4- Alterar media do aluno\n\n");
        printf(" 5- Listagem geral\n\n");
        printf(" 0- Sair\n\n");
        linha();
        printf("\nInforme a opcao desejada: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            inserir();
            break;
        case 2:
            remover();
            break;
        case 3:
            consultar();
            break;
        case 4:
            alterar();
            break;
        case 5:
            listagem();
            break;
        case 0:
            fclose(paluno);
            break;
        default:
            printf("\n\n\aOpcao invalida!");
            break;
        }
    } while (op != 0);
    return 0;
}