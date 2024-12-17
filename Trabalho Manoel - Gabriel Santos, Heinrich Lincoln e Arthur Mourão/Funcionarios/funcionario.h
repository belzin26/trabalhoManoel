#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct {
    char nome[30];
    char cpf[20];
    char cargo[30];
    float salario;
} Funcionario;

void cadastroFuncionario();
void confereDadosFuncionario(Funcionario f);

void editaFuncionario();
void consultaFuncionario();
void excluiFuncionario();

void gravaFuncionarioTXT(Funcionario f);
void gravaFuncionarioBIN(Funcionario f);

#endif