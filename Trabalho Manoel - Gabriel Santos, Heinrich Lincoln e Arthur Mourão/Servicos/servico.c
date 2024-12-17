#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "servico.h"

#ifndef CONFIG_H
#define CONFIG_H

#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

extern int tipoArquivo;

void carregarConfiguracoes();

#endif

/*Busca, exclui e atualiza os dados dos serviços utilizando o codigo como pesquisa */
void excluiServico() {
    int encontrado = 0, result, codigoBusca;
    Servico servicoAtual;
    FILE *arq, *temp;
    char excluir[5];

    printf("\nDigite o código do serviço: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosServicos.txt", "r");
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

        while (fscanf(arq, "%d;%[^;];%f;%f\n",  
                &servicoAtual.codigo, servicoAtual.descricao,
                &servicoAtual.comissao, &servicoAtual.preco) != EOF) {
            if (servicoAtual.codigo == codigoBusca) {
                encontrado = 1;

                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nCódigo: %d", servicoAtual.codigo);
                printf("\nDescrição: %s", servicoAtual.descricao);
                printf("\nPreço: %.2f", servicoAtual.preco);
                printf("\nComissão: %.2f", servicoAtual.comissao);
                printf("\nOs dados acima se referem ao serviço que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiServico();
                }

            } 
            
            if(encontrado){
                fprintf(temp, "%d;%s;%.2f;%.2f\n",
                    servicoAtual.codigo - 1, servicoAtual.descricao,
                    servicoAtual.comissao, servicoAtual.preco);
            }else{
                fprintf(temp, "%d;%s;%.2f;%.2f\n",
                    servicoAtual.codigo, servicoAtual.descricao,
                    servicoAtual.comissao, servicoAtual.preco);
            }

        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosServicos.txt");
            rename("temp.txt", "dadosServicos.txt");
            printf("\nServiço excluído com sucesso!\n");
        } else {
            printf("\nServiço não encontrado.\n");
            remove("temp.txt");
        }

    } else if (tipoArquivo == FORMATO_BINARIO) {
        arq = fopen("dadosServicos.bin", "rb");
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

        while (fread(&servicoAtual, sizeof(Servico), 1, arq) == 1) {
            if (servicoAtual.codigo == codigoBusca) {
                encontrado = 1; 
                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nCódigo: %d", servicoAtual.codigo);
                printf("\nDescrição: %s", servicoAtual.descricao);
                printf("\nPreço: %.2f", servicoAtual.preco);
                printf("\nComissão: %.2f", servicoAtual.comissao);
                printf("\nOs dados acima se referem ao serviço que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiServico();
                }

            } 
            if(encontrado){
                servicoAtual.codigo -= 1;
                fwrite(&servicoAtual, sizeof(Servico), 1, temp);
            }else{
                fwrite(&servicoAtual, sizeof(Servico), 1, temp);
            }
        }

        /*Fecha os arquivos que foram utilizados.*/
        fclose(arq);
        fclose(temp);

        if (encontrado) {// Se de fato encontrou o código 
            remove("dadosServicos.bin");
            rename("temp.bin", "dadosServicos.bin");
            printf("\nServiço excluído com sucesso!\n");
        } else { // se nao encontrou o codigo
            printf("\nServiço não encontrado.\n");
            remove("temp.bin");
        }
    }
}

