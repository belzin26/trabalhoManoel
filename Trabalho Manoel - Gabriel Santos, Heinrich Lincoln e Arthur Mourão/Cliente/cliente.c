#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#ifndef CONFIG_H
#define CONFIG_H

#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

extern int tipoArquivo;

void carregarConfiguracoes();


#endif

/*Busca, exclui e atualiza os códigos de todos os demais clientes utilizando como busca o código do mesmo.*/
void excluiCliente() {
    int codigoBusca, encontrado = 0;
    Cliente clienteAtual;
    FILE *arq, *temp;
    char excluir[5];

    printf("\nDigite o código do cliente que deseja buscar: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosClientes.txt", "r");
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

        while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                    &clienteAtual.codigo, clienteAtual.nome,
                    clienteAtual.cpf, clienteAtual.endereco,
                    clienteAtual.telefone, clienteAtual.email) != EOF) {
            if (clienteAtual.codigo == codigoBusca) {
                encontrado = 1;

                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nCódigo: %d", clienteAtual.codigo);
                printf("\nNome: %s", clienteAtual.nome);
                printf("\nCPF/CNPJ: %s", clienteAtual.cpf); 
                printf("\nEndereço: %s", clienteAtual.endereco);
                printf("\nE-mail: %s", clienteAtual.email);
                printf("\nTelefone: %s", clienteAtual.telefone);
                printf("\n-----------------------------------------\n");
                printf("\nOs dados acima se referem ao cliente que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiCliente();
                }
            }
            if(encontrado){
                fprintf(temp, "%d;%s;%s;%s;%s;%s\n",
                        clienteAtual.codigo - 1, clienteAtual.nome,
                        clienteAtual.cpf, clienteAtual.endereco,
                        clienteAtual.telefone, clienteAtual.email);
            }else{
                fprintf(temp, "%d;%s;%s;%s;%s;%s\n",
                        clienteAtual.codigo, clienteAtual.nome,
                        clienteAtual.cpf, clienteAtual.endereco,
                        clienteAtual.telefone, clienteAtual.email);
            }
        }

        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosClientes.txt");
            rename("temp.txt", "dadosClientes.txt");
            printf("\nCliente excluído com sucesso!\n");
        } else {
            printf("\nCliente não encontrado.\n");
            remove("temp.txt");
        }
    } else if (tipoArquivo == FORMATO_BINARIO) {
        arq = fopen("dadosClientes.bin", "rb");
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

        while (fread(&clienteAtual, sizeof(Cliente), 1, arq)) {
            if (clienteAtual.codigo == codigoBusca) {
                encontrado = 1;

                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nCódigo: %d", clienteAtual.codigo);
                printf("\nNome: %s", clienteAtual.nome);
                printf("\nCPF/CNPJ: %s", clienteAtual.cpf); 
                printf("\nEndereço: %s", clienteAtual.endereco);
                printf("\nE-mail: %s", clienteAtual.email);
                printf("\nTelefone: %s", clienteAtual.telefone);
                printf("\n-----------------------------------------\n");
                printf("\nOs dados acima se referem ao cliente que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if(strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0){
                    continue; // Ignora a gravação no arquivo temporário
                }else{
                    excluiCliente();
                }
            }
            if(encontrado){
                clienteAtual.codigo -= 1;
                fwrite(&clienteAtual, sizeof(Cliente), 1, temp);
            }else{
                fwrite(&clienteAtual, sizeof(Cliente), 1, temp);
            }
        }
        /*Fecha os arquivos que foram utilizados.*/
        fclose(arq);
        fclose(temp);

        if (encontrado) { // Se de fato encontrou o cliente/código 
            remove("dadosClientes.bin");
            rename("temp.bin", "dadosClientes.bin");
            printf("\nCliente excluído com sucesso!\n\n");
        } else { // Se não encontrou o código do cliente.
            printf("\nCliente não encontrado.\n");
            remove("temp.bin");
        }
    }
}

/*Edita uma peça específica do arquivo de extensão .txt ou .bin*/
void editaCliente() {
    int encontrado, codigoBusca;
    FILE *arq, *temp; 
    char editar[2]; // editar cliente?
    Cliente clienteAtual;
    
    printf("\nDigite o código do cliente que deseja editar: ");
    scanf("%d", &codigoBusca);

    if (tipoArquivo == FORMATO_TEXTO) { // TEXTO
        arq = fopen("dadosClientes.txt", "r");
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

        while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                    &clienteAtual.codigo, clienteAtual.nome,
                    clienteAtual.cpf, clienteAtual.endereco,
                    clienteAtual.telefone, clienteAtual.email) != EOF) {
            if (clienteAtual.codigo == codigoBusca) {
                encontrado = 1;

                printf("\n----- DADOS CADASTRADOS -----");
                printf("\n");
                printf("\n\nCódigo: %d", clienteAtual.codigo);
                printf("\nNome: %s", clienteAtual.nome);
                printf("\nCPF/CNPJ: %s", clienteAtual.cpf); 
                printf("\nEndereço: %s", clienteAtual.endereco);
                printf("\nE-mail: %s", clienteAtual.email);
                printf("\nTelefone: %s", clienteAtual.telefone);
                printf("\n-----------------------------------------\n");
                printf("\nOs dados acima se referem ao cliente que deseja editar? (S/N) ");
                scanf(" %[^\n]", editar);
                
                system("clear");
                if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0){
                    system("clear");
                    printf("\n----- NOVOS DADOS -----\n");
                    printf("\nNome: ");
                    scanf(" %[^\n]", clienteAtual.nome);
                    printf("CPF: ");
                    scanf(" %[^\n]", clienteAtual.cpf);
                    printf("Endereço: ");
                    scanf(" %[^\n]", clienteAtual.endereco);
                    printf("Telefone: ");
                    scanf(" %[^\n]", clienteAtual.telefone);
                    printf("E-mail: ");
                    scanf(" %[^\n]", clienteAtual.email);
                }else{
                    editaCliente();
                }
            }
            fprintf(temp, "%d;%s;%s;%s;%s;%s\n",
                    clienteAtual.codigo, clienteAtual.nome,
                    clienteAtual.cpf, clienteAtual.endereco,
                    clienteAtual.telefone, clienteAtual.email);
        }

        fclose(arq);
        fclose(temp);
        system("clear");

        if (encontrado) {
            remove("dadosClientes.txt");
            rename("temp.txt", "dadosClientes.txt");
            printf("Cliente editado com sucesso!\n\n");
        } else {
            printf("Cliente não encontrado.\n\n");
            remove("temp.txt");
        }

    } else if (tipoArquivo == FORMATO_BINARIO) { // BINÁRIO
        arq = fopen("dadosClientes.bin", "rb");
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

        while (fread(&clienteAtual, sizeof(Cliente), 1, arq)) {
            if (clienteAtual.codigo == codigoBusca) {
                encontrado = 1;
                printf("\nDigite os novos dados para o cliente:\n");
                printf("Nome: ");
                scanf(" %[^\n]", clienteAtual.nome);
                printf("CPF: ");
                scanf(" %[^\n]", clienteAtual.cpf);
                printf("Endereço: ");
                scanf(" %[^\n]", clienteAtual.endereco);
                printf("Telefone: ");
                scanf(" %[^\n]", clienteAtual.telefone);
                printf("E-mail: ");
                scanf(" %[^\n]", clienteAtual.email);
            }
            fwrite(&clienteAtual, sizeof(Cliente), 1, temp);
        }
        // Fecha os arquivos que foram utilizados
        fclose(arq);
        fclose(temp);

        if (encontrado) {
            remove("dadosClientes.bin");
            rename("temp.bin", "dadosClientes.bin");
            printf("\nCliente editado com sucesso!\n");
        } else {
            printf("\nCliente não encontrada.\n");
            remove("temp.bin");
        }
    }
}

/*Solicita dads para cadastro de cliente*/
void cadastroCliente(){
    Cliente c;
    FILE *arq;
    int codigo;

    codigo = 0;
    if (tipoArquivo == FORMATO_TEXTO){
        arq = fopen("dadosClientes.txt", "r");
        if (arq == NULL){
            arq = fopen("dadosClientes.txt", "w");
            fclose(arq);
            arq = fopen("dadosClientes.txt", "r");
        }
        while(fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                &c.codigo, c.nome,
                c.cpf, c.endereco,
                c.telefone, c.email) != EOF){
                    codigo += 1;
        }
    }else if(tipoArquivo == FORMATO_BINARIO){
        arq = fopen("dadosClientes.bin", "rb");
        if (arq == NULL){
            arq = fopen("dadosClientes.bin", "wb");
            fclose(arq);
            arq = fopen("dadosClientes.bin", "rb");
        }
        while(fread(&c, sizeof(Cliente), 1, arq) == 1){
                    codigo += 1;
        }
    }
    fclose(arq);

    system("clear");
    printf("----- CADASTRO CLIENTE -----");
    printf("\nInforme o nome do cliente: ");
    scanf(" %[^\n]", c.nome);
    printf("Informe o CPF/CNPJ do cliente: ");
    scanf(" %[^\n]", c.cpf);
    printf("Informe o telefone do cliente: ");
    scanf(" %[^\n]", c.telefone);
    printf("Informe o endereço do cliente: ");
    scanf(" %[^\n]", c.endereco);
    printf("Informe o e-mail do cliente: ");
    scanf(" %[^\n]", c.email);

    c.codigo = codigo;

    system("clear");
    confereDadosCliente(c); 
}

/*Confere os dados informados para cadastro do cliente / Passa a struct cadastro como parâmetro.
Já encaminha para o gravaDados se confere.*/
void confereDadosCliente(Cliente c) { 
    char confere[2];
    FILE *arq;

    system("clear");
    printf("----- CONFERÊNCIA DE DADOS ------");

    printf("\n\nCódigo: %d", c.codigo);
    printf("\nNome: %s", c.nome);
    printf("\nCPF/CNPJ: %s", c.cpf); 
    printf("\nEndereço: %s", c.endereco);
    printf("\nE-mail: %s", c.email);
    printf("\nTelefone: %s", c.telefone); 

    printf("\n\nOs dados acima conferem? (S/N)\n");
    scanf(" %[^\n]", confere);

    if ((strcmp(confere, "S") == 0) || (strcmp(confere, "s") == 0)) {
        system("clear");
        if (tipoArquivo == FORMATO_TEXTO){
            gravaClienteTXT(c);
        }else if(tipoArquivo == FORMATO_BINARIO){
            gravaClienteBIN(c);
        }else{
            system("clear");
            printf("Tipo de arquivo inválido.");
            exit(1);
        }
    } else {
        cadastroCliente();
    }
}

/*Grava cliente em arquivo texto*/
void gravaClienteTXT(Cliente c) {
    FILE *arq;

    arq = fopen("dadosClientes.txt", "r");
    if (arq == NULL){ // Criando arquivo caso não exista
        arq = fopen("dadosClientes.txt", "w");
    }
    fclose(arq);
    arq = fopen("dadosClientes.txt", "a");
    printf("\nSalvando dados... ");
    int result = fprintf(arq, "%d;%s;%s;%s;%s;%s\n", c.codigo, c.nome, c.cpf, c.endereco, c.telefone, c.email);
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

/*Grava cliente em arquivo binário*/
void gravaClienteBIN(Cliente c) {
    FILE *arq;

    arq = fopen("dadosClientes.bin", "rb");
    if (arq == NULL){
        arq = fopen("dadosClientes.bin", "wb");
        fclose(arq);
    }
    fclose(arq);
    arq = fopen("dadosClientes.bin", "ab+");
    if (arq == NULL) {
        system("clear");
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    // Gravando o cliente no arquivo binário
    printf("\nSalvando dados... ");
    int result = fwrite(&c, sizeof(Cliente), 1, arq);
    if (result == 0) {
        printf("Erro na escrita do arquivo.\n");
    } else {
        printf("Dados salvos com sucesso!\n");
    }
    fclose(arq);
    return;
}

/*Consulta de cliente por qualquer informação cadastrada no sistema. Se chave única (código, cpf, email) retorna apenas 1 cliente. Se não, retorna todos os resultados encontrados.*/
void consultaCliente() {
    FILE *arq;
    Cliente clienteAtual;

    int codigoBusca, escolha, encontrado = 0;
    char cpfBusca[20], telefoneBusca[20];
    char nomeBusca[100], emailBusca[100], enderecoBusca[100];
    char confere[2], novaConsulta[10];

    printf("CONFIGURAÇÃO ATUAL: ");
    if(tipoArquivo == FORMATO_TEXTO){
        printf("TEXTO");
    }else if(tipoArquivo == FORMATO_BINARIO){
        printf("BINÁRIO");
    }

    printf("\n\n----- CONSULTA CLIENTE -----");
    printf("\n\nOPÇÕES");
    printf("\n1 - Código");
    printf("\n2 - CPF");
    printf("\n3 - Nome");
    printf("\n4 - E-mail");
    printf("\n5 - Telefone");
    printf("\n6 - Endereço");
    printf("\n7 - VISUALIZAR TODOS OS CLIENTES");
    printf("\n\n8 - VOLTAR PARA O MENU");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    system("clear");
    if (escolha == 8){
        return;
    }

    if (tipoArquivo == FORMATO_TEXTO) {
        arq = fopen("dadosClientes.txt", "r");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo de dados texto.\n");
            printf("\nCertifique-se de que o arquivo foi criado e possui informações para serem lidas.");
            return;
        }

        switch (escolha) {
            case 1: // Busca por código
                printf("----- BUSCA CLIENTE -----\n");
                printf("\nDigite o código do cliente: ");
                scanf("%d", &codigoBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &clienteAtual.codigo, clienteAtual.nome,
                            clienteAtual.cpf, clienteAtual.endereco,
                            clienteAtual.telefone, clienteAtual.email) != EOF) {
                    if (clienteAtual.codigo == codigoBusca) {
                        printf("\n----- CLIENTE ENCONTRADO -----\n");
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 2: // Busca por CPF
                printf("\t\t----- BUSCA CLIENTE -----\n");
                printf("\nDigite o CPF do cliente: ");
                scanf(" %[^\n]", cpfBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &clienteAtual.codigo, clienteAtual.nome,
                            clienteAtual.cpf, clienteAtual.endereco,
                            clienteAtual.telefone, clienteAtual.email) != EOF) {

                    if (strcmp(clienteAtual.cpf, cpfBusca) == 0) {
                        printf("\n----- CLIENTE ENCONTRADO -----\n");
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 3: // Busca por nome
                printf("\t\t----- BUSCA CLIENTE -----\n");
                printf("\nDigite o nome do cliente: ");
                scanf(" %[^\n]", nomeBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &clienteAtual.codigo, clienteAtual.nome,
                            clienteAtual.cpf, clienteAtual.endereco,
                            clienteAtual.telefone, clienteAtual.email) != EOF) {
                    if (strcmp(clienteAtual.nome, nomeBusca) == 0){
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- CLIENTES ENCONTRADOS -----\n");
                        }
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        printf("\n-------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;
            
            case 4: // Busca por e-mail
                printf("\t\t----- BUSCA CLIENTE -----\n");
                printf("\nDigite o e-mail do cliente: ");
                scanf(" %[^\n]", emailBusca);
                encontrado = 0;
                system("clear");
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &clienteAtual.codigo, clienteAtual.nome,
                            clienteAtual.cpf, clienteAtual.endereco,
                            clienteAtual.telefone, clienteAtual.email) != EOF) {
                    if (strcmp(clienteAtual.email, emailBusca) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- CLIENTES ENCONTRADOS -----\n");
                        }
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("E-mail: %s\n", clienteAtual.email);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 5: // Busca por telefone
            printf("----- BUSCA CLIENTE -----\n");
                printf("\nDigite o telefone do cliente: ");
                scanf(" %[^\n]", telefoneBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &clienteAtual.codigo, clienteAtual.nome,
                            clienteAtual.cpf, clienteAtual.endereco,
                            clienteAtual.telefone, clienteAtual.email) != EOF) {
                    if (strcmp(clienteAtual.telefone, telefoneBusca) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- CLIENTES ENCONTRADOS -----\n");
                        }
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 6: // Busca por endereço
            printf("----- BUSCA CLIENTE -----\n");
                printf("\nDigite o endereço do cliente: ");
                scanf(" %[^\n]", enderecoBusca);
                system("clear");
                encontrado = 0;
                while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &clienteAtual.codigo, clienteAtual.nome,
                            clienteAtual.cpf, clienteAtual.endereco,
                            clienteAtual.telefone, clienteAtual.email) != EOF) {
                    if (strcmp(clienteAtual.endereco, enderecoBusca) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- CLIENTES ENCONTRADOS -----\n");
                        }
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 7: // Mostra toda a lista de clientes cadastradas no sistema
                printf("\t\t----- LISTA DE CLIENTES -----\n");
                printf("\n\n");
                encontrado = 0;
                system("clear");
                while(fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &clienteAtual.codigo, clienteAtual.nome,
                            clienteAtual.cpf, clienteAtual.endereco,
                            clienteAtual.telefone, clienteAtual.email) != EOF){
                    printf("Código: %d\n", clienteAtual.codigo);
                    printf("Nome: %s\n", clienteAtual.nome);
                    printf("CPF: %s\n", clienteAtual.cpf);
                    printf("Telefone: %s\n", clienteAtual.telefone);
                    printf("Endereço: %s\n", clienteAtual.endereco);
                    printf("E-mail: %s\n", clienteAtual.email);
                    printf("\n--------------------------------------------------------\n");
                    encontrado += 1;
                }
                if(encontrado){
                    printf("Número total de clientes cadastrados no sistema: %d", encontrado);
                }
                printf("\n");
                break;

            default:
                printf("\nOpção inválida.\n\n");
                fclose(arq);
                return;
        }
        fclose(arq); // Fechar o arquivo texto
        if(encontrado == 0){
            printf("\nNenhum cliente foi encontrado.");
        }
        printf("\n--------------------------------------------------------");
        printf("\nDeseja realizar uma nova busca? (S/N)");
        scanf(" %[^\n]", novaConsulta);

        if (strcmp(novaConsulta, "s") == 0 || strcmp(novaConsulta, "S") == 0){
            system("clear");
            consultaCliente();
        }else{
            system("clear");
        }
        return;

    } else if (tipoArquivo == FORMATO_BINARIO) { // Arquivo Binário
        // Abrir arquivo binário
        arq = fopen("dadosClientes.bin", "rb");
        if (arq == NULL) {
            printf("\nErro ao abrir o arquivo binário.\n");
            return;
        }
        
        switch (escolha) {
            case 1: // Busca por código
                printf("\nDigite o código do cliente: ");
                scanf("%d", &codigoBusca);
                system("clear");
                while (fread(&clienteAtual, sizeof(Cliente), 1, arq) == 1) {
                    if (clienteAtual.codigo == codigoBusca) {
                        printf("\n----- CLIENTE ENCONTRADO -----\n");
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        printf("\n--------------------------------------------------------\n");
                        break;
                    }
                }
                break;

            case 2: // Busca por CPF
                printf("\nDigite o CPF do cliente: ");
                scanf(" %[^\n]", cpfBusca);
                system("clear");
                encontrado = 0;
                while (fread(&clienteAtual, sizeof(Cliente), 1, arq) == 1) {
                    if (strcmp(clienteAtual.cpf, cpfBusca) == 0) {
                        printf("\n----- CLIENTE ENCONTRADO -----\n");
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        printf("\n--------------------------------------------------------\n");
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 3: // Busca por nome
                printf("\nDigite o nome do cliente: ");
                scanf(" %[^\n]", nomeBusca);
                system("clear");
                encontrado = 0;
                while (fread(&clienteAtual, sizeof(Cliente), 1, arq) == 1) {
                    if (strcmp(clienteAtual.nome, nomeBusca) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- CLIENTES ENCONTRADOS -----\n");
                        }
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;
            
            case 4: // Busca por e-mail
                printf("----- BUSCA CLIENTE -----\n");
                printf("\nDigite o e-mail do cliente: ");
                scanf(" %[^\n]", emailBusca);
                encontrado = 0;
                system("clear");
                while (fread(&clienteAtual, sizeof(Cliente), 1, arq) == 1) {
                    if (strcmp(clienteAtual.email, emailBusca) == 0) {
                        encontrado += 1;
                        if (encontrado == 1){
                            printf("\n----- CLIENTES ENCONTRADOS -----\n");
                        }
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("E-mail: %s\n", clienteAtual.email);
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;
            
            case 5: // Busca por telefone
                printf("----- BUSCA CLIENTE -----\n");
                printf("\nDigite o telefone do cliente: ");
                scanf(" %[^\n]", telefoneBusca);
                system("clear");
                encontrado = 0;
                while (fread(&clienteAtual, sizeof(Cliente), 1, arq) == 1) {
                    if (strcmp(clienteAtual.telefone, telefoneBusca) == 0) {
                        printf("\n----- CLIENTE ENCONTRADO -----\n");
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 6: // Busca por endereço
            printf("----- BUSCA CLIENTE -----\n");
                printf("\nDigite o endereço do cliente: ");
                scanf(" %[^\n]", enderecoBusca);
                system("clear");
                encontrado = 0;
                while (fread(&clienteAtual.endereco, sizeof(Cliente), 1, arq) == 1) {
                    if (strcmp(clienteAtual.endereco, enderecoBusca) == 0) {
                        printf("\n----- CLIENTE ENCONTRADO -----\n");
                        printf("Código: %d\n", clienteAtual.codigo);
                        printf("Nome: %s\n", clienteAtual.nome);
                        printf("CPF: %s\n", clienteAtual.cpf);
                        printf("Telefone: %s\n", clienteAtual.telefone);
                        printf("Endereço: %s\n", clienteAtual.endereco);
                        printf("Email: %s\n", clienteAtual.email);
                        encontrado += 1;
                        printf("\n--------------------------------------------------------\n");
                    }
                }
                if(encontrado){
                    printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
                }
                break;

            case 7: // Mostra toda a lista de clientes cadastrados no sistema
                printf("\t\t----- LISTA DE CLIENTES -----\n");
                printf("\n");
                encontrado = 0;
                while(fread(&clienteAtual, sizeof(Cliente), 1, arq) == 1){
                    encontrado += 1;
                    printf("Código: %d\n", clienteAtual.codigo);
                    printf("Nome: %s\n", clienteAtual.nome);
                    printf("CPF: %s\n", clienteAtual.cpf);
                    printf("Telefone: %s\n", clienteAtual.telefone);
                    printf("Endereço: %s\n", clienteAtual.endereco);
                    printf("E-mail: %s\n", clienteAtual.email);
                    printf("--------------------------------------------------------\n");
                }
                if(encontrado){
                    printf("Número total de clientes cadastrados no sistema: %d", encontrado);
                }else{
                    printf("Nenhum cliente cadastrado no sistema.");
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
            consultaCliente();
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
        consultaCliente();
    }else{
        system("clear");
        return;
    }
    return;
}