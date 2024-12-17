#ifndef SERVICO_H
#define SERVICO_H

typedef struct {
    int codigo;
    char descricao[100];
    float comissao;
    float preco;
} Servico;

void cadastroServico();
void confereDadosServico(Servico s);

void editaServico();
void consultaServico();
void excluiServico();

void gravaServicoTXT(Servico s);
void gravaServicoBIN(Servico s);

#endif