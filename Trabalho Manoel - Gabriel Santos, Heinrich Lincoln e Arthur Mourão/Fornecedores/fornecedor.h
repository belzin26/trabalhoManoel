#ifndef FORNECEDOR_H
#define FORNECEDOR_H

typedef struct {
    int codigo;
    char nome_fantasia[100];
    char razao_social[100];
    char inscricao_estadual[100];
    char cpf[20];
    char endereco[100];
    char telefone[20];
    char email[30];
} Fornecedor;

void cadastroFornecedor();
void confereDadosFornecedor(Fornecedor f);

void editaFornecedor();
void consultaFornecedor();
void excluiFornecedor();

void gravaFornecedorTXT(Fornecedor f);
void gravaFornecedorBIN(Fornecedor f);

#endif