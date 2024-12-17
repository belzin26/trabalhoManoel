#ifndef OFICINA_H
#define OFICINA_H


typedef struct{
    char nome[100];
    char cpf[20];
    char endereco[100];
    char telefone[20];
    char email[100];
    float lucro;
}Oficina;

void gravaDadosOficina(Oficina of);
void cadastraOficina();
void confereDadosOficina(Oficina of);
void editarOficina();

#endif