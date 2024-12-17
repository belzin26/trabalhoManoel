#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "veiculo.h"
#ifndef CONFIG_H
#define CONFIG_H

#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

extern int tipoArquivo;

void carregarConfiguracoes();

#endif // CONFIG_H


//funçao que verifica se possui algum cliente com o cpf informado ja cadastrado, recebe por parametro o proprio cpf do dono do veiculo e uma variavel que retornara se foi ou nao encontrado o cpf no final
void relacionaVeiculoCliente(const char *cpf, int *resultado) { 
    FILE *arq;
    int relacionaCodigo;
    char relacionaNome[50], relacionaCpf[15], relacionaEndereco[100], relacionaTelefone[15], relacionaEmail[50];

    *resultado = 0;  // Inicializa resultado como não encontrado

    if (tipoArquivo == FORMATO_TEXTO) { //verfica se as informaçoes estao no arquivo txt
        // Abrindo arquivo de clientes em formato texto
        arq = fopen("dadosClientes.txt", "r");
        if (arq == NULL) {
            printf("Erro ao abrir o arquivo de clientes em texto.\n");
            return;
        }

        while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n", //le o arquivo linha por linha
                    &relacionaCodigo, relacionaNome,
                    relacionaCpf, relacionaEndereco,
                    relacionaTelefone, relacionaEmail) != EOF) {

            if (strcmp(relacionaCpf, cpf) == 0) { // compara pra ver se achou o cpf 
                *resultado = 1;
                fclose(arq);
                return;
            }
        }

        fclose(arq);
        printf("CPF não encontrado.\n");
        printf("Deseja cadastrar o cliente? (s/n): ");
        char opcao;
        scanf(" %[^\n]", &opcao);
        if (opcao == 's' || opcao == 'S') {
            cadastroCliente(); // Chama a função de cadastro do cliente
            *resultado = 1;
        } else {
            printf("Veículo não registrado sem um cliente.\n");
            printf("Voltando ao menu.\n");
            return;
        }
    } else if (tipoArquivo == FORMATO_BINARIO) {
        // Abrindo arquivo de clientes em formato binário
        arq = fopen("dadosClientes.bin", "rb");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo de dados binário.\n");
            printf("Certifique-se de que o arquivo foi criado e possui informações para serem lidas.\n");
            return;
        }

        struct Cliente {
            int codigo;
            char nome[50];
            char cpf[15];
            char endereco[100];
            char telefone[15];
            char email[50];
        } cliente;

        while (fread(&cliente, sizeof(cliente), 1, arq)) {
            if (strcmp(cliente.cpf, cpf) == 0) {
                *resultado = 1;
                fclose(arq);
                return;
            }
        }

        fclose(arq);
        printf("CPF não encontrado.\n");
        printf("Deseja cadastrar o cliente? (s/n): ");
        char opcao;
        scanf(" %[^\n]", &opcao);
        if (opcao == 's' || opcao == 'S') {
            cadastroCliente();
            *resultado = 1;
        } else {
            printf("Veículo não registrado sem um cliente.\n");
            return;
        }
    }
    return;
}