//edita um serviço que o usuário escolher pelo código no arquivo txt ou bin depedendo da configuraçao
void editaServico() {
    int encontrado = 0;
    int codigoBusca;
    FILE *arq, *temp;
    char editar[10]; //variavel auxiliar q futuramente sera utilizada pra ter certeza de que é o serviço q ele quer editar 
    Servico servicoAtual;

    printf("\nDigite o código do serviço: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO) { // TEXTO
        arq = fopen("dadosServicos.txt", "r");
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

        while (fscanf(arq, "%d;%[^;];%f;%f\n",
                      &servicoAtual.codigo, servicoAtual.descricao,
                      &servicoAtual.comissao, &servicoAtual.preco) != EOF) {

            if (servicoAtual.codigo == codigoBusca) {
                encontrado = 1;

                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nCódigo: %d", servicoAtual.codigo);
                printf("\nDescrição: %s", servicoAtual.descricao);
                printf("\nPreço: %.2f", servicoAtual.preco);
                printf("\nComissão: %.2f", servicoAtual.comissao);
                printf("\nOs dados acima se referem ao serviço que deseja editar? (S/N) ");
                scanf(" %[^\n]", editar);

                system("clear");
                if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0) {
                    system("clear");
                    printf("\nDigite os novos dados para o serviço:\n");
                    printf("Descrição: ");
                    scanf(" %[^\n]", servicoAtual.descricao);
                    printf("Preço: ");
                    scanf("%f", &servicoAtual.preco);
                    printf("Comissão: ");
                    scanf("%f", &servicoAtual.comissao);
                }else{
                    editaServico();
                }
            }
            fprintf(temp, "%d;%s;%.2f;%.2f;\n",
                    servicoAtual.codigo, servicoAtual.descricao,
                    servicoAtual.comissao, servicoAtual.preco);
        }

        fclose(arq);
        fclose(temp);
        system("clear");

        if (encontrado) {
            remove("dadosServicos.txt");
            rename("temp.txt", "dadosServicos.txt");
            printf("\nServiço editado com sucesso!\n");
        } else {
            printf("\nServiço não encontrado.\n");
            remove("temp.txt");
        }

    } else if (tipoArquivo == FORMATO_BINARIO) { // BINÁRIO
        arq = fopen("dadosServicos.bin", "rb");
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

        while (fread(&servicoAtual, sizeof(Servico), 1, arq) == 1) {
            if (servicoAtual.codigo == codigoBusca) {
                encontrado = 1;

                printf("\n\nCódigo: %d", servicoAtual.codigo);
                printf("\nDescrição: %s", servicoAtual.descricao);
                printf("\nPreço: %.2f", servicoAtual.preco);
                printf("\nComissão: %.2f", servicoAtual.comissao);
                printf("\nOs dados acima se referem ao serviço que deseja editar? (S/N) ");
                scanf(" %[^\n]", editar);

                if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0) {
                    printf("\nDigite os novos dados para o serviço:\n");
                    printf("Descrição: ");
                    scanf(" %[^\n]", servicoAtual.descricao);
                    printf("Preço: ");
                    scanf("%f", &servicoAtual.preco);
                    printf("Comissão: ");
                    scanf("%f", &servicoAtual.comissao);
                }
            }
            fwrite(&servicoAtual, sizeof(Servico), 1, temp);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosServicos.bin");
            rename("temp.bin", "dadosServicos.bin");
            printf("\nServiço editado com sucesso!\n");
        } else {
            printf("\nServiço não encontrado.\n");
            remove("temp.bin");
        }
    }
}

//solicita os dados para o cadastro de serviços
void cadastroServico() {
    Servico s;
    FILE *arq;
    int codigo;

    codigo = 0;
    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosServicos.txt", "r");
        if (arq == NULL) {
            arq = fopen("dadosServicos.txt", "w");
            fclose(arq);
            arq = fopen("dadosServicos.txt", "r");
        }
        while (fscanf(arq, "%d;%[^;];%f;%f\n",
                      &s.codigo, s.descricao,
                      &s.comissao, &s.preco) != EOF) {
            codigo += 1;
        }
    }else if(tipoArquivo == FORMATO_BINARIO){
        arq = fopen("dadosServicos.bin", "rb");
        if (arq == NULL){
            arq = fopen("dadosServicos.bin", "wb");
            fclose(arq);
            arq = fopen("dadosServicos.bin", "rb");
        }
        while(fread(&s, sizeof(Servico), 1, arq) == 1){
                    codigo += 1;
        }
    }
    fclose(arq);


    system("clear");
    printf("----- CADASTRO SERVIÇO -----");

    printf("\n\nInforme a descrição do serviço: ");
    scanf("%s", s.descricao);
    printf("Informe o preco do serviço: ");
    scanf("%f", &s.preco);
    printf("Informe a comissão do serviço: ");
    scanf("%f", &s.comissao);

    s.codigo = codigo;

    system("clear");
    confereDadosServico(s); 
}

