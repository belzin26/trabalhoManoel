#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int codigo;
    char nome[30];
    char cpf[20];
    char telefone[20];
    char endereco[100];
    char email[100];
} Cliente;

void cadastroCliente();
void confereDadosCliente(Cliente c);

void editaCliente();
void consultaCliente();
void excluiCliente();

void gravaClienteTXT(Cliente c);
void gravaClienteBIN(Cliente c);

#endif
