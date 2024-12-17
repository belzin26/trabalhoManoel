#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oficina.h"

#ifndef CONFIG_H
#define CONFIG_H

// Define os tipos de arquivo possíveis
#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

// Variável global para armazenar o tipo de arquivo
extern int tipoArquivo;

void carregarConfiguracoes();

#endif // CONFIG_H


void confereDadosOficina(Oficina of){
    char confere[5];

    printf("----- CONFERÊNCIA DE DADOS -----");
    printf("\n\nNome: %s", of.nome);
    printf("\nCPF/CNPJ: %s", of.cpf);
    printf("\nEndereço: %s", of.endereco);
    printf("\nE-mail: %s", of.email);
    printf("\nTelefone: %s", of.telefone);
    printf("\nLucro: %.2f", of.lucro);

    printf("\n\nOs dados acima conferem? (S/N) ");
    scanf(" %[^\n]", confere);
    system("clear");
    if (strcmp(confere, "S") == 0 || strcmp(confere, "s") == 0){
        gravaDadosOficina(of);
    }else if(strcmp(confere, "N") == 0 || strcmp(confere, "n") == 0){
        cadastraOficina();
    }else{
        printf("\nOpção inválida. Tente novamente");
        printf("\n");
        confereDadosOficina(of);
    }
}

void gravaDadosOficina(Oficina of){

    int result = 0;
    FILE *arq;

    if (tipoArquivo == FORMATO_TEXTO){
        arq = fopen("dadosOficina.txt", "r");
        if(arq == NULL){
            arq = fopen("dadosOficina.txt", "w");
        }
        fclose(arq);
        arq = fopen("dadosOficina.txt", "w");
        result = fprintf(arq, "%s;%s;%s;%s;%s;%.2f", of.nome, of.cpf, of.endereco, of.telefone, of.email, of.lucro);
        system("clear");
        printf("Salvando dados... ");
        if (result == 0){
            printf("Erro de escrita no arquivo.");
            return;
        }else{
            system("clear");
            printf("Dados salvos com sucesso!\n\n");
        }
    }else if (tipoArquivo == FORMATO_BINARIO){
        arq = fopen("dadosOficina.bin", "wb");
        if (arq == NULL){
            arq = fopen("dadosOficina.bin", "ab+");
        }
        result = fwrite(&of, sizeof(Oficina), 1, arq);
        system("clear");
        printf("Salvando dados... ");
        if (result == 0){
            printf("Erro de escrita no arquivo.");
            return;
        }else{
            system("clear");
            printf("Dados salvos com sucesso!\n\n");
        }
    fclose(arq);
    return;
    }
}

void editarOficina(){
    FILE *arq;
    Oficina of;

    printf("----- CADASTRO OFICINA -----");
    printf("\n\n");
    printf("Nome da oficina: ");
    scanf(" %[^\n]", of.nome);
    printf("CNPJ: ");
    scanf(" %[^\n]", of.cpf);
    printf("Informe o endereço: ");
    scanf(" %[^\n]", of.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]", of.telefone);
    printf("E-mail: ");
    scanf(" %[^\n]", of.email);
    printf("Lucro: ");
    scanf("%f", &of.lucro);

    system("clear");
    confereDadosOficina(of);
}


void cadastraOficina(){

    int result;
    char editar[5];
    char escrever[5];
    FILE *arq;
    Oficina of;

    if (tipoArquivo == FORMATO_TEXTO){
        arq = fopen("dadosOficina.txt", "r");
        if(arq == NULL){
            printf("----- CADASTRO OFICINA -----");
            printf("\n\n");
            printf("Nome da oficina: ");
            scanf(" %[^\n]", of.nome);
            printf("CNPJ: ");
            scanf(" %[^\n]", of.cpf);
            printf("Informe o endereço: ");
            scanf(" %[^\n]", of.endereco);
            printf("Telefone: ");
            scanf(" %[^\n]", of.telefone);
            printf("E-mail: ");
            scanf(" %[^\n]", of.email);
            printf("Lucro: ");
            scanf("%f", &of.lucro);
            system("clear");
            confereDadosOficina(of);
        }
    }else if(tipoArquivo == FORMATO_BINARIO){
        arq = fopen("dadosOficina.bin", "rb");
        if (arq == NULL){
            arq = fopen("dadosOficina.txt", "r");
            if(arq == NULL){
                arq = fopen("dadosOficina.bin", "wb");

                printf("----- CADASTRO OFICINA -----");
                printf("\n\n");
                printf("Nome da oficina: ");
                scanf(" %[^\n]", of.nome);
                printf("CNPJ: ");
                scanf(" %[^\n]", of.cpf);
                printf("Informe o endereço: ");
                scanf(" %[^\n]", of.endereco);
                printf("Telefone: ");
                scanf(" %[^\n]", of.telefone);
                printf("E-mail: ");
                scanf(" %[^\n]", of.email);
                printf("Lucro: ");
                scanf("%f", &of.lucro);
                
                system("clear");
                confereDadosOficina(of);
            }else{
                system("clear");
                printf("Não foi encontrado o arquivo binário.");
                printf("\nMas encontramos um arquivo texto com os dados da oficina com os seguintes dados:");
                while (fscanf(arq, "%[^;];%[^;];%[^;];%[^;];%[^;];%f", 
                    of.nome, of.cpf, of.endereco, 
                    of.telefone, of.email, &of.lucro) != EOF) {

                        printf("\n\n----- DADOS CADASTRADOS ATUALMENTE -----\n");
                        printf("\nNome: %s", of.nome);
                        printf("\nCPF/CNPJ: %s", of.cpf);
                        printf("\nEndereço: %s", of.endereco);
                        printf("\nTelefone: %s", of.telefone);
                        printf("\nE-mail: %s", of.email);
                        printf("\nPercentual de lucro: %.2f", of.lucro);

                        printf("\n\nDeseja editar os dados acima? (S/N) ");
                        scanf(" %[^\n]", editar);
                        fclose(arq);

                        if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0) {
                            editarOficina();
                        }else if(strcmp(editar, "N") == 0 || strcmp(editar, "n") == 0){
                            printf("\nDeseja escrever os dados informados acima no arquivo binário? (S/N)");
                            scanf(" %[^\n]", escrever);
                            fclose(arq);
                            if (strcmp(escrever, "S") == 0 || strcmp(escrever, "s") == 0){
                                arq = fopen("dadosOficina.bin", "wb");
                                result = fwrite(&of, sizeof(Oficina), 1, arq);
                                    system("clear");
                                    printf("Salvando dados...");
                                if (result){
                                    printf(" Dados salvos com sucesso!\n");
                                }
                                fclose(arq);
                                return;
                            }
                        }else{
                            system("clear");
                            printf("Opção inválida. Tente novamente.\n");
                            return;
                        }
                    }
                    fclose(arq);
                }
        }
    }
    fclose(arq);
    return;
}