//exclui veiculo pela placa
void excluiVeiculo() {
    int encontrado = 0, result;
    char placaBusca[10];
    Veiculo veiculoAtual;
    FILE *arq, *temp;
    char excluir[5];

    // solicitando a placa do veiculo que vai ser excluido
    printf("\nDigite a placa do veículo que deseja buscar: ");
    scanf("%s", placaBusca);

    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosVeiculos.txt", "r");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo texto.\n");
            return;
        }
        temp = fopen("temp.txt", "w"); //cria um arquivo temporario
        if (temp == NULL) {
            printf("\nErro ao criar arquivo temporário.\n");
            fclose(arq);
            return;
        }

        while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                    veiculoAtual.placa, veiculoAtual.modelo,
                    veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                    veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {

            if (strcmp(veiculoAtual.placa, placaBusca) == 0) {
                encontrado = 1; // Placa encontrada exclui o veículo


                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nPlaca: %s", veiculoAtual.placa);
                printf("\nModelo: %s", veiculoAtual.modelo);
                printf("\nMarca: %s", veiculoAtual.marca); 
                printf("\nAno de fabricação: %d", veiculoAtual.ano_fabricacao);
                printf("\nChassi: %s", veiculoAtual.chassi);
                printf("\nCPF: %s", veiculoAtual.cpf);
                printf("\nOs dados acima se referem ao veículo que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);


                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiVeiculo();
                }
            } 
             //grava no arquivo temporario os dados dos outros veiculos
            fprintf(temp, "%s;%s;%s;%d;%s;%s\n",
            veiculoAtual.placa, veiculoAtual.modelo, 
            veiculoAtual.marca, veiculoAtual.ano_fabricacao,
            veiculoAtual.chassi, veiculoAtual.cpf);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosVeiculos.txt"); //apaga o arquivo 
            rename("temp.txt", "dadosVeiculos.txt"); //renomeia esse arquvi para q agora ele vire o novo dados.txt
            printf("\nVeículo excluído com sucesso!\n");
        } else {
            printf("\nVeículo não encontrado.\n");
            remove("temp.txt");
        }

    } else if (tipoArquivo == FORMATO_BINARIO) {
        // Modo binário
        arq = fopen("dadosVeiculos.bin", "rb");
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

        // Lê e filtra os veículos
        while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {
            if (strcmp(veiculoAtual.placa, placaBusca) == 0) {
                encontrado = 1; // Placa encontrada, exclui o veículo
                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nPlaca: %s", veiculoAtual.placa);
                printf("\nModelo: %s", veiculoAtual.modelo);
                printf("\nMarca: %s", veiculoAtual.marca); 
                printf("\nAno de fabricação: %d", veiculoAtual.ano_fabricacao);
                printf("\nChassi: %s", veiculoAtual.chassi);
                printf("\nCPF: %s", veiculoAtual.cpf);
                printf("\nOs dados acima se referem ao veículo que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiVeiculo();
                }
                
            } else {
                fwrite(&veiculoAtual, sizeof(Veiculo), 1, temp);
            }
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosVeiculos.bin");
            rename("temp.bin", "dadosVeiculos.bin");
            printf("\nVeículo excluído com sucesso!\n");
        } else {
            printf("\nVeículo não encontrado.\n");
            remove("temp.bin");
        }
    }
}


