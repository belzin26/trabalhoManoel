#ifndef VEICULO_H
#define VEICULO_H

typedef struct {
    char placa[10];
    char modelo[50];
    char marca[20];
    int ano_fabricacao;
    char chassi[100];
    char cpf[20];
} Veiculo;

void cadastroVeiculo();
void confereDadosVeiculo(Veiculo v);

void editaVeiculo();
void consultaVeiculo();
void excluiVeiculo();

void gravaVeiculoTXT(Veiculo v);
void gravaVeiculoBIN(Veiculo v);


#endif