/*Confere os dados informados para cadastro do serviço / Passa a struct cadastro como parâmetro.
Já encaminha para o gravaDados se confere.*/
void confereDadosServico(Servico s) { 
    char confere[2];

    FILE *arq;

    system("clear");
    printf("\n----- CONFERÊNCIA DE DADOS ------");

    printf("\n\nCódigo: %d", s.codigo);
    printf("\nDescriçao: %s", s.descricao);
    printf("\nPreço: %.0f", s.preco);
    printf("\nComissão: %.0f", s.comissao); 
    

    printf("\n\nOs dados acima conferem? (S/N)\n");
    scanf(" %[^\n]", confere);

    if ((strcmp(confere, "S") == 0) || (strcmp(confere, "s") == 0)) {
        system("clear");
        if (tipoArquivo == FORMATO_TEXTO){
            gravaServicoTXT(s);
        }else if(tipoArquivo == FORMATO_BINARIO){
            gravaServicoBIN(s);
        }else{
            system("clear");
            printf("Tipo de arquivo inválido.");
            exit(1);
        }
    } else {
        cadastroServico();
    }
}

//grava serviço no arquivo .txt
void gravaServicoTXT(Servico s) {
    FILE *arq;

    arq = fopen("dadosServicos.txt", "r");
    if (arq == NULL){ // Criando arquivo caso não exista
        arq = fopen("dadosServicos.txt", "w");
    }
    fclose(arq);
    arq = fopen("dadosServicos.txt", "a");
    printf("\nSalvando dados... ");
    int result = fprintf(arq, "%d;%s;%.0f;%.0f\n", s.codigo, s.descricao, s.preco, s.comissao);
    if (result == 0){
        system("clear");
        printf("Erro na escrita do arquivo.\n");
        exit(1);
    }else{
        system("clear");
        printf("Dados gravados com sucesso!\n");
    }
    fclose(arq);
    return;
}

