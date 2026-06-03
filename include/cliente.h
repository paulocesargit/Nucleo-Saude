#ifndef CLIENTE_H
#define CLIENTE_H

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
    char nome_terceiro [100];
    char cpf_terceiro[15];
    char data_nasci_terceiro[10];

    // Variaveis planos
    int plano;
    float valorPlano;

} Cliente;

void cadastrarCliente();

void cadastro_cliente_terceiro();

void cadastrar_plano();

int buscarCPF();

void listarClientes();

void editarCliente();

void removerCliente();

float calcularPlano();

void mostrarRelatorios();

#endif