//edita dados do veículo que o cliente escolher
void editaVeiculo() {
    int result, encontrado = 0;
    char placaBusca[10];
    FILE *arq, *temp; 
    char conf[10], editar[2];
    char arquivo[10] = "TEXTO"; 
    Veiculo veiculoAtual;
    
    printf("\nDigite a placa do veículo que deseja editar: ");
    scanf(" %[^\n]", placaBusca);

    if (tipoArquivo == FORMATO_TEXTO) { // TEXTO
        arq = fopen("dadosVeiculos.txt", "r");
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

        while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n", //le o arquivo original todas as linhas
            veiculoAtual.placa, veiculoAtual.modelo, 
            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
            veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {
                        
            if (strcmp(veiculoAtual.placa, placaBusca) == 0) {
                encontrado = 1;

                printf("\n\nPlaca: %s", veiculoAtual.placa);
                printf("\nModelo: %s", veiculoAtual.modelo);
                printf("\nMarca: %s", veiculoAtual.marca); 
                printf("\nAno de fabricação: %d", veiculoAtual.ano_fabricacao);
                printf("\nChassi: %s", veiculoAtual.chassi);
                printf("\nCPF: %s", veiculoAtual.cpf);
                printf("\nOs dados acima se referem ao veículo que deseja editar? (S/N) ");
                scanf(" %[^\n]", editar);


                if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0){
                    printf("\nDigite os novos dados para o veiculo:\n");
                    printf("Placa: ");
                    scanf(" %[^\n]", veiculoAtual.placa);
                    printf("Modelo: ");
                    scanf(" %[^\n]", veiculoAtual.modelo);
                    printf("Marca: ");
                    scanf(" %[^\n]", veiculoAtual.marca);
                    printf("Ano de fabricação: ");
                    scanf("%d", &veiculoAtual.ano_fabricacao);
                    printf("Chassi: ");
                    scanf(" %[^\n]", veiculoAtual.chassi);
                    printf("CPF do dono do veículo: ");
                    scanf(" %[^\n]", veiculoAtual.cpf);
                }else{
                    system("clear");
                    editaVeiculo();
                }
            }
            fprintf(temp, "%s;%s;%s;%d;%s;%s\n",
                veiculoAtual.placa, veiculoAtual.modelo, 
                veiculoAtual.marca, veiculoAtual.ano_fabricacao,
                veiculoAtual.chassi, veiculoAtual.cpf);
        }

        system("clear");
        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosVeiculos.txt");
            rename("temp.txt", "dadosVeiculos.txt");
            printf("\nVeiculo editado com sucesso!\n");
        } else {
            printf("\nVeiculo não encontrado.\n");
            remove("temp.txt");
        }

    } else if (tipoArquivo == FORMATO_BINARIO) { // BINÁRIO
        arq = fopen("dadosVeiculos.bin", "rb");
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

        while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {
            if (strcmp(veiculoAtual.placa, placaBusca)) {
                encontrado = 1;

                printf("\n\nPlaca: %s", veiculoAtual.placa);
                printf("\nModelo: %s", veiculoAtual.modelo);
                printf("\nMarca: %s", veiculoAtual.marca); 
                printf("\nAno de fabricação: %d", veiculoAtual.ano_fabricacao);
                printf("\nChassi: %s", veiculoAtual.chassi);
                printf("\nCPF: %s", veiculoAtual.cpf);
                printf("\nOs dados acima se referem ao veículo que deseja editar? (S/N) ");
                scanf(" %[^\n]", editar);


                if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0){
                    printf("\nDigite os novos dados para o veiculo:\n");
                    printf("Placa: ");
                    scanf(" %[^\n]", veiculoAtual.placa);
                    printf("Modelo: ");
                    scanf(" %[^\n]", veiculoAtual.modelo);
                    printf("Marca: ");
                    scanf(" %[^\n]", veiculoAtual.marca);
                    printf("Ano de fabricação: ");
                    scanf("%d", &veiculoAtual.ano_fabricacao);
                    printf("Chassi: ");
                    scanf(" %[^\n]", veiculoAtual.chassi);
                    printf("CPF do dono: ");
                    scanf(" %[^\n]", veiculoAtual.cpf);
                }
            }
            fwrite(&veiculoAtual, sizeof(Veiculo), 1, temp);
        }

        system("clear");
        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosVeiculos.bin");
            rename("temp.bin", "dadosVeiculos.bin");
            printf("\nVeiculo editado com sucesso!\n");
        } else {
            printf("\nVeiculo não encontrada.\n");
            remove("temp.bin");
        }
    }
}


//tenta cadastrar um veículo
void cadastroVeiculo() {
    Veiculo v;
    char arquivo[10] = "TEXTO";

    system("clear");
    printf("----- CADASTRO VEICULO -----");

    printf("\n\nInforme a placa do veículo: ");
    scanf(" %[^\n]", v.placa);
    printf("Informe o modelo do veículo: ");
    scanf(" %[^\n]", v.modelo);
    printf("Informe a marca do veículo: ");
    scanf(" %[^\n]", v.marca);
    printf("Informe o ano de fabricação do veículo: ");
    scanf("%d", &v.ano_fabricacao);
    printf("Informe o chassi do veículo: ");
    scanf(" %[^\n]", v.chassi);
    printf("Informe o CPF do dono do veículo: ");
    scanf(" %[^\n]", v.cpf);

    int resultado;
    relacionaVeiculoCliente(v.cpf, &resultado);
    if (resultado != 1) {
        printf("Cadastro do veículo cancelado.\n");
        return;
    }

    system("clear");
    confereDadosVeiculo(v);
}

/*Confere os dados informados para cadastro do veiculo / Passa a struct cadastro como parâmetro.
Já encaminha para o gravaDados se confere.*/

void confereDadosVeiculo(Veiculo v) { 
    char confere[2];
    char conf[10];
    char tipo[10] = "TEXTO";

    system("clear");
    printf("----- CONFERÊNCIA DE DADOS ------");

    printf("\n\nPlaca: %s", v.placa);
    printf("\nModelo: %s", v.modelo);
    printf("\nMarca: %s", v.marca); 
    printf("\nAno de fabricação: %d", v.ano_fabricacao);
    printf("\nChassi: %s", v.chassi);
    printf("\nCPF: %s", v.cpf); 

    printf("\n\nOs dados acima conferem? (S/N)\n");
    scanf("%s", confere);

    if ((strcmp(confere, "S") == 0) || (strcmp(confere, "s") == 0)) {
        system("clear");
        printf("\nSalvando dados... ");
        if (tipoArquivo == FORMATO_TEXTO){
            gravaVeiculoTXT(v);
        }else if(tipoArquivo == FORMATO_BINARIO){
            gravaVeiculoBIN(v);
        }else{
            system("clear");
            printf("Tipo de arquivo inválido.");
            exit(1);
        }
    } else {
        cadastroVeiculo();
    }
    return;
}


/*Essa funçao esta gravando o veiculo num arquivo TXT*/
    void gravaVeiculoTXT(Veiculo v) {
        FILE *arq;

        arq = fopen("dadosVeiculos.txt", "r");
        if (arq == NULL){ // Criando arquivo caso não exista
            arq = fopen("dadosVeiculos.txt", "w");
        }
        fclose(arq);
        arq = fopen("dadosVeiculos.txt", "a");
        int result = fprintf(arq, "%s;%s;%s;%d;%s;%s\n", 
                v.placa, v.modelo, v.marca, 
                v.ano_fabricacao, v.chassi, v.cpf);

        if (result == 0){
            system("clear");
            printf("Erro na escrita do arquivo.");
            exit(1);
        }else{
            system("clear");
            printf("Dados gravados com sucesso!\n\n");
        }
        fclose(arq);
        return;
    }

/*Essa funçao esta gravando o veiculo num arquivo BIN*/
void gravaVeiculoBIN(Veiculo v) {
    FILE *arq;

    arq = fopen("dadosVeiculos.bin", "rb");
    if (arq == NULL){
        arq = fopen("dadosVeiculos.bin", "wb");
        fclose(arq);
    }
    fclose(arq);
    arq = fopen("dadosVeiculos.bin", "ab+");
    if (arq == NULL) {
        system("clear");
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    // Gravando o veículo no arquivo binário
    printf("\nSalvando dados... ");
    int result = fwrite(&v, sizeof(Veiculo), 1, arq);
    if (result == 0) {
        printf("Erro na escrita do arquivo.\n");
    } else {
        printf("Veiculo salvo com sucesso!\n");
    }
    fclose(arq);
    return;
}

//funçao responsável pela consulta de dados do veículo seja por qualquer dado que esteja no struct q o usuário queira
void consultaVeiculo() { 
    FILE *arq;
    Veiculo veiculoAtual;
    
    char placaBusca[10];
    char modeloBusca[50];
    char marcaBusca[20];
    int ano_fabricacaoBusca;
    char chassiBusca[100];
    char cpfBusca[20];

    int encontrado = 0, result, escolha;
    
    char confere[2];

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

    printf("\n\n----- CONSULTA VEICULO -----");
    printf("\n\nOPÇÕES");
    printf("\n1 - Placa");
    printf("\n2 - Modelo");
    printf("\n3 - Marca");
    printf("\n4 - Ano de fabricação");
    printf("\n5 - Chassi");
    printf("\n6 - CPF do dono do veículo");
    printf("\n7 - Visualizar todos os veículos");
    printf("\n\n8 - Voltar para o menu");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    if (escolha == 8){
        system("clear");
        return;
    }

    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosVeiculos.txt", "r");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo de dados texto.\n");
            printf("\nCertifique-se de que o arquivo foi criado e possui informações para serem lidas.");
            return;
        }

        switch (escolha) {
            case 1: // Busca por placa
                printf("\nDigite a placa do veículo: ");
                scanf(" %[^\n]", placaBusca);
                system("clear");
                while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                            veiculoAtual.placa, veiculoAtual.modelo, 
                            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                            veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {

                    if (strcmp(veiculoAtual.placa, placaBusca) == 0) {
                        encontrado = 1;
                        printf("\n----- VEICULO ENCONTRADO -----\n");
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                        break;
                    }
                }

                break;

            case 2: // Busca por Modelo
                printf("\nDigite o modelo do carro: ");
                scanf(" %[^\n]", modeloBusca);
                encontrado = 0;
                system("clear");
                while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                            veiculoAtual.placa, veiculoAtual.modelo, 
                            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                            veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {

                    if (strcmp(veiculoAtual.modelo, modeloBusca) == 0) {
                        encontrado += 1;
                        if(encontrado == 1){
                            printf("\n----- VEICULOS ENCONTRADOS -----\n");
                        }
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;


            case 3: // Busca por Marca
                printf("\nDigite a marca: ");
                scanf(" %[^\n]", marcaBusca);
                encontrado = 0;
                system("clear");
                while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                            veiculoAtual.placa, veiculoAtual.modelo, 
                            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                            veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {

                    if (strcmp(veiculoAtual.marca, marcaBusca) == 0) {
                        encontrado += 1;
                        if(encontrado == 1){
                            printf("\n----- VEICULOS ENCONTRADOS -----\n");
                        }
                        
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;
            
            case 4: //Busca por ano de fabricaçao
                printf("\nDigite o ano de fabricação do veículo: ");
                scanf("%d", &ano_fabricacaoBusca);
                encontrado = 0;
                system("clear");
                while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                            veiculoAtual.placa, veiculoAtual.modelo, 
                            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                            veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {

                    if (veiculoAtual.ano_fabricacao == ano_fabricacaoBusca) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- VEICULOS ENCONTRADOS -----\n");
                        }
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 5: //Busca por chassi
                printf("\nDigite o chassi do veículo: ");
                scanf(" %[^\n]", chassiBusca);
                system("clear");
                while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%lf\n",
                            veiculoAtual.placa, veiculoAtual.modelo, 
                            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                            veiculoAtual.chassi, &veiculoAtual.cpf) != EOF) {

                    if (strcmp(veiculoAtual.chassi, chassiBusca) == 0) {
                        encontrado = 1;
                        printf("\n----- VEICULO ENCONTRADO -----\n");
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                        break;
                    }
                }
                break;

            case 6: //Busca por cpf do dono
                printf("\nDigite o CPF do dono do veículo: ");
                scanf(" %[^\n]", cpfBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                            veiculoAtual.placa, veiculoAtual.modelo, 
                            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                            veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {

                    if (strcmp(veiculoAtual.cpf, cpfBusca) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- VEICULOS ENCONTRADOS -----\n");
                        }
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("RESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 7: // Mostra toda a lista de veiculos cadastradas no sistema
                system("clear");
                printf("\t\t----- LISTA DE VEÍCULOS -----\n");
                printf("\n");
                encontrado = 0;
                while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                            veiculoAtual.placa, veiculoAtual.modelo, 
                            veiculoAtual.marca, &veiculoAtual.ano_fabricacao,
                            veiculoAtual.chassi, veiculoAtual.cpf) != EOF) {
                    printf("Placa: %s\n", veiculoAtual.placa);
                    printf("Modelo: %s\n", veiculoAtual.modelo);
                    printf("Marca: %s\n", veiculoAtual.marca);
                    printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                    printf("Chassi: %s\n", veiculoAtual.chassi);
                    printf("CPF: %s\n", veiculoAtual.cpf);
                    printf("--------------------------------------------------------\n");
                    encontrado += 1;
                }
                if(encontrado){
                    printf("\nNúmero total de veículos cadastrados no sistema: %d", encontrado);
                }
                printf("\n");
                break;

            default: //talvez esse dafault dê pau pq se clicar 8 é pra sair mas tb vai entrar nele
                printf("\nOpção inválida.\n");
                fclose(arq);
                return;
        }
        
        if(encontrado == 0){
            printf("\nNenhum veículo encontrado");
        }

        fclose(arq); // Fechar o arquivo texto

    } else if (tipoArquivo == FORMATO_BINARIO) {
        // Abrir arquivo binário
        arq = fopen("dadosVeiculos.bin", "rb");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo binário.\n");
            return;
        }

        switch (escolha) {
            case 1: // Busca por placa
                printf("\nDigite a placa do veículo: ");
                scanf(" %[^\n]", placaBusca);
                system("clear");
                while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {
                    if (strcmp(veiculoAtual.placa, placaBusca) == 0) {
                        encontrado = 1;
                        printf("\n----- VEICULO ENCONTRADO -----\n");
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                        break;
                    }
                }
                break;

            case 2: // Busca por MODELO
                printf("\nDigite o modelo do carro: ");
                scanf(" %[^\n]", modeloBusca);
                system("clear");
                encontrado = 0;
                while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {
                    if (strcmp(veiculoAtual.modelo, modeloBusca) == 0) {
                        encontrado++;

                        if (encontrado == 1){
                            printf("\n----- VEÍCULOS ENCONTRADOS -----\n");
                        }

                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 3: // Busca por marca
                printf("\nDigite a marca do carro: ");
                scanf(" %[^\n]", marcaBusca);
                system("clear");
                encontrado = 0;
                while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {
                    if (strcmp(veiculoAtual.marca, marcaBusca) == 0) {
                        encontrado++;

                        if (encontrado == 1){
                            printf("\n----- VEÍCULOS ENCONTRADOS -----\n");
                        }

                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 4: // Busca por ano de fabricaçaço
                printf("\nDigite o ano de fabricaçao do carro: ");
                scanf("%d", &ano_fabricacaoBusca);
                system("clear");
                encontrado = 0;
                while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {
                    if (veiculoAtual.ano_fabricacao == ano_fabricacaoBusca) {
                        encontrado++;

                        if (encontrado == 1){
                            printf("\n----- VEÍCULOS ENCONTRADOS -----\n");
                        }

                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 5: // Busca por chassi
                printf("\nDigite o chassi do carro: ");
                scanf(" %[^\n]", chassiBusca);
                system("clear");
                while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {

                    if (strcmp(veiculoAtual.chassi, chassiBusca) == 0) {
                        printf("\n----- VEICULO ENCONTRADO -----\n");
                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                        break;
                    }
                }
                break;

            case 6: // Busca por cpf do dono
                printf("\nDigite o CPF do dono do carro: ");
                scanf(" %[^\n]", cpfBusca);
                system("clear");
                encontrado = 0;
                while (fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1) {
                    if (strcmp(veiculoAtual.cpf, cpfBusca)) {
                        encontrado++;

                        if (encontrado == 1){
                            printf("\n----- VEÍCULOS ENCONTRADOS -----\n");
                        }

                        printf("Placa: %s\n", veiculoAtual.placa);
                        printf("Modelo: %s\n", veiculoAtual.modelo);
                        printf("Marca: %s\n", veiculoAtual.marca);
                        printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                        printf("Chassi: %s\n", veiculoAtual.chassi);
                        printf("CPF: %s\n", veiculoAtual.cpf);
                        printf("--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("RESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 7: // Mostra toda a lista de veículos cadastrados no sistema
                printf("\t\t----- LISTA DE VEÍCULOS -----\n");
                printf("\n");
                encontrado = 0;
                while(fread(&veiculoAtual, sizeof(Veiculo), 1, arq) == 1){
                    printf("Placa: %s\n", veiculoAtual.placa);
                    printf("Modelo: %s\n", veiculoAtual.modelo);
                    printf("Marca: %s\n", veiculoAtual.marca);
                    printf("Ano de Fabricação: %d\n", veiculoAtual.ano_fabricacao);
                    printf("Chassi: %s\n", veiculoAtual.chassi);
                    printf("CPF: %s\n", veiculoAtual.cpf);
                    printf("--------------------------------------------------------\n");
                    encontrado += 1;
                }
                if(encontrado){
                    printf("Número total de veículos cadastrados no sistema: %d", encontrado);
                }
                printf("\n");
                break;

            default:
                printf("\nOpção inválida.\n");
                fclose(arq);
                return;
        }

        if(encontrado == 0){
            printf("\nNenhum veículo encontrado");
        }
        fclose(arq); // Fechar o arquivo binário

    } else {
        printf("\nTipo de arquivo inválido nas configurações.\n");
        return;
    }

    printf("\nDeseja fazer uma outra busca? (S/N) ");
    scanf(" %[^\n]", confere);
    if (strcmp(confere, "S") == 0 || strcmp(confere, "s") == 0){
        system("clear");
        consultaVeiculo();
    }else{
        system("clear");
        return;
    }
}