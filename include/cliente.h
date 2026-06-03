#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct
{
    char nome[100];
    char cpf[15];
    int idade;
    int sexo;
    int plano;
    float valorPlano;

} Cliente;

void cadastrarCliente();

int buscarCPF();

void listarClientes();

void editarCliente();

void removerCliente();

float calcularPlano();

void mostrarRelatorios();

#endif