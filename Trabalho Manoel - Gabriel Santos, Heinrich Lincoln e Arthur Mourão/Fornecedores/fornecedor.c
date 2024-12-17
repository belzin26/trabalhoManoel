#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fornecedor.h"
#ifndef CONFIG_H
#define CONFIG_H

// Define os tipos de arquivo possíveis
#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

// Variável para armazenar o tipo de arquivo
extern int tipoArquivo;

void carregarConfiguracoes();

#endif

//função para cadastrar o fornecedor
void cadastroFornecedor()
{
    Fornecedor f;
    FILE *arq;
    int codigo = 0;

    codigo = 0;
    if (tipoArquivo == FORMATO_TEXTO){
        arq = fopen("dadosFornecedor.txt", "r");
        if (arq == NULL){
            arq = fopen("dadosFornecedor.txt", "w");
            fclose(arq);
            arq = fopen("dadosFornecedor.txt", "r");
        }
        while(fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &f.codigo, f.nome_fantasia,
                        f.razao_social, f.inscricao_estadual,
                        f.cpf, f.endereco,
                        f.telefone, f.email) != EOF){
                    codigo += 1;
        }
    }
    fclose(arq);

    system("clear");
    printf("----- CADASTRO FORNECEDOR -----");

    printf("\nInforme o nome fantasia: ");
    scanf(" %[^\n]", f.nome_fantasia);
    printf("Informe a razão social: ");
    scanf(" %[^\n]", f.razao_social);
    printf("Informe o a inscrição estadual: ");
    scanf(" %[^\n]", f.inscricao_estadual);
    printf("Informe o CNPJ (apenas números): ");
    scanf(" %[^\n]", f.cpf);
    printf("Informe o endereço completo: ");
    scanf(" %[^\n]", f.endereco);
    printf("Informe o telefone: ");
    scanf(" %[^\n]", f.telefone);
    printf("Informe o e-mail: ");
    scanf(" %[^\n]", f.email);

    f.codigo = codigo;

    system("clear");
    confereDadosFornecedor(f);
}

void confereDadosFornecedor(Fornecedor f)
{

    FILE *arq;
    char confere[2];

    system("clear");
    printf("----- CONFERÊNCIA DE DADOS ------");

    printf("\n\nCódigo: %d", f.codigo);
    printf("\nNome: %s", f.nome_fantasia);
    printf("\nRazão Social: %s", f.razao_social);
    printf("\nIncrição Estadual: %s", f.inscricao_estadual);
    printf("\nCPF/CNPJ: %s", f.cpf);
    printf("\nEndereço: %s", f.endereco);
    printf("\nTelefone: %s", f.telefone);
    printf("\nE-mail: %s", f.email);

    printf("\n\nOs dados acima conferem? (S/N)\n");
    scanf("%s", confere);

    if ((strcmp(confere, "S") == 0) || (strcmp(confere, "s") == 0))
    {
        system("clear");
        printf("\nSalvando dados...");
        if (tipoArquivo == FORMATO_TEXTO) // if para mandar os dados pro grava binario ou texto
        {
            gravaFornecedorTXT(f);
        }
        else if (tipoArquivo == FORMATO_BINARIO)
        {
            gravaFornecedorBIN(f);
        }
        else
        {
            system("clear");
            printf("Tipo de arquivo inválido.");
            exit(1);
        }
    }
    else
    {
        cadastroFornecedor();
    }
}

// gravando dados do fornecedor em texto
void gravaFornecedorTXT(Fornecedor f)
{

    system("clear");

    FILE *arq;
    arq = fopen("dadosFornecedor.txt", "r");

    if (arq == NULL)
    {
        arq = fopen("dadosFornecedor.txt", "w");
    }
    fclose(arq);
    arq = fopen("dadosFornecedor.txt", "a");

    int grava = fprintf(arq, "%d;%s;%s;%s;%s;%s;%s;%s\n", f.codigo, f.nome_fantasia, f.razao_social, f.inscricao_estadual, f.cpf, f.endereco, f.telefone, f.email);

    if (grava == 0)
    {
        system("clear");
        printf("\nErro de escrita no arquivo.");
        return;
    }
    else
    {
        printf("\nDADOS DO FORNECEDOR CADASTRADOS COM SUCESSO!!");
        printf("\n");
    }
    fclose(arq);
    return;
}

// gravando dados do fornecedor em binario
void gravaFornecedorBIN(Fornecedor f)
{
    FILE *arq;

    arq = fopen("dadosFornecedor.bin", "rb");
    if (arq == NULL)
    {
        arq = fopen("dadosFornecedor.bin", "wb");
        fclose(arq);
    }
    fclose(arq);
    arq = fopen("dadosFornecedor.bin", "ab+");
    if (arq == NULL)
    {
        system("clear");
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    int result = fwrite(&f, sizeof(Fornecedor), 1, arq);
    if (result == 0)
    {
        printf("Erro na escrita do arquivo.\n");
    }
    else
    {
        printf("Fornecedor salvo com sucesso!\n");
    }
    fclose(arq);
    return;
}


// funçao que consulta o fornecedor desejado
void consultaFornecedor()
{

    int escolha;

    FILE *arq;
    Fornecedor fornecedorAtual;

    int codigoBusca;
    char nome_fantasiaBusca[100];
    char razao_socialBusca[100];
    char inscricao_estadualBusca[100];
    char cpfBusca[20];
    char enderecoBusca[100];
    char telefoneBusca[20];
    char emailBusca[30];

    int encontrado = 0;

    char confere[2];

    printf("CONFIGURAÇÃO ATUAL: ");
    if (tipoArquivo == FORMATO_TEXTO)
    {
        printf("TEXTO\n");
    }
    else
    {
        printf("BINÁRIO\n");
    }

    printf("----- CONSULTA FORNECEDOR -----");
    printf("\n\nOPÇÕES");
    printf("\n1 - CÓDIGO");
    printf("\n2 - NOME FANTASIA");
    printf("\n3 - RAZÃO SOCIAL");
    printf("\n4 - INCRIÇÃO ESTADUAL");
    printf("\n5 - CPF");
    printf("\n6 - ENDEREÇO");
    printf("\n7 - TELEFONE");
    printf("\n8 - EMAIL");
    printf("\n9 - LISTAR TODOS OS FORNCEDORES");
    printf("\n10 - VOLTAR PARA O MENU: ");

    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    if (tipoArquivo == FORMATO_TEXTO)
    {
        // Abrir arquivo texto
        arq = fopen("dadosFornecedor.txt", "r");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo de dados texto.\n");
            printf("\nCertifique-se de que o arquivo foi criado e possui informações para serem lidas.\n");
            return;
        }

        switch (escolha)
        {
        case 1: // Busca por código
            printf("\nDigite o código do fornecedor: ");
            scanf("%d", &codigoBusca);
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {

                if (fornecedorAtual.codigo == codigoBusca)
                {
                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 2: // Busca por nome fantasia
            printf("\nDigite o nome fantasia do fornecedor: ");
            scanf(" %[^\n]", nome_fantasiaBusca);
            encontrado = 0;
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {

                if (strcmp(fornecedorAtual.nome_fantasia, nome_fantasiaBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FORNECEDORES ENCONTRADOS -----\n");
                    }

                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 3: // Busca por razao social
            printf("\nDigite a razão social do fornecedor: ");
            scanf(" %[^\n]", razao_socialBusca);
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {

                if (strcmp(fornecedorAtual.razao_social, razao_socialBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 4: // Busca por inscriçao estadual
            printf("\nDigite a inscrição estadual do fornecedor: ");
            scanf(" %[^\n]", inscricao_estadualBusca);
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {

                if (strcmp(fornecedorAtual.inscricao_estadual, inscricao_estadualBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 5: // busca por cpf
            printf("\nDigite o cpf/cnpj do fornecedor: ");
            scanf(" %[^\n]", cpfBusca);
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {

                if (strcmp(fornecedorAtual.cpf, cpfBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 6: // Busca por endereco
            printf("\nDigite o endereço do fornecedor: ");
            scanf(" %[^\n]", enderecoBusca);
            encontrado = 0;
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {

                if (strcmp(fornecedorAtual.endereco, enderecoBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FORNECEDORES ENCONTRADOS -----\n");
                    }

                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 7: // Busca por telefone
            printf("\nDigite o telefone do fornecedor: ");
            scanf(" %[^\n]", telefoneBusca);
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {

                if (strcmp(fornecedorAtual.telefone, telefoneBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 8: // Busca por email
            printf("\nDigite o email do fornecedor: ");
            scanf(" %[^\n]", emailBusca);
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {
                if (strcmp(fornecedorAtual.email, emailBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 9: // lista todos os fonecedores disponíveis
            system("clear");
            printf("\t\t----- LISTA DE FORNECEDORES -----\n");
            printf("\n");
            encontrado = 0;
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                        fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                        fornecedorAtual.cpf, fornecedorAtual.endereco,
                        fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
            {
                encontrado++;
                printf("Código: %d\n", fornecedorAtual.codigo);
                printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                printf("CPF: %s\n", fornecedorAtual.cpf);
                printf("Endereço: %s\n", fornecedorAtual.endereco);
                printf("Telefone: %s\n", fornecedorAtual.telefone);
                printf("Email: %s\n", fornecedorAtual.email);
                printf("--------------------------------------------------------\n");
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        default:
            printf("\nOpção inválida.\n");
            fclose(arq);
            return;
        }

        fclose(arq); // Fechar o arquivo texto
    }
    else if (tipoArquivo == FORMATO_BINARIO)
    {
        // Abrir arquivo binário
        arq = fopen("dadosFornecedor.bin", "rb");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo binário.\n");
            printf("\nCertifique-se de que o arquivo foi criado e possui informações para serem lidas.\n");
            return;
        }

        switch (escolha)
        {
        case 1: // Busca por código
            printf("\nDigite o código do fornecedor: ");
            scanf("%d", &codigoBusca);
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (fornecedorAtual.codigo == codigoBusca)
                {
                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 2: // Busca por nome fantasia
            printf("\nDigite o nome fantasia do fornecedor: ");
            scanf(" %[^\n]", nome_fantasiaBusca);
            encontrado = 0;
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (strcmp(fornecedorAtual.nome_fantasia, nome_fantasiaBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FORNECEDORES ENCONTRADOS -----\n");
                    }

                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 3: // Busca por razao social
            printf("\nDigite a razão social do fornecedor: ");
            scanf(" %[^\n]", razao_socialBusca);
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (strcmp(fornecedorAtual.razao_social, razao_socialBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 4: // Busca por inscriçao estadual
            printf("\nDigite a inscrição estadual do fornecedor: ");
            scanf(" %[^\n]", inscricao_estadualBusca);
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (strcmp(fornecedorAtual.inscricao_estadual, inscricao_estadualBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 5: // busca por cpf
            printf("\nDigite o cpf/cnpj do fornecedor: ");
            scanf(" %[^\n]", cpfBusca);
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (strcmp(fornecedorAtual.cpf, cpfBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 6: // Busca por endereco
            printf("\nDigite o endereço do fornecedor: ");
            scanf(" %[^\n]", enderecoBusca);
            encontrado = 0;
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (strcmp(fornecedorAtual.endereco, enderecoBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FORNECEDORES ENCONTRADOS -----\n");
                    }

                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 7: // Busca por telefone
            printf("\nDigite o telefone do fornecedor: ");
            scanf(" %[^\n]", telefoneBusca);
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (strcmp(fornecedorAtual.telefone, telefoneBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 8: // Busca por email
            printf("\nDigite o email do fornecedor: ");
            scanf(" %[^\n]", emailBusca);
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {

                if (strcmp(fornecedorAtual.email, emailBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                    printf("Código: %d\n", fornecedorAtual.codigo);
                    printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                    printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                    printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                    printf("CPF: %s\n", fornecedorAtual.cpf);
                    printf("Endereço: %s\n", fornecedorAtual.endereco);
                    printf("Telefone: %s\n", fornecedorAtual.telefone);
                    printf("Email: %s\n", fornecedorAtual.email);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;
        case 9: // busca por todos os fornecedores em binario
            system("clear");
            printf("\t\t----- LISTA DE FORNECEDORES -----\n");
            printf("\n");
            encontrado = 0;
            while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
            {
                encontrado++;
                printf("Código: %d\n", fornecedorAtual.codigo);
                printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                printf("CPF: %s\n", fornecedorAtual.cpf);
                printf("Endereço: %s\n", fornecedorAtual.endereco);
                printf("Telefone: %s\n", fornecedorAtual.telefone);
                printf("Email: %s\n", fornecedorAtual.email);
                printf("--------------------------------------------------------\n");
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        default:
            printf("\nOpção inválida.\n");
            fclose(arq);
            return;
        }
    }
    else
    {
        printf("\nTipo de arquivo inválido nas configurações.\n");
        return;
    }

    printf("\nDeseja fazer uma outra busca? (S/N) ");
    scanf("%s", confere);
    if (strcmp(confere, "S") == 0 || strcmp(confere, "s") == 0)
    {
        system("clear");
        consultaFornecedor();
    }
    else
    {
        system("clear");
        return;
    }
}


// funcao para excluir algum fornecedor
void excluiFornecedor()
{

    Fornecedor fornecedorAtual;
    FILE *arq, *temp;

    int codigoBusca;
    int encontrado = 0;
    char excluir[5];

    printf("\nDigite o código do fornecedor que deseja excluir: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO)
    {
        arq = fopen("dadosFornecedor.txt", "r");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo texto.\n");
            return;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL)
        {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        // compara o codigo fornecido com os codigos de fornecedores disponiveis em texto e printa os dados do fornecedor encontrado
        while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                    &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                    fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                    fornecedorAtual.cpf, fornecedorAtual.endereco,
                    fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
        {

            if (fornecedorAtual.codigo == codigoBusca)
            {
                encontrado = 1;
                printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                printf("\nCódigo: %d\n", fornecedorAtual.codigo);
                printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                printf("CPF: %s\n", fornecedorAtual.cpf);
                printf("Endereço: %s\n", fornecedorAtual.endereco);
                printf("Telefone: %s\n", fornecedorAtual.telefone);
                printf("Email: %s\n", fornecedorAtual.email);
                printf("--------------------------------------------------------\n");
                printf("\nOs dados acima se referem ao fornecedor que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiFornecedor();
                }
                break;
            }
            if(encontrado){
                fprintf(temp, "%d;%s;%s;%s;%s;%s;%s;%s\n",
                    fornecedorAtual.codigo - 1, fornecedorAtual.nome_fantasia,
                    fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                    fornecedorAtual.cpf, fornecedorAtual.endereco,
                    fornecedorAtual.telefone, fornecedorAtual.email);
            }else{
                fprintf(temp, "%d;%s;%s;%s;%s;%s;%s;%s\n",
                    fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                    fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                    fornecedorAtual.cpf, fornecedorAtual.endereco,
                    fornecedorAtual.telefone, fornecedorAtual.email);
            }
        }

        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFornecedor.txt");
            rename("temp.txt", "dadosFornecedor.txt");
            printf("\nFornecedor excluído com sucesso!\n");
        }
        else
        {
            printf("\nFornecedor não encontrado.\n");
            remove("temp.txt");
        }
    }
    else if (tipoArquivo == FORMATO_BINARIO)
    {
        arq = fopen("dadosFornecedor.bin", "rb");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo binário.\n");
            return;
        }
        temp = fopen("temp.bin", "wb");
        if (temp == NULL)
        {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        // compara o codigo fornecido com os fornecedores disponiveis em binario e printa o fornecedor encontrado
        while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
        {

            if (fornecedorAtual.codigo == codigoBusca)
            {
                encontrado = 1;
                printf("\n----- FORNECEDOR ENCONTRADO -----\n");
                printf("Código: %d\n", fornecedorAtual.codigo);
                printf("Nome Fantasia: %s\n", fornecedorAtual.nome_fantasia);
                printf("Razão Social: %s\n", fornecedorAtual.razao_social);
                printf("Inscrição Estadual: %s\n", fornecedorAtual.inscricao_estadual);
                printf("CPF: %s\n", fornecedorAtual.cpf);
                printf("Endereço: %s\n", fornecedorAtual.endereco);
                printf("Telefone: %s\n", fornecedorAtual.telefone);
                printf("Email: %s\n", fornecedorAtual.email);
                printf("--------------------------------------------------------\n");
                printf("\nOs dados acima se referem ao fornecedor que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiFornecedor();
                }
            }
            if(encontrado){
                fornecedorAtual.codigo -= 1;
                fwrite(&fornecedorAtual, sizeof(Fornecedor), 1, temp);
            }else{
                fwrite(&fornecedorAtual, sizeof(Fornecedor), 1, temp);
            }
        }

        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFornecedor.bin");
            rename("temp.bin", "dadosFornecedor.bin");
            printf("\nFornecedor excluído com sucesso!\n");
        }
        else
        {
            printf("\nFornecedor não encontrado.\n");
            remove("temp.bin");
        }
    }
}


// funçao para edital algum fornecedor
void editaFornecedor()
{

    FILE *arq, *temp;
    Fornecedor fornecedorAtual;

    int encontrado;
    int codigoBusca;

    printf("\nDigite o código do fornecedor que deseja editar: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO)
    { // TEXTO
        arq = fopen("dadosFornecedor.txt", "r");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo texto. Certifique-se de que o arquivo existe.\n");
            return;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL)
        {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        // compara o codigo fornecido com o codigo presente no arquivo de texto para fazer a ediçao
        while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                    &fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                    fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                    fornecedorAtual.cpf, fornecedorAtual.endereco,
                    fornecedorAtual.telefone, fornecedorAtual.email) != EOF)
        {

            if (fornecedorAtual.codigo == codigoBusca)
            {

                encontrado = 1;
                printf("\nDigite os novos dados para o Fornecedor:\n");
                printf("\n\nInforme o novo código: ");
                scanf("%d", &fornecedorAtual.codigo);
                printf("Informe o novo nome fantasia: ");
                scanf("%s", fornecedorAtual.nome_fantasia);
                printf("Informe a nova razão social: ");
                scanf("%s", fornecedorAtual.razao_social);
                printf("Informe o a nova inscrição estadual: ");
                scanf("%s", fornecedorAtual.inscricao_estadual);
                printf("Informe o novo CNPJ (apenas números): ");
                scanf("%s", fornecedorAtual.cpf);
                printf("Informe o novo endereço completo: ");
                scanf("%s", fornecedorAtual.endereco);
                printf("Informe o novo telefone: ");
                scanf("%s", fornecedorAtual.telefone);
                printf("Informe o novo e-mail: ");
                scanf("%s", fornecedorAtual.email);
            }

            // salva a alteraçao no arquivo de texto
            fprintf(temp, "%d;%s;%s;%s;%s;%s;%s;%s\n",
                    fornecedorAtual.codigo, fornecedorAtual.nome_fantasia,
                    fornecedorAtual.razao_social, fornecedorAtual.inscricao_estadual,
                    fornecedorAtual.cpf, fornecedorAtual.endereco,
                    fornecedorAtual.telefone, fornecedorAtual.email);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFornecedor.txt");
            rename("temp.txt", "dadosFornecedor.txt");
            printf("\nFornecedor editado com sucesso!\n");
        }
        else
        {
            printf("\nFornecedor não encontrado.\n");
            remove("temp.txt");
        }
    }
    else if (tipoArquivo == FORMATO_BINARIO)
    { // BINÁRIO
        arq = fopen("dadosFornecedor.bin", "rb");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo binário.\n");
            return;
        }
        temp = fopen("temp.bin", "wb");
        if (temp == NULL)
        {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }


        // compara o codigo fornecido com o codigo presente no arquivo binario para fazer a ediçao
        while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, arq) == 1)
        {

            if (fornecedorAtual.codigo == codigoBusca)
            {

                encontrado = 1;
                printf("\nDigite os novos dados para o Fornecedor:\n");
                printf("\n\nInforme o novo código: ");
                scanf("%d", &fornecedorAtual.codigo);
                printf("Informe o novo nome fantasia: ");
                scanf("%s", fornecedorAtual.nome_fantasia);
                printf("Informe a nova razão social: ");
                scanf("%s", fornecedorAtual.razao_social);
                printf("Informe o a nova inscrição estadual: ");
                scanf("%s", fornecedorAtual.inscricao_estadual);
                printf("Informe o novo CNPJ (apenas números): ");
                scanf("%s", fornecedorAtual.cpf);
                printf("Informe o novo endereço completo: ");
                scanf("%s", fornecedorAtual.endereco);
                printf("Informe o novo telefone: ");
                scanf("%s", fornecedorAtual.telefone);
                printf("Informe o novo e-mail: ");
                scanf("%s", fornecedorAtual.email);
            }

            // salva a alteração no arquivo binario
            fwrite(&fornecedorAtual, sizeof(Fornecedor), 1, temp);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFornecedor.bin");
            rename("temp.bin", "dadosFornecedor.bin");
            printf("\nFornecedor editado com sucesso!\n");
        }
        else
        {
            printf("\nFornecedor não encontrada.\n");
            remove("temp.bin");
        }
    }
}