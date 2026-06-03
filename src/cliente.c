#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cliente.h"

void cadastrarCliente()
{
    Cliente cliente;// variavel cliente para conectar os campos de variaveis e cadastro!

    printf("\n--- CADASTRO CLIENTE ---\n");
    
    printf("\nInforme o nome do cliente: ");
    scanf("%s", cliente.nome_titular);

    printf("\nInforme o CPF do cliente (so os numeros): ");
    scanf("%s", cliente.cpf_titular);

    printf("\nInforme a idade do cliente: \n");
    scanf("%d",&cliente.idade);

    printf("\nInforme o sexo do cliente (1-maculino / 2-feminino): ");
    scanf("%d",&cliente.sexo);

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
    scanf("%f",&planos.valorPlano);

    printf("\nInforme a data de vencimento do plano de saude: ");
    scanf("%d",&planos.plano);

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