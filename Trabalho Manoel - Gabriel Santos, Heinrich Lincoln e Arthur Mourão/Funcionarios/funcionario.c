#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionario.h"
#ifndef CONFIG_H
#define CONFIG_H

// Define os tipos de arquivo possíveis
#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

// Variável para armazenar o tipo de arquivo
extern int tipoArquivo;

void carregarConfiguracoes();

#endif

// funcao para cadastras o funcionario
void cadastroFuncionario()
{
    Funcionario f;

    system("clear");
    printf("----- CADASTRO FUNCIONÁRIO -----");

    printf("\n\nInforme o nome: ");
    scanf(" %[^\n]", f.nome);
    printf("Informe o cpf: ");
    scanf(" %[^\n]", f.cpf);
    printf("Informe o cargo: ");
    scanf(" %[^\n]", f.cargo);
    printf("Informe o salário (Apenas números): ");
    scanf("%f", &f.salario);

    system("clear");
    confereDadosFuncionario(f);
}

// funcao para conferir se os dados estao corretos e enviar para a gravaçao tanto em texto quanto binario
void confereDadosFuncionario(Funcionario f)
{

    FILE *arq;
    char confere[2];

    char conf[10];
    char tipo[10] = "TEXTO";

    system("clear");
    printf("----- CONFERÊNCIA DE DADOS ------");

    printf("\n\nNome: %s", f.nome);
    printf("\nCPF: %s", f.cpf);
    printf("\nCargo: %s", f.cargo);
    printf("\nSalário: %.2f", f.salario);

    printf("\n\nOs dados acima conferem? (S/N)\n");
    scanf("%s", confere);

    if ((strcmp(confere, "S") == 0) || (strcmp(confere, "s") == 0))
    {
        system("clear");
        printf("\nSalvando dados...");
        if (tipoArquivo == FORMATO_TEXTO)
        {
            gravaFuncionarioTXT(f);
        }
        else if (tipoArquivo == FORMATO_BINARIO)
        {
            gravaFuncionarioBIN(f);
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
        cadastroFuncionario();
    }
}

// gravando dados do fornecedor em texto
void gravaFuncionarioTXT(Funcionario f)
{

    system("clear");

    FILE *arq;
    arq = fopen("dadosFuncionario.txt", "r");

    if (arq == NULL)
    {
        arq = fopen("dadosFuncionario.txt", "w");
    }
    fclose(arq);
    arq = fopen("dadosFuncionario.txt", "a");

    int grava = fprintf(arq, "%s;%s;%s;%.2f\n", f.nome, f.cpf, f.cargo, f.salario);

    if (grava == 0)
    {
        system("clear");
        printf("\nErro de escrita no arquivo.");
        return;
    }
    else
    {
        printf("\nDADOS DO FUNCIONÁRIO CADASTRADOS COM SUCESSO!!");
        printf("\n");
    }
    fclose(arq);
    return;
}

// gravando dados do fornecedor em binario
void gravaFuncionarioBIN(Funcionario f)
{
    FILE *arq;

    arq = fopen("dadosFuncionario.bin", "rb");
    if (arq == NULL)
    {
        arq = fopen("dadosFuncionario.bin", "wb");
        fclose(arq);
    }
    fclose(arq);
    arq = fopen("dadosFuncionario.bin", "ab+");
    if (arq == NULL)
    {
        system("clear");
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    int result = fwrite(&f, sizeof(Funcionario), 1, arq);
    if (result == 0)
    {
        printf("Erro na escrita do arquivo.\n");
    }
    else
    {
        printf("Funcionário salvo com sucesso!\n");
    }
    fclose(arq);
    return;
}

// funcao para consultar os dados de algum funcionario
void consultaFuncionario()
{

    int escolha;

    FILE *arq;
    Funcionario funcionarioAtual;

    char nomeBusca[30];
    char cpfBusca[20];
    char cargoBusca[30];
    float salarioBusca;

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

    printf("----- CONSULTA FUNCIONÁRIO -----");
    printf("\n\nOPÇÕES");
    printf("\n1 - NOME");
    printf("\n2 - CPF");
    printf("\n3 - CARGO");
    printf("\n4 - SALÁRIO");
    printf("\n5 - LISTAR TODOS OS FUNCIONÁRIOS");
    printf("\n6 - VOLTAR PARA O MENU: ");

    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    if (tipoArquivo == FORMATO_TEXTO)
    {
        // Abrir arquivo texto
        arq = fopen("dadosFuncionario.txt", "r");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo de dados texto.\n");
            printf("\nCertifique-se de que o arquivo foi criado e possui informações para serem lidas.\n");
            return;
        }

        switch (escolha)
        {
        case 1: // Busca por nome
            printf("\nDigite o nome do funcionário: ");
            scanf(" %[^\n]", nomeBusca);
            encontrado = 0;
            while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                        funcionarioAtual.cargo, &funcionarioAtual.salario) != EOF)
            {

                if (strcmp(funcionarioAtual.nome, nomeBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FUNCIONÁRIOS ENCONTRADOS -----\n");
                    }

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 2: // Busca por cpf
            printf("\nDigite o cpf do funcionário: ");
            scanf(" %[^\n]", cpfBusca);
            while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                        funcionarioAtual.cargo, &funcionarioAtual.salario) != EOF)
            {

                if (strcmp(funcionarioAtual.cpf, cpfBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FUNCIONÁRIO ENCONTRADO -----\n");

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 3: // Busca por cargo
            printf("\nDigite o cargo do funcionário: ");
            scanf(" %[^\n]", cargoBusca);
            encontrado = 0;
            while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                        funcionarioAtual.cargo, &funcionarioAtual.salario) != EOF)
            {

                if (strcmp(funcionarioAtual.cargo, cargoBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FUNCIONÁRIOS ENCONTRADOS -----\n");
                    }

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 4: // Busca por salário
            printf("\nDigite o salário do funcionário: ");
            scanf("%f", &salarioBusca);
            encontrado = 0;
            while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                        funcionarioAtual.cargo, &funcionarioAtual.salario) != EOF)
            {

                if (funcionarioAtual.salario == salarioBusca)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FUNCIONÁRIOS ENCONTRADOS -----\n");
                    }

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 5: // busca por todos os funcionarios
            system("clear");
            printf("\t\t----- LISTA DE FUNCIONÁRIOS -----\n");
            printf("\n");
            encontrado = 0;
            while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                        funcionarioAtual.cargo, &funcionarioAtual.salario) != EOF)
            {
                encontrado++;
                printf("Nome: %s\n", funcionarioAtual.nome);
                printf("CPF: %s\n", funcionarioAtual.cpf);
                printf("Cargo: %s\n", funcionarioAtual.cargo);
                printf("Salário: %.2f\n", funcionarioAtual.salario);
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
        arq = fopen("dadosFuncionario.bin", "rb");
        if (arq == NULL)
        {
            printf("\nErro ao abrir o arquivo binário.\n");
            printf("\nCertifique-se de que o arquivo foi criado e possui informações para serem lidas.\n");
            return;
        }

        switch (escolha)
        {
        case 1: // Busca por nome
            printf("\nDigite o nome do funcionário: ");
            scanf(" %[^\n]", nomeBusca);
            encontrado = 0;
            while (fread(&funcionarioAtual, sizeof(Funcionario), 1, arq) == 1)
            {

                if (strcmp(funcionarioAtual.nome, nomeBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FUNCIONÁRIOS ENCONTRADOS -----\n");
                    }

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 2: // Busca por cpf
            printf("\nDigite o CPF do funcionário: ");
            scanf(" %[^\n]", cpfBusca);
            while (fread(&funcionarioAtual, sizeof(Funcionario), 1, arq) == 1)
            {

                if (strcmp(funcionarioAtual.cpf, cpfBusca) == 0)
                {

                    system("clear");
                    printf("\n----- FUNCIONÁRIO ENCONTRADO -----\n");

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                    break;
                }
            }
            break;

        case 3: // Busca por cargo
            printf("\nDigite o cargo do funcionário: ");
            scanf(" %[^\n]", cargoBusca);
            encontrado = 0;
            while (fread(&funcionarioAtual, sizeof(Funcionario), 1, arq) == 1)
            {

                if (strcmp(funcionarioAtual.cargo, cargoBusca) == 0)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FUNCIONÁRIOS ENCONTRADOS -----\n");
                    }

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 4: // Busca por salario
            printf("\nDigite o salário do funcionário: ");
            scanf("%f", &salarioBusca);
            encontrado = 0;
            while (fread(&funcionarioAtual, sizeof(Funcionario), 1, arq) == 1)
            {

                if (funcionarioAtual.salario == salarioBusca)
                {

                    encontrado++;
                    if (encontrado == 1)
                    {
                        system("clear");
                        printf("\n----- FUNCIONÁRIOS ENCONTRADOS -----\n");
                    }

                    printf("Nome: %s\n", funcionarioAtual.nome);
                    printf("CPF: %s\n", funcionarioAtual.cpf);
                    printf("Cargo: %s\n", funcionarioAtual.cargo);
                    printf("Salário: %.2f\n", funcionarioAtual.salario);
                    printf("--------------------------------------------------------\n");
                }
            }
            printf("\n__________________");
            printf("\n\nRESULTADOS ENCONTRADOS: %d", encontrado);
            break;

        case 5: // lista todos os funcionarios disponiveis no sistema
            system("clear");
            printf("\t\t----- LISTA DE FUNCIONÁRIOS -----\n");
            printf("\n");
            encontrado = 0;
            while (fread(&funcionarioAtual, sizeof(Funcionario), 1, arq) == 1)
            {
                encontrado++;
                printf("Nome: %s\n", funcionarioAtual.nome);
                printf("CPF: %s\n", funcionarioAtual.cpf);
                printf("Cargo: %s\n", funcionarioAtual.cargo);
                printf("Salário: %.2f\n", funcionarioAtual.salario);
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
        consultaFuncionario();
    }
    else
    {
        system("clear");
        return;
    }
}

// funcao para excluir algum funcionario
void excluiFuncionario()
{

    Funcionario funcionarioAtual;
    FILE *arq, *temp;
    char excluir[5];

    char cpfBusca[20];
    int encontrado = 0;

    printf("\nDigite o CPF do funcionário que deseja excluir: ");
    scanf("%s", cpfBusca);

    if (tipoArquivo == FORMATO_TEXTO)
    {
        arq = fopen("dadosFuncionario.txt", "r");
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

        // compara o cpf fornecido com o sistema e printa o funcionario encontrado
        while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                    funcionarioAtual.cargo, &funcionarioAtual.salario) != EOF)
        {

            if (strcmp(funcionarioAtual.cpf, cpfBusca) == 0)
            {
                encontrado = 1;
                printf("\n----- FUNCIONÁRIO ENCONTRADO -----\n");

                printf("Nome: %s\n", funcionarioAtual.nome);
                printf("CPF: %s\n", funcionarioAtual.cpf);
                printf("Cargo: %s\n", funcionarioAtual.cargo);
                printf("Salário: %.2f\n", funcionarioAtual.salario);
                printf("--------------------------------------------------------\n");
                printf("\nOs dados acima se referem ao funcionário que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if (strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0)
                {
                    continue; // Ignora a gravação no arquivo temporário
                }
                else
                {
                    excluiFuncionario();
                }
                break;
            }

            // salva as alteraçoes feitas no arquivo de texto
            if (encontrado)
            {
                fprintf(temp, "%s;%s;%s;%.2f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                        funcionarioAtual.cargo, funcionarioAtual.salario);
            }
            else
            {
                fprintf(temp, "%s;%s;%s;%.2f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                        funcionarioAtual.cargo, funcionarioAtual.salario);
            }
        }
        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFuncionario.txt");
            rename("temp.txt", "dadosFuncionario.txt");
            printf("\nFuncionário excluído com sucesso!\n");
        }
        else
        {
            printf("\nFuncionário não encontrado.\n");
            remove("temp.txt");
        }
    }
    else if (tipoArquivo == FORMATO_BINARIO)
    {
        arq = fopen("dadosFuncionario.bin", "rb");
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

        // compara o cpf fornecido com o sistema e printa o funcionario encontrado
        while (fread(&funcionarioAtual, sizeof(Funcionario), 1, arq) == 1)
        {

            if (strcmp(funcionarioAtual.cpf, cpfBusca) == 0)
            {
                encontrado = 1;
                printf("\n----- FUNCIONÁRIO ENCONTRADO -----\n");

                printf("Nome: %s\n", funcionarioAtual.nome);
                printf("CPF: %s\n", funcionarioAtual.cpf);
                printf("Cargo: %s\n", funcionarioAtual.cargo);
                printf("Salário: %.2f\n", funcionarioAtual.salario);
                printf("--------------------------------------------------------\n");
                printf("\nOs dados acima se referem ao funcionário que deseja excluir? (S/N) ");
                scanf(" %[^\n]", excluir);

                system("clear");
                if (strcmp(excluir, "s") == 0 || strcmp(excluir, "S") == 0)
                {
                    continue; // Ignora a gravação no arquivo temporário
                }
                else
                {
                    excluiFuncionario();
                }
                break;
            }
        }

        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFuncionario.bin");
            rename("temp.bin", "dadosFuncionario.bin");
            printf("\nFuncionário excluído com sucesso!\n");
        }
        else
        {
            printf("\nFuncionário não encontrado.\n");
            remove("temp.bin");
        }
    }
}


// funcao para editar o funcionario desejado
void editaFuncionario()
{

    FILE *arq, *temp;
    Funcionario funcionarioAtual;

    int encontrado;
    char cpfBusca[20];

    printf("\nDigite o CPF do funcionário que deseja editar: ");
    scanf(" %[^\n]", cpfBusca);

    if (tipoArquivo == FORMATO_TEXTO)
    { // TEXTO
        arq = fopen("dadosFuncionario.txt", "r");
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

        // compara o cpf fornecido com os disponiveis no sistema e faz a alteraçao desejada
        while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                    funcionarioAtual.cargo, &funcionarioAtual.salario) != EOF)
        {

            if (strcmp(funcionarioAtual.cpf, cpfBusca) == 0)
            {

                encontrado = 1;
                printf("\nDigite os novos dados para o Funcionário:\n");
                printf("\n\nInforme o novo nome: ");
                scanf("%s", funcionarioAtual.nome);
                printf("Informe o novo CPF: ");
                scanf("%s", funcionarioAtual.cpf);
                printf("Informe o novo cargo: ");
                scanf("%s", funcionarioAtual.cargo);
                printf("Informe o novo salário: ");
                scanf("%f", &funcionarioAtual.salario);
            }
            fprintf(temp, "%s;%s;%s;%.2f\n", funcionarioAtual.nome, funcionarioAtual.cpf,
                    funcionarioAtual.cargo, funcionarioAtual.salario);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFuncionario.txt");
            rename("temp.txt", "dadosFuncionario.txt");
            printf("\nFuncionário editado com sucesso!\n");
        }
        else
        {
            printf("\nFuncionário não encontrado.\n");
            remove("temp.txt");
        }
    }
    else if (tipoArquivo == FORMATO_BINARIO)
    { // BINÁRIO
        arq = fopen("dadosFuncionario.bin", "rb");
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

        // compara o cpf fornecido com os disponiveis no sistema e faz a alteraçao desejada
        while (fread(&funcionarioAtual, sizeof(Funcionario), 1, arq) == 1)
        {

            if (strcmp(funcionarioAtual.cpf, cpfBusca) == 0)
            {

                encontrado = 1;
                printf("\nDigite os novos dados para o Funcionário:\n");
                printf("\n\nInforme o novo nome: ");
                scanf("%s", funcionarioAtual.nome);
                printf("Informe o novo CPF: ");
                scanf("%s", funcionarioAtual.cpf);
                printf("Informe o novo cargo: ");
                scanf("%s", funcionarioAtual.cargo);
                printf("Informe o novo salário: ");
                scanf("%f", &funcionarioAtual.salario);
            }

            fwrite(&funcionarioAtual, sizeof(Funcionario), 1, temp);
        }

        fclose(arq);
        fclose(temp);

        if (encontrado)
        {
            remove("dadosFuncionario.bin");
            rename("temp.bin", "dadosFuncionario.bin");
            printf("\nFuncionário editado com sucesso!\n");
        }
        else
        {
            printf("\nFuncionário não encontrado.\n");
            remove("temp.bin");
        }
    }
}