#ifndef PECA_H
#define PECA_H

typedef struct {
    int codigo;
    char descricao[100];
    char fabricante[100];
    char fornecedor[100];
    float preco_custo;
    float preco_venda;
    int quantidade_estoque;
    int estoque_minimo;
} Peca;

void cadastroPeca();
void confereDadosPeca(Peca p);
void consultaPeca();
void editaPeca();
void excluiPeca();

void gravaPecaTXT(Peca p);
void gravaPecaBIN(Peca p);

#endif