//grava serviço no arquivo .bin
void gravaServicoBIN(Servico s) {
    FILE *arq;

    arq = fopen("dadosServicos.bin", "ab+");
    if (arq == NULL) {
        arq = fopen("dadosServicos.bin", "rb");
        fclose(arq);
    }
    fclose(arq);
    arq = fopen("dadosServicos.bin", "ab+");
    if (arq == NULL) {
        system("clear");
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    // Gravando o servico no arquivo binário
    printf("\nSalvando dados... ");
    int result = fwrite(&s, sizeof(Servico), 1, arq);
    if (result == 0) {
        printf("Erro na escrita do arquivo.\n");
    } else {
        printf("Serviço salvo com sucesso!\n");
    }
    fclose(arq);
    return;
}

void consultaServico() {

    FILE *arq;
    Servico servicoAtual;

    int codigoBusca;
    char descricaoBusca[100];
    float comissaoBusca, precoBusca;

    int encontrado = 0, escolha;

    char confere[2], novaConsulta[10];

    char conf[10];
    char arquivo[10] = "TEXTO";

    arq = fopen("configuracoes.txt", "r");
    if (arq == NULL){
        arq = fopen("configuracoes.txt", "w");
        fprintf(arq, "%s", arquivo);
    }
    fclose(arq);

    printf("CONFIGURAÇÃO ATUAL: ");
    if(tipoArquivo == FORMATO_TEXTO){
        printf("TEXTO");
    }else{
        printf("BINÁRIO");
    }

    printf("\n\n----- CONSULTA SERVIÇO -----");
    printf("\n\nOPÇÕES");
    printf("\n1 - Código");
    printf("\n2 - descrição");
    printf("\n3 - comissão");
    printf("\n4 - preço");
    printf("\n5 - Visualizar todos os Serviços");
    printf("\n\n6 - Voltar para o menu");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    system("clear");
    if (escolha == 6){
        return;
    }

    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosServicos.txt", "r");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo de dados texto.\n");
            printf("\nCertifique-se de que o arquivo foi criado e possui informações para serem lidas.");
            return;
        }

        switch (escolha) {
            case 1: // Buscar por código
                printf("----- BUSCA SERVIÇO -----\n");
                printf("\nDigite o código do serviço: ");
                scanf("%d", &codigoBusca);
                system("clear");
                while (fscanf(arq, "%d;%[^;];%f;%f\n",
                      &servicoAtual.codigo, servicoAtual.descricao,
                      &servicoAtual.comissao, &servicoAtual.preco) != EOF) {

                    if (codigoBusca == servicoAtual.codigo) {
                        printf("\n----- SERVIÇO ENCONTRADO -----\n");
                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                        printf("--------------------------------------------------------\n");
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 2: // Busca por descrição
                printf("----- BUSCA SERVIÇO -----\n");
                printf("\nDigite a descrição do serviço: ");
                scanf(" %[^\n]", descricaoBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%f;%f\n",
                      &servicoAtual.codigo, servicoAtual.descricao,
                      &servicoAtual.comissao, &servicoAtual.preco) != EOF) {

                    if (strcmp(servicoAtual.descricao, descricaoBusca) == 0) {
                        encontrado++;
                        if(encontrado == 1){
                            printf("\n----- SERVIÇOS ENCONTRADOS -----\n");
                        }
                        printf("\n----------------------------\n");
                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                    }
                }
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;


            case 3: // Busca por comissão
                printf("----- BUSCA SERVIÇO -----\n");
                printf("\nDigite a comissão: ");
                scanf("%f", &comissaoBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%f;%f\n",
                      &servicoAtual.codigo, servicoAtual.descricao,
                      &servicoAtual.comissao, &servicoAtual.preco) != EOF) {

                    if (comissaoBusca == servicoAtual.comissao) {

                        encontrado++;
                        if(encontrado == 1){
                            printf("\n----- SERVIÇOS ENCONTRADOS -----\n");
                        }
                        
                        printf("\n----------------------------\n");
                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                    }
                }

                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;
            
            case 4: //Busca por preço
                printf("----- BUSCA SERVIÇO -----\n");
                printf("\nDigite o preço do serviço: ");
                scanf("%f", &precoBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%f;%f\n",
                      &servicoAtual.codigo, servicoAtual.descricao,
                      &servicoAtual.comissao, &servicoAtual.preco) != EOF) {

                    if (precoBusca == servicoAtual.preco) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- SERVIÇOS ENCONTRADOS -----\n");
                        }
                        
                        printf("\n----------------------------\n");
                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                    }
                }
                printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;

            case 5: // Mostra toda a lista de serviços cadastradas no sistema
                printf("\t\t----- LISTA DE SERVIÇOS -----\n");
                printf("\n\n");
                encontrado = 0;
                system("clear");
                while (fscanf(arq, "%d;%[^;];%f;%f\n",
                      &servicoAtual.codigo, servicoAtual.descricao,
                      &servicoAtual.comissao, &servicoAtual.preco) != EOF) {

                    printf("Código: %d\n", servicoAtual.codigo);
                    printf("Descrição: %s\n", servicoAtual.descricao);
                    printf("Comissão: %.0f\n", servicoAtual.comissao);
                    printf("preço: %.0f\n", servicoAtual.preco);
                    printf("--------------------------------------------------------\n");
                    encontrado += 1;
                }
                if(encontrado){
                    printf("Número total de serviços cadastrados no sistema: %d", encontrado);
                }
                printf("\n");
                break;

            default:
                printf("\nOpção inválida.\n");
                fclose(arq);
                return;
        }

        fclose(arq); // Fechar o arquivo texto
        if(encontrado == 0){
            printf("\nNenhum serviço foi encontrado.");
        }
        printf("\n--------------------------------------------------------");
        printf("\nDeseja realizar uma nova busca? (S/N)");
        scanf(" %[^\n]", novaConsulta);

        if (strcmp(novaConsulta, "s") == 0 || strcmp(novaConsulta, "S") == 0){
            system("clear");
            consultaServico();
        }else{
            system("clear");
        }
        return;

    } else if (tipoArquivo == FORMATO_BINARIO) {
        // Abrir arquivo binário
        arq = fopen("dadosServicos.bin", "rb");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo binário.\n");
            return;
        }

        switch (escolha) {
            case 1: // Busca por código
                printf("\nDigite o código do serviço: ");
                scanf("%d", &codigoBusca);
                system("clear");
                while (fread(&servicoAtual, sizeof(Servico), 1, arq) == 1) {

                    if (servicoAtual.codigo == codigoBusca) {
                        printf("\n----- SERVIÇO ENCONTRADO -----\n");
                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                        printf("--------------------------------------------------------\n");
                        break;
                    }
                }
                break;

            case 2: // Busca por descrição
                printf("\nDigite a descrição: ");
                scanf(" %[^\n]", descricaoBusca);
                system("clear");
                encontrado = 0;
                while (fread(&servicoAtual, sizeof(Servico), 1, arq) == 1) {
                    if (strcmp(servicoAtual.descricao, descricaoBusca) == 0) {
                        encontrado++;

                        if (encontrado == 1){
                            printf("\n----- SERVIÇOS ENCONTRADOS -----\n");
                        }

                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                        printf("--------------------------------------------------------\n");
                    }
                }
                printf("\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;

            case 3: // Busca por comissao
                printf("\nDigite a comissão do serviço: ");
                scanf("%f", comissaoBusca);
                system("clear");
                encontrado = 0;
                while (fread(&servicoAtual, sizeof(Servico), 1, arq) == 1) {
                    if (comissaoBusca == servicoAtual.comissao) {
                        encontrado++;

                        if (encontrado == 1){
                            printf("\n----- SERVIÇOS ENCONTRADOS -----\n");
                        }

                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                        printf("--------------------------------------------------------\n");
                    }
                }
                printf("\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;

            case 4: // Busca por preço
                printf("\nDigite o preço do serviço: ");
                scanf("%f", &precoBusca);
                system("clear");
                encontrado = 0;
                while (fread(&servicoAtual, sizeof(Servico), 1, arq) == 1) {
                    if (precoBusca == servicoAtual.preco) {
                        encontrado++;

                        if (encontrado == 1){
                            printf("\n----- SERVIÇOS ENCONTRADOS -----\n");
                        }

                        printf("Código: %d\n", servicoAtual.codigo);
                        printf("Descrição: %s\n", servicoAtual.descricao);
                        printf("Comissão: %.0f\n", servicoAtual.comissao);
                        printf("preço: %.0f\n", servicoAtual.preco);
                        printf("--------------------------------------------------------\n");
                    }
                }
                printf("\nRESULTADOS ENCONTRADOS: %d", encontrado);
                break;

            case 5: // Mostra toda a lista de serviços cadastrados no sistema
                printf("\t\t----- LISTA DE SERVIÇOS -----\n");
                printf("\n");
                encontrado = 0;
                while (fread(&servicoAtual, sizeof(Servico), 1, arq) == 1) {
                    printf("Código: %d\n", servicoAtual.codigo);
                    printf("Descrição: %s\n", servicoAtual.descricao);
                    printf("Comissão: %.0f\n", servicoAtual.comissao);
                    printf("preço: %.0f\n", servicoAtual.preco);
                    printf("--------------------------------------------------------\n");
                    encontrado += 1;
                }
                if(encontrado){
                printf("\nNúmero total de serviços cadastrados no sistema: %d", encontrado);
                }else{
                    printf("\nNenhum serviço encontrado.");
                }
                printf("\n");
                break;

            default:
                printf("\nOpção inválida.\n");
                fclose(arq);
                return;
        }
        fclose(arq); // Fechar o arquivo binário
        printf("\n--------------------------------------------------------");
        printf("\nDeseja realizar uma nova busca? (S/N)");
        scanf(" %[^\n]", novaConsulta);

        if (strcmp(novaConsulta, "s") == 0 || strcmp(novaConsulta, "S") == 0){
            system("clear");
            consultaServico();
        }else{
            system("clear");
        }
        return;

    } else {
        printf("\nTipo de arquivo inválido nas configurações.\n");
        return;
    }

    printf("\nDeseja fazer uma outra busca? (S/N) ");
    scanf(" %[^\n]", confere);
    if (strcmp(confere, "S") == 0 || strcmp(confere, "s") == 0){
        system("clear");
        consultaServico();
    }else{
        system("clear");
        return;
    }
}