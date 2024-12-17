#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "peca.h"
#ifndef CONFIG_H
#define CONFIG_H

#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

extern int tipoArquivo;

void carregarConfiguracoes();

#endif


/*Exclui peça informada do arquivo, podendo ser ele extensão .txt ou .bin*/
void excluiPeca() {
    int codigoBusca, encontrado = 0, result;
    Peca pecaAtual;
    FILE *arq, *temp;
    char conf[10];
    char arquivo[10] = "TEXTO";
    char excluir[5];

    printf("\nDigite o código da peça que deseja excluir: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosPecas.txt", "r");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo texto.\n");
            return;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                    &pecaAtual.codigo, pecaAtual.descricao,
                    pecaAtual.fabricante, pecaAtual.fornecedor,
                    &pecaAtual.preco_custo, &pecaAtual.preco_venda,
                    &pecaAtual.quantidade_estoque, &pecaAtual.estoque_minimo) != EOF) {
            if (pecaAtual.codigo == codigoBusca) {
                encontrado = 1;
                printf("\n----- PEÇA ENCONTRADA -----\n");
                printf("Código: %d\n", pecaAtual.codigo);
                printf("Descrição: %s\n", pecaAtual.descricao);
                printf("Fabricante: %s\n", pecaAtual.fabricante);
                printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                printf("--------------------------------------------------------\n");
                printf("\nOs dados acima se referem a peça que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "S") == 0 || strcmp(excluir, "s") == 0){
                    continue;
                }else{
                    excluiPeca();
                }

            }
            if(encontrado){
                fprintf(temp, "%d;%s;%s;%s;%f;%f;%d;%d\n",
                    pecaAtual.codigo - 1, pecaAtual.descricao,
                    pecaAtual.fabricante, pecaAtual.fornecedor,
                    pecaAtual.preco_custo, pecaAtual.preco_venda,
                    pecaAtual.quantidade_estoque, pecaAtual.estoque_minimo);
            }else{
                fprintf(temp, "%d;%s;%s;%s;%f;%f;%d;%d\n",
                    pecaAtual.codigo, pecaAtual.descricao,
                    pecaAtual.fabricante, pecaAtual.fornecedor,
                    pecaAtual.preco_custo, pecaAtual.preco_venda,
                    pecaAtual.quantidade_estoque, pecaAtual.estoque_minimo);
            }
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosPecas.txt");
            rename("temp.txt", "dadosPecas.txt");
            printf("\nPeça excluída com sucesso!\n");
        } else {
            printf("\nPeça não encontrada.\n");
            remove("temp.txt");
        }
    } else if (tipoArquivo == FORMATO_BINARIO) {
        arq = fopen("dadosPecas.bin", "rb");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo binário.\n");
            return;
        }
        temp = fopen("temp.bin", "wb");
        if (temp == NULL) {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        while (fread(&pecaAtual, sizeof(Peca), 1, arq)) {
            if (pecaAtual.codigo == codigoBusca) {
                encontrado = 1;
                continue; // Ignora a gravação no arquivo temporário
            }
            fwrite(&pecaAtual, sizeof(Peca), 1, temp);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosPecas.bin");
            rename("temp.bin", "dadosPecas.bin");
            printf("\nPeça excluída com sucesso!\n");
        } else {
            printf("\nPeça não encontrada.\n");
            remove("temp.bin");
        }
    }
}

/*Edita uma peça específica do arquivo de extensão .txt ou .bin*/
void editaPeca() {
    int result, encontrado, codigoBusca;
    FILE *arq, *temp; 
    char conf[10];
    char arquivo[10] = "TEXTO";
    char confere[2];
    Peca pecaAtual;

    printf("\nDigite o código da peça que deseja editar: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO) { // TEXTO
        printf("Configuração atual: TEXTO\n\n");
        arq = fopen("dadosPecas.txt", "r");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo texto. Certifique-se de que o arquivo existe.\n");
            return;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                    &pecaAtual.codigo, pecaAtual.descricao,
                    pecaAtual.fabricante, pecaAtual.fornecedor,
                    &pecaAtual.preco_custo, &pecaAtual.preco_venda,
                    &pecaAtual.quantidade_estoque, &pecaAtual.estoque_minimo) != EOF) {
            if (pecaAtual.codigo == codigoBusca) {
                encontrado = 1;
                printf("\nDigite os novos dados para a peça:\n");
                printf("Descrição: ");
                scanf(" %[^\n]", pecaAtual.descricao);
                printf("Fabricante: ");
                scanf(" %[^\n]", pecaAtual.fabricante);
                printf("Fornecedor: ");
                scanf(" %[^\n]", pecaAtual.fornecedor);
                printf("Preço de custo: ");
                scanf("%f", &pecaAtual.preco_custo);
                printf("Preço de venda: ");
                scanf("%f", &pecaAtual.preco_venda);
                printf("Quantidade em estoque: ");
                scanf("%d", &pecaAtual.quantidade_estoque);
                printf("Estoque mínimo: ");
                scanf("%d", &pecaAtual.estoque_minimo);
            }
            fprintf(temp, "%d;%s;%s;%s;%f;%f;%d;%d\n",
                    pecaAtual.codigo, pecaAtual.descricao,
                    pecaAtual.fabricante, pecaAtual.fornecedor,
                    pecaAtual.preco_custo, pecaAtual.preco_venda,
                    pecaAtual.quantidade_estoque, pecaAtual.estoque_minimo);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosPecas.txt");
            rename("temp.txt", "dadosPecas.txt");
            printf("\nPeça editada com sucesso!\n");
        } else {
            printf("\nPeça não encontrada.\n");
            remove("temp.txt");
        }

    } else if (tipoArquivo == FORMATO_BINARIO) { // BINÁRIO
        printf("Configuração atual: BINÁRIO\n\n");
        arq = fopen("dadosPecas.bin", "rb");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo binário.\n");
            return;
        }
        temp = fopen("temp.bin", "wb");
        if (temp == NULL) {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        while (fread(&pecaAtual, sizeof(Peca), 1, arq)) {
            if (pecaAtual.codigo == codigoBusca) {
                encontrado = 1;
                printf("\nDigite os novos dados para a peça:\n");
                printf("Descrição: ");
                scanf(" %[^\n]", pecaAtual.descricao);
                printf("Fabricante: ");
                scanf(" %[^\n]", pecaAtual.fabricante);
                printf("Fornecedor: ");
                scanf(" %[^\n]", pecaAtual.fornecedor);
                printf("Preço de custo: ");
                scanf("%f", &pecaAtual.preco_custo);
                printf("Preço de venda: ");
                scanf("%f", &pecaAtual.preco_venda);
                printf("Quantidade em estoque: ");
                scanf("%d", &pecaAtual.quantidade_estoque);
                printf("Estoque mínimo: ");
                scanf("%d", &pecaAtual.estoque_minimo);
            }
            fwrite(&pecaAtual, sizeof(Peca), 1, temp);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosPecas.bin");
            rename("temp.bin", "dadosPecas.bin");
            printf("\nPeça editada com sucesso!\n");
        } else {
            printf("\nPeça não encontrada.\n");
            remove("temp.bin");
        }
    }
}

/*Confere se os dados informados confere. Conferência pré-salvamento.
Têm como parâmetro uma struct do tipo Peca.*/
void confereDadosPeca(Peca p){
    system("clear");
    char confere[2];
    
    FILE *arq;
    int result;

    char conf[10];
    char arquivo[10] = "TEXTO";

    printf("----- DADOS INFORMADOS -----");
    printf("\n\nCódigo: %d", p.codigo);
    printf("\nDescrição: %s", p.descricao);
    printf("\nFabricante: %s", p.fabricante);
    printf("\nFornecedor: %s", p.fornecedor);
    printf("\nPreço de custo: %.2f", p.preco_custo);
    printf("\nPreço de venda: %.2f", p.preco_venda);
    printf("\nQuantidade estoque: %d", p.quantidade_estoque);
    printf("\nEstoque mínimo: %d", p.estoque_minimo);

    printf("\n\nOs dados acima conferem? (S/N)\n");
    scanf("%s", confere);

    if ((strcmp(confere, "S") == 0) || (strcmp(confere, "s") == 0) || (strcmp(confere, "\n") == 0)){
        system("clear");
        if (tipoArquivo == FORMATO_TEXTO){
            gravaPecaTXT(p);
        }else if (tipoArquivo == FORMATO_BINARIO){
            gravaPecaBIN(p);
        }else{
            system("clear");
            printf("\nTipo de arquivo inválido.");
            system("clear");
            printf("----- SESSÃO ENCERRADA -----");
            printf("\n");
        }
    }
}

/*Inicia o questionário de preenchimento de dados para cadastro de uma nova Peça no sistema.*/
void cadastroPeca(){
    Peca p;
    FILE *arq;
    int codigo;
    codigo = 0;

    if (tipoArquivo == FORMATO_TEXTO){
        arq = fopen("dadosPecas.txt", "r");
        if (arq == NULL){
            arq = fopen("dadosPecas.txt", "w");
            fclose(arq);
            arq = fopen("dadosPecas.txt", "r");
        }
        while(fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                    &p.codigo, p.descricao,
                    p.fabricante, p.fornecedor,
                    &p.preco_custo, &p.preco_venda,
                    &p.quantidade_estoque, &p.estoque_minimo) != EOF){
            codigo += 1;
        }
    }else if(tipoArquivo == FORMATO_BINARIO){
        arq = fopen("dadosPecas.bin", "rb");
        if (arq == NULL){
            arq = fopen("dadosPecas.bin", "wb");
            fclose(arq);
            arq = fopen("dadosPecas.bin", "rb");
        }
        while(fread(&p, sizeof(Peca), 1, arq) == 1){
                    codigo += 1;
        }
    }
    fclose(arq);

    system("clear");
    printf("----- CADASTRO PEÇA -----");
    
    printf("\nInforme a descrição: ");
    scanf(" %[^\n]", p.descricao);
    printf("Informe o fabricante: ");
    scanf(" %[^\n]", p.fabricante);
    printf("Informe o fornecedor: ");
    scanf(" %[^\n]", p.fornecedor);
    printf("Preço de custo: ");
    scanf("%f", &p.preco_custo);
    printf("Quantidade em estoque: ");
    scanf("%d", &p.quantidade_estoque);
    printf("Estoque mínimo: ");
    scanf("%d", &p.estoque_minimo);

    p.codigo = codigo;
    p.preco_venda = p.preco_custo + (p.preco_custo * 20/100);

    confereDadosPeca(p);
}

/*Função destinada ao gravamento de peças em arquivo de extensão .txt*/
void gravaPecaTXT(Peca p){
    FILE *arq;
    int result;

    arq = fopen("dadosPecas.txt", "r");
    if (arq == NULL){ // Criando arquivo caso não exista
        arq = fopen("dadosPecas.txt", "w");
    }
    fclose(arq);
    arq = fopen("dadosPecas.txt", "a");
    result = fprintf(arq, "%d;%s;%s;%s;%f;%f;%d;%d\n", p.codigo, p.descricao, p.fabricante, p.fornecedor, p.preco_custo, p.preco_venda, p.quantidade_estoque, p.estoque_minimo);
    system("clear");
    printf("\nSalvando dados... ");
    if (result == 0){
        printf("Erro na escrita do arquivo.");
        exit(1);
    }else{
        printf("Dados gravados com sucesso!\n");
    }
    fclose(arq);
}

/*Função destinada ao gravamento de peças em arquivo de extensão .bin
Têm como parâmetro uma struct p do tipo Peca*/
void gravaPecaBIN(Peca p){
    FILE *arq;

    arq = fopen("dadosPecas.bin", "ab+");
    if (arq == NULL) {
        system("clear");
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    int result = fwrite(&p, sizeof(Peca), 1, arq);
    system("clear");
    printf("Salvando dados... ");
    if (result == 0) {
        printf("Erro na escrita do arquivo.\n");
    } else {
        printf("Dados salvos com sucesso!\n");
    }
    fclose(arq);
}

/*Função destinada a consulta de determinada(s) peças referente à um filtro de busca.*/
void consultaPeca() {
    int escolha;
    Peca pecaAtual;
    int codigoBusca;
    char novaConsulta[5];
    char buscaDescricao[30];
    char buscaFornecedor[100];
    char buscaFabricante[100];
    int encontrado = 0, result;

    FILE *arq;
    char confere[2];

    printf("----- CONSULTA PEÇA -----");
    printf("\n\nOPÇÕES");
    printf("\n1 - Código");
    printf("\n2 - Descrição");
    printf("\n3 - Fornecedor");
    printf("\n4 - Fabricante");
    printf("\n5 - VISUALIZAR TODAS AS PEÇAS CADASTRADAS");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);
    system("clear");

    if (tipoArquivo == FORMATO_TEXTO) {
        // Abrir arquivo texto
        printf("Configuração atual: TEXTO\n\n");
        arq = fopen("dadosPecas.txt", "r");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo TEXTO. Certifique-se que o arquivo exista.\n");
            fclose(arq);
            return;
        }
        encontrado = 0;
        switch (escolha) {
            case 1: // Busca por código
                printf("\nDigite o código da peça: ");
                scanf("%d", &codigoBusca);
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                            &pecaAtual.codigo, pecaAtual.descricao,
                            pecaAtual.fabricante, pecaAtual.fornecedor,
                            &pecaAtual.preco_custo, &pecaAtual.preco_venda,
                            &pecaAtual.quantidade_estoque, &pecaAtual.estoque_minimo) != EOF) {
                    if (pecaAtual.codigo == codigoBusca) {
                        encontrado == 1;
                        printf("\n----- PEÇA ENCONTRADA -----\n");
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("--------------------------------------------------------\n");
                        break;
                    }
                }
                if (!encontrado) {
                    printf("\nPeça não encontrada.\n");
                }else{
                    encontrado = 0;
                }
                break;

            case 2: // Busca pela descrição da peça
                printf("\nDigite a descrição da peça: ");
                scanf("%s", buscaDescricao);
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                        &pecaAtual.codigo, pecaAtual.descricao,
                        pecaAtual.fabricante, pecaAtual.fornecedor,
                        &pecaAtual.preco_custo, &pecaAtual.preco_venda,
                        &pecaAtual.quantidade_estoque, &pecaAtual.estoque_minimo) != EOF) {

                    if (strcmp(pecaAtual.descricao, buscaDescricao) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- PEÇAS ENCONTRADAS -----\n");
                        }
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("--------------------------------------------------------\n");
                    }
                }
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;
            
            case 3:
                printf("\nInforme o fornecedor: ");
                scanf(" %[^\n]", buscaFornecedor);
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                            &pecaAtual.codigo, pecaAtual.descricao,
                            pecaAtual.fabricante, pecaAtual.fornecedor,
                            &pecaAtual.preco_custo, &pecaAtual.preco_venda,
                            &pecaAtual.quantidade_estoque, &pecaAtual.estoque_minimo) != EOF) {

                    if (strcmp(pecaAtual.fornecedor, buscaFornecedor) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- PEÇAS ENCONTRADAS -----\n");
                        }
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;

            case 4:
                printf("\nInforme o fabricante: ");
                scanf(" %[^\n]", buscaFabricante);
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                            &pecaAtual.codigo, pecaAtual.descricao,
                            pecaAtual.fabricante, pecaAtual.fornecedor,
                            &pecaAtual.preco_custo, &pecaAtual.preco_venda,
                            &pecaAtual.quantidade_estoque, &pecaAtual.estoque_minimo) != EOF) {

                    if (strcmp(pecaAtual.fabricante, buscaFabricante) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- PEÇAS ENCONTRADAS -----\n");
                        }
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;
            
            case 5: // Mostra toda a lista de todas as peças cadastradas no sistema
                printf("\t\t----- LISTA DE PEÇAS -----\n");
                printf("\n");
                encontrado = 0;
                while(fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                            &pecaAtual.codigo, pecaAtual.descricao,
                            pecaAtual.fabricante, pecaAtual.fornecedor,
                            &pecaAtual.preco_custo, &pecaAtual.preco_venda,
                            &pecaAtual.quantidade_estoque, &pecaAtual.estoque_minimo) != EOF){
                    printf("Código: %d\n", pecaAtual.codigo);
                    printf("Descrição: %s\n", pecaAtual.descricao);
                    printf("Fabricante: %s\n", pecaAtual.fabricante);
                    printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                    printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                    printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                    printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                    printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                    printf("\n--------------------------------------------------------\n");
                    encontrado += 1;
                }
                printf("Número total de peças cadastradas no sistema: %d", encontrado);
                printf("\n");
                break;

            default:
                printf("\nOpção inválida.\n");
                fclose(arq);
                consultaPeca();
                return;
        }
        fclose(arq); // Fechar o arquivo texto
        printf("\n--------------------------------------------------------");
        printf("\nDeseja realizar uma nova busca? (S/N)");
        scanf(" %[^\n]", novaConsulta);

        if (strcmp(novaConsulta, "s") == 0 || strcmp(novaConsulta, "S") == 0){
            system("clear");
            consultaPeca();
        }else{
            system("clear");
        }
        return;

    } else if (tipoArquivo == FORMATO_BINARIO) {
        // Abrir arquivo binário
        printf("Configuração atual: BINÁRIO\n\n");
        arq = fopen("dadosClientes.bin", "rb");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo BINÁRIO. Certifique-se que o arquivo exista.");
            fclose(arq);
            return;
        }

        switch (escolha) {
            case 1: // Busca por código
                printf("\nDigite o código da peça: ");
                scanf("%d", &codigoBusca);
                encontrado == 0;
                while (fread(&pecaAtual, sizeof(Peca), 1, arq) == 1) {
                    if (pecaAtual.codigo == codigoBusca) {
                        system("clear");

                        printf("\n----- PEÇA ENCONTRADA -----\n");
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("\n--------------------------------------------------------\n");
                        break;
                    }
                }
                if (encontrado == 0){
                    printf("\nPeça não encontrada.");
                }
                break;

            case 2: // Busca por descrição
                printf("\nDigite a descrição da peça: ");
                scanf("%s", buscaDescricao);
                encontrado = 0;
                while (fread(&pecaAtual, sizeof(Peca), 1, arq) == 1) {
                    if (strcmp(pecaAtual.descricao, buscaDescricao) == 0) {
                        system("clear");
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- PEÇAS ENCONTRADAS -----\n\n");
                        }
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("\n--------------------------------------------------------\n");
                    }
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                encontrado = 0;
                break;
            
            case 3:
                printf("\nInforme o fornecedor: ");
                scanf("%s", buscaFornecedor);
                encontrado = 0;
                while(fread(&pecaAtual, sizeof(Peca), 1, arq) == 1){
                    if (strcmp(pecaAtual.fornecedor, buscaFornecedor) == 0){
                        system("clear");
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("----- PEÇAS ENCONTRADAS -----");
                        }
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                encontrado = 0;
                break;

            case 4:
                printf("\nInforme o fabricante: ");
                scanf("%s", buscaFabricante);
                encontrado = 0;
                while (fread(&pecaAtual, sizeof(Peca), 1, arq) == 1){
                    if (strcmp(pecaAtual.fabricante, buscaFabricante) == 0){
                        system("clear");
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- PEÇAS ENCONTRADAS -----\n");
                        }
                        printf("Código: %d\n", pecaAtual.codigo);
                        printf("Descrição: %s\n", pecaAtual.descricao);
                        printf("Fabricante: %s\n", pecaAtual.fabricante);
                        printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                        printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                        printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                        printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                        printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                encontrado = 0;
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;
            
            case 5: // Mostra toda a lista de peças cadastrados no sistema
                printf("\t\t----- LISTA DE PECAS -----\n");
                printf("\n");
                encontrado = 0;
                while(fread(&pecaAtual, sizeof(Peca), 1, arq) == 1){
                    encontrado += 1;
                    printf("Código: %d\n", pecaAtual.codigo);
                    printf("Descrição: %s\n", pecaAtual.descricao);
                    printf("Fabricante: %s\n", pecaAtual.fabricante);
                    printf("Fornecedor: %s\n", pecaAtual.fornecedor);
                    printf("Preço de custo: %.2f\n", pecaAtual.preco_custo);
                    printf("Preço de venda: %.2f\n", pecaAtual.preco_venda);
                    printf("Quantidade em estoque: %d\n", pecaAtual.quantidade_estoque);
                    printf("Estoque mínimo: %d\n", pecaAtual.estoque_minimo);
                    printf("--------------------------------------------------------\n");
                }
                printf("Número total de peças cadastrados no sistema: %d", encontrado);
                printf("\n");
                break;

            default:
                printf("\nOpção inválida.\n");
                fclose(arq);
                return;
        }
        return;
        fclose(arq); // Fechar o arquivo binário

    } else {
        printf("\nTipo de arquivo inválido nas configurações.\n");
        exit(1);
    }
    
    printf("\nDeseja fazer uma outra busca? (S/N) ");
    scanf("%s", confere);
    if (strcmp(confere, "S") == 0 || strcmp(confere, "s") == 0){
        system("clear");
        consultaPeca();
    }else{
        system("clear");
    }
}