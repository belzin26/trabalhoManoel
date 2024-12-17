#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cliente/cliente.h"
#include "Oficina/oficina.h"
#include "Pecas/peca.h"
#include "config.h"
#include "Servicos/servico.h"
#include "Funcionarios/funcionario.h"
#include "Veiculos/veiculo.h"
#include "Fornecedores/fornecedor.h"

void finalizar();
void configuraDadosOficina();
void cadastro();
void configuracoes();
void converteArquivos();
void consulta();
void editar();
void excluir();
void menu();

/*Converte todos os arquivos existentes para o atual formato do sistema.*/
void converteArquivos() {
    int result;
    FILE *arq, *temp;
    Oficina of;
    Cliente c;
    Peca p;
    Funcionario f;
    Veiculo v;
    Servico s;
    Fornecedor ff;
    char criarOficina[10];

    if (tipoArquivo == FORMATO_TEXTO) {
        // Arquivo texto para binário
        arq = fopen("dadosOficina.txt", "r");
        if (arq != NULL) {
            temp = fopen("dadosOficina.bin", "wb");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo binário de destino.\n");
                return;
            }
            while (fscanf(arq, "%[^;];%[^;];%[^;];%[^;];%[^;];%f", 
                        of.nome, of.cpf, of.endereco, 
                        of.telefone, of.email, &of.lucro) == 6) {
                result = fwrite(&of, sizeof(Oficina), 1, temp);
            }
            if (result) {   // Confere a escrita no novo arquivo
                printf("dadosOficina.txt --> dadosOficina.bin\n");
            } else {
                printf("Erro ao gravar em dadosOficina.bin\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosOficina.txt");
        } else { // Se não foi possível localizar o arquivo "dadosOficina.txt"
            printf("Não foi possível localizar o arquivo 'dadosOficina.txt'. Deseja cadastrar os dados da oficina? (S/N) ");
            scanf(" %[^\n]", criarOficina);
            if (strcmp(criarOficina, "S") == 0 || strcmp(criarOficina, "s") == 0) {
                // Chamar função para cadastrar oficina
                cadastraOficina();
                converteArquivos(); // Logo em seguida chama a função para seguir com a conversão de arquivos
            } else {
                printf("Não podemos seguir com a conversão. Retornando ao menu.\n");
                menu();
            }
        }

        arq = fopen("dadosClientes.txt", "r");
        if (arq != NULL) {
            temp = fopen("dadosClientes.bin", "wb");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo binário de destino.\n");
                return;
            }
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%s\n",
                            &c.codigo, c.nome,
                            c.cpf, c.endereco,
                            c.telefone, c.email) == 6) {
                result = fwrite(&c, sizeof(Cliente), 1, temp);
            }
            if (result) {
                printf("dadosClientes.txt --> dadosClientes.bin\n");
            } else {
                printf("Erro ao gravar em dadosClientes.bin\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosClientes.txt");
        }

        arq = fopen("dadosPecas.txt", "r");
        if (arq != NULL) {
            temp = fopen("dadosPecas.bin", "wb");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo binário de destino.\n");
                return;
            }
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%f;%f;%d;%d\n",
                            &p.codigo, p.descricao,
                            p.fabricante, p.fornecedor,
                            &p.preco_custo, &p.preco_venda,
                            &p.quantidade_estoque, &p.estoque_minimo) == 8){

                result = fwrite(&p, sizeof(Peca), 1, temp);
            }
            if (result) {
                printf("dadosPecas.txt --> dadosPecas.bin\n");
            } else {
                printf("Erro ao gravar em dadosPecas.bin\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosPecas.txt");
        }

        arq = fopen("dadosVeiculos.txt", "r");
        if (arq != NULL) {
            temp = fopen("dadosVeiculos.bin", "wb");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo binário de destino.\n");
                return;
            }
            while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%s\n",
                            v.placa, v.modelo, 
                            v.marca, &v.ano_fabricacao,
                            v.chassi, v.cpf) == 6){

                result = fwrite(&v, sizeof(Veiculo), 1, temp);
            }
            if (result) {
                printf("dadosVeiculos.txt --> dadosVeiculos.bin\n");
            } else {
                printf("Erro ao gravar em dadosVeiculos.bin\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosVeiculos.txt");
        }

        arq = fopen("dadosFuncionario.txt", "r");
        if (arq != NULL) {
            temp = fopen("dadosFuncionario.bin", "wb");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo binário de destino.\n");
                return;
            }
            while (fscanf(arq, "%[^;];%[^;];%[^;];%f\n",
                                f.nome, f.cpf,
                                f.cargo, &f.salario) == 4){

                result = fwrite(&f, sizeof(Funcionario), 1, temp);
            }
            if (result) {
                printf("dadosFuncionario.txt --> dadosFuncionario.bin\n");
            } else {
                printf("Erro ao gravar em dadosFuncionario.bin\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosFuncionario.txt");
        }

        arq = fopen("dadosFornecedor.txt", "r");
        if (arq != NULL) {
            temp = fopen("dadosFornecedor.bin", "wb");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo binário de destino.\n");
                return;
            }
            result = 0;
            while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s\n",
                        &ff.codigo, ff.nome_fantasia,
                        ff.razao_social, ff.inscricao_estadual,
                        ff.cpf, ff.endereco,
                        ff.telefone, ff.email) == 8){

                result = fwrite(&ff, sizeof(Fornecedor), 1, temp);
            }
            if (result) {
                printf("dadosFornecedor.txt --> dadosFornecedor.bin\n");
            } else {
                printf("Erro ao gravar em dadosFornecedor.bin\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosFornecedor.txt");
        }

        arq = fopen("dadosServicos.txt", "r");
        if (arq != NULL) {
            temp = fopen("dadosServicos.bin", "wb");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo binário de destino.\n");
                return;
            }
            result = 0;
            while (fscanf(arq, "%d;%[^;];%f;%f\n",
                    &s.codigo, s.descricao,
                    &s.comissao, &s.preco) == 4){

                result = fwrite(&s, sizeof(Servico), 1, temp);
            }
            if (result) {
                printf("dadosServicos.txt --> dadosServicos.bin\n");
            } else {
                printf("Erro ao gravar em dadosServicos.bin\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosServicos.txt");
        }

    } else if (tipoArquivo == FORMATO_BINARIO) {
        // Arquivo binário para texto
        arq = fopen("dadosOficina.bin", "rb");
        if (arq != NULL) {
            temp = fopen("dadosOficina.txt", "w");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo de texto de destino.\n");
                return;
            }
            result = 0;
            while (fread(&of, sizeof(Oficina), 1, arq) == 1) {
                result = fprintf(temp, "%s;%s;%s;%s;%s;%.2f", of.nome, of.cpf, of.endereco, of.telefone, of.email, of.lucro);
            }
            if (result) {
                printf("dadosOficina.bin --> dadosOficina.txt\n");
            } else {
                printf("Erro ao gravar em dadosOficina.txt\n");
            }
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosOficina.bin");
        } else {
            printf("Não foi possível localizar o arquivo 'dadosOficina.bin'. Cadastre uma oficina para continuar.\n");
            // cadastraOficina();
            converteArquivos();
        }

        arq = fopen("dadosClientes.bin", "rb");
        if (arq != NULL) {
            temp = fopen("dadosClientes.txt", "w");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo de texto de destino.\n");
                fclose(arq);
                return;
            }
            result = 0;
            while(fread(&c, sizeof(Cliente), 1, arq) == 1) {
                if(fprintf(temp, "%d;%s;%s;%s;%s;%s\n", 
                            c.codigo, c.nome, c.cpf, c.endereco, c.telefone, c.email) < 0) {
                    printf("Erro ao gravar registro no arquivo de texto.\n");
                    break;
                }
            }

            printf("dadosClientes.bin --> dadosClientes.txt\n");
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosClientes.bin");
        }

        arq = fopen("dadosFornecedor.bin", "rb");
        if (arq != NULL) {
            temp = fopen("dadosFornecedor.txt", "w");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo de texto de destino.\n");
                fclose(arq);
                return;
            }
            
            while(fread(&ff, sizeof(Fornecedor), 1, arq) == 1) {
                if(fprintf(arq, "%d;%s;%s;%s;%s;%s;%s;%s\n", ff.codigo, ff.nome_fantasia, ff.razao_social, ff.inscricao_estadual, ff.cpf, ff.endereco, ff.telefone, ff.email) < 0) {
                    printf("Erro ao gravar registro no arquivo de texto.\n");
                    break;
                }
            }

            printf("dadosFornecedor.bin --> dadosFornecedor.txt\n");
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosFornecedor.bin");
        }

        arq = fopen("dadosPecas.bin", "rb");
        if (arq != NULL) {
            temp = fopen("dadosPecas.txt", "w");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo de texto de destino.\n");
                fclose(arq);
                return;
            }
            
            while(fread(&p, sizeof(Peca), 1, arq) == 1) {
                if(fprintf(temp, "%d;%s;%s;%s;%f;%f;%d;%d\n", p.codigo, p.descricao, p.fabricante, p.fornecedor,
                                    p.preco_custo, p.preco_venda, p.quantidade_estoque, p.estoque_minimo) < 0) {
                    printf("Erro ao gravar registro no arquivo de texto.\n");
                    break;
                }
            }

            printf("dadosPecas.bin --> dadosPecas.txt\n");
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosPecas.bin");
        }

        arq = fopen("dadosServicos.bin", "rb");
        if (arq != NULL) {
            temp = fopen("dadosServicos.txt", "w");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo de texto de destino.\n");
                fclose(arq);
                return;
            }

            while(fread(&s, sizeof(Servico), 1, arq) == 1) {
                if(fprintf(temp, "%d;%s;%.0f;%.0f\n", s.codigo, s.descricao, s.preco, s.comissao) < 0) {
                    printf("Erro ao gravar registro no arquivo de texto.\n");
                    break;
                }
            }

            printf("dadosServicos.bin --> dadosServicos.txt\n");
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosServicos.bin");
        }

        arq = fopen("dadosFuncionario.bin", "rb");
        if (arq != NULL) {
            temp = fopen("dadosFuncionario.txt", "w");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo de texto de destino.\n");
                fclose(arq);
                return;
            }

            while(fread(&f, sizeof(Funcionario), 1, arq) == 1) {
                if(fprintf(temp, "%s;%s;%s;%.2f\n", f.nome, f.cpf, f.cargo, f.salario) < 0) {
                    printf("Erro ao gravar registro no arquivo de texto.\n");
                    break;
                }
            }

            printf("dadosFuncionario.bin --> dadosFuncionario.txt\n");
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosFuncionario.bin");
        }

        arq = fopen("dadosVeiculos.bin", "rb");
        if (arq != NULL) {
            temp = fopen("dadosVeiculos.txt", "w");
            if (temp == NULL) {
                printf("Erro ao abrir arquivo de texto de destino.\n");
                fclose(arq);
                return;
            }

            while(fread(&v, sizeof(Veiculo), 1, arq) == 1) {
                if(fprintf(temp, "%s;%s;%s;%d;%s;%s\n", v.placa, v.modelo, v.marca, v.ano_fabricacao, v.chassi, v.cpf) < 0) {
                    printf("Erro ao gravar registro no arquivo de texto.\n");
                    break;
                }
            }

            printf("dadosVeiculos.bin --> dadosVeiculos.txt\n");
            // Fecha os arquivos que foram utilizados e exclui o anterior
            fclose(arq);
            fclose(temp);
            remove("dadosVeiculos.bin");
        }
    }
    printf("\n--------------------------------------------------\n");
    printf("Conversão concluída.\n\n");
}

/*Finaliza o sistema*/
void finalizar(){
    system("clear");
    printf("\t\t----- SESSÃO ENCERRADA -----");
    printf("\n");
    exit(1);
};

/*Menu de configurações destinado a arquivos e dados da oficina*/
void configuracoes() {
    int escolha;
    char confere[2];
    FILE *arq;

    printf("----- CONFIGURAÇÕES -----\n");
    printf("1 - Tipo do arquivo do sistema\n");
    printf("2 - Visualizar/Editar dados da oficina\n");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    system("clear");

    switch (escolha) {
        case 1:
            printf("----- CONFIGURAÇÕES ATUAIS -----\n");

            if (tipoArquivo == FORMATO_TEXTO) {
                printf("\n\nConfiguração atual: TEXTO");
            } else if (tipoArquivo == FORMATO_BINARIO) {
                printf("\n\nConfiguração atual: BINÁRIO");
            } else {
                tipoArquivo = FORMATO_TEXTO;
                printf("\n\nConfiguração atual: TEXTO");
            }

            printf("\nDeseja alterar a configuração do tipo de arquivo? (S/N): ");
            scanf(" %[^\n]", confere);
            system("clear");

            if (strcmp(confere, "S") == 0 || strcmp(confere, "s") == 0) {
                system("clear");
                converteArquivos();
                if (tipoArquivo == FORMATO_TEXTO) {
                    tipoArquivo = FORMATO_BINARIO;
                    arq = fopen("configuracoes.txt", "w");
                    if (arq != NULL){
                        int result = fprintf(arq, "BINARIO");
                        if(!result){
                            system("clear");
                            printf("Houve um erro ao realizar a conversão do formato do arquivo.");
                            exit(1);
                        }
                    }
                    fclose(arq);
                } else if (tipoArquivo == FORMATO_BINARIO) {
                    tipoArquivo = FORMATO_TEXTO;
                    arq = fopen("configuracoes.txt", "w");
                    if (arq != NULL){
                        int result = fprintf(arq, "TEXTO");
                        if(!result){
                            system("clear");
                            printf("Houve um erro ao realizar a conversão do formato do arquivo.");
                            exit(1);
                        }
                    }
                    fclose(arq);
                }
                menu(); // Chama o menu novamente
            } else {
                system("clear");
                menu(); // Chama o menu sem alterar a configuração atual
            }
            break;
        
        case 2:
            configuraDadosOficina(); // Chama a função para editar os dados da oficina
            break;

        default:
            break;
    }

    menu(); // Retorna ao menu principal ao final da execução
}

/*Destinada a selecionar a qual função de cadastro o usuário deseja*/
void cadastro(){
    int y;    

    printf("\n----- CADASTRO -----");
    printf("\n1 - Cliente");
    printf("\n2 - Funcionário");
    printf("\n3 - Peça");
    printf("\n4 - Fornecedor");
    printf("\n5 - Serviço");
    printf("\n6 - Veículos\n");
    printf("\n7 - RETORNAR PARA O MENU");

    printf("\n\nEscolha: ");
    scanf("%d", &y);

    system("clear");

    switch (y){
    case 1:
        cadastroCliente();
        break;
    
    case 2:
        cadastroFuncionario();
        break;
    
    case 3:
        cadastroPeca();
        break;

    case 4:
        cadastroFornecedor();
        break;
    
    case 5:
        cadastroServico();
        break;

    case 6:
        cadastroVeiculo();
        break;

    case 7:
        menu();
        break;
        
    default:
        printf("\nOpção inválida. Tente novamente.");
        cadastro();
        break;
    }
    menu();
};

/*Menu de escolha para edição*/
void editar(){
    int escolha;
    printf("----- EDITAR -----\n");
    printf("\n1 - Cliente");
    printf("\n2 - Funcionário");
    printf("\n3 - Peça");
    printf("\n4 - Fornecedor");
    printf("\n5 - Serviço");
    printf("\n6 - Veículos");
    printf("\n7 - RETORNAR PARA O MENU");

    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    system("clear");
    switch (escolha){
        case 1:
            editaCliente();
            break;
        
        case 2:
            editaFuncionario();
            break;
        
        case 3:
            editaPeca();
            break;
        
        case 4:
            editaFornecedor();
            break;
        
        case 5:
            editaServico();
            break;

        case 6:
            editaVeiculo();
            break;
        
        case 7:
            menu();
            break;

        default:
            break;
    }
    menu();
}

/*Menu de exclusão*/
void excluir(){
    int escolha;

    printf("----- EXCLUIR -----\n");
    printf("\n1 - Cliente");
    printf("\n2 - Funcionário");
    printf("\n3 - Peça");
    printf("\n4 - Fornecedor");
    printf("\n5 - Serviço");
    printf("\n6 - Veículos");
    printf("\n7 - RETORNAR PARA O MENU");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    system("clear");
    switch (escolha){
    case 1:
        excluiCliente();
        break;
    
    case 2:
        excluiFuncionario();
        break;
    
    case 3:
        excluiPeca();
        break;
    
    case 4:
        excluiFornecedor();
        break;
    
    case 5:
        excluiServico();
        break;

    case 6:
        excluiVeiculo();
        break;
    
    case 7:
        menu();
        break;

    default:
        break;
    }
    menu();
}

/*Mostra os dados da oficina cadastrados atualmente, possibilitando editar os dados atuais.*/
void configuraDadosOficina() {
    Oficina ofic;
    FILE *arq; 
    char editar[5];


    // Tentar abrir o arquivo texto
    if (tipoArquivo == FORMATO_TEXTO){
        arq = fopen("dadosOficina.txt", "r"); // Tenta abrir o arquio em texto
        if (arq != NULL) { // Se deu certo a abertura o arquivo
            while (fscanf(arq, "%[^;];%[^;];%[^;];%[^;];%[^;];%f", 
                        ofic.nome, ofic.cpf, ofic.endereco, 
                        ofic.telefone, ofic.email, &ofic.lucro) != EOF) {
                printf("----- DADOS CADASTRADOS ATUALMENTE -----\n");
                printf("\nNome: %s", ofic.nome);
                printf("\nCPF/CNPJ: %.s", ofic.cpf);
                printf("\nEndereço: %s", ofic.endereco);
                printf("\nTelefone: %s", ofic.telefone);
                printf("\nE-mail: %s", ofic.email);
                printf("\nPercentual de lucro: %.2f\n", ofic.lucro);

                printf("\n\nDeseja editar os dados acima? (S/N) ");
                scanf(" %[^\n]", editar);
                system("clear");
                fclose(arq);

                if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0) {
                    editarOficina();
                }else{
                    system("clear");
                    printf("Certo, retornando ao menu.\n\n");
                    menu();
                }
            }
            fclose(arq);
        } else {
            arq = fopen("dadosOficina.bin", "rb"); // Tenta buscar pelo arquivo em binário
            if (arq != NULL) { // Se encontrou o arquivo em binário
                printf("O sistema está configurado para TEXTO, mas houve um erro em abrir o arquivo texto.");
                printf("\nNeste caso, executamos a abertura do arquivo em binário para evitar possíveis erros.");
                printf("\n\n");

                while (fread(&ofic, sizeof(Oficina), 1, arq)) {
                    printf("----- DADOS CADASTRADOS ATUALMENTE -----\n");
                    printf("\nNome: %s", ofic.nome);
                    printf("\nCPF/CNPJ: %s", ofic.cpf);
                    printf("\nEndereço: %s", ofic.endereco);
                    printf("\nTelefone: %s", ofic.telefone);
                    printf("\nE-mail: %s", ofic.email);
                    printf("\nPercentual de lucro: %.2f", ofic.lucro);

                    printf("\n\nDeseja editar os dados acima? (S/N) ");
                    scanf(" %[^\n]", editar);
                    fclose(arq);
                    system("clear");
                    if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0) {
                        editarOficina();
                    }else{
                        printf("Certo, retornando ao menu.");
                        printf("\n\n");
                        menu();
                    }
                }
                fclose(arq);
            } else {
                printf("\nNenhum dado de oficina encontrado.\n");
                printf("Deseja cadastrar uma nova oficina? (S/N) ");
                scanf(" %[^\n]", editar);
                if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0) {
                    editarOficina();
                }
            }
        }
        // Abre o arquivo Binário
    }else if(tipoArquivo == FORMATO_BINARIO){
        arq = fopen("dadosOficina.bin", "rb"); // Tenta abrir o arquivo binário
            if (arq != NULL) { // Se deu certo a abertura do arquivo
                while (fread(&ofic, sizeof(Oficina), 1, arq) == 1) {
                    printf("----- DADOS CADASTRADOS ATUALMENTE -----\n");
                    printf("\nNome: %s", ofic.nome);
                    printf("\nCPF/CNPJ: %s", ofic.cpf);
                    printf("\nEndereço: %s", ofic.endereco);
                    printf("\nTelefone: %s", ofic.telefone);
                    printf("\nE-mail: %s", ofic.email);
                    printf("\nPercentual de lucro: %.2f", ofic.lucro);

                    printf("\n\nDeseja editar os dados acima? (S/N) ");
                    scanf(" %[^\n]", editar);
                    fclose(arq);

                    if (strcmp(editar, "S") == 0 || strcmp(editar, "s") == 0) {
                        editarOficina();
                    }else{
                        system("clear");
                        printf("Certo, retornando ao menu.");
                        printf("\n\n");
                        menu();
                    }
                }
                fclose(arq);
            }
    }
}

/*Menu principal do sistema*/
void menu() {
    int x;

    if(tipoArquivo == FORMATO_TEXTO){
        printf("CONFIGURAÇÕES ATUAIS: TEXTO\n\n");
    }else if(tipoArquivo == FORMATO_BINARIO){
        printf("CONFIGURAÇÕES ATUAIS: BINÁRIO\n\n");
    }
    printf("----- MENU -----\n");
    printf("1 - Cadastro\n");
    printf("2 - Consulta\n");
    printf("3 - Editar\n");
    printf("4 - Excluir\n");
    printf("5 - Configurações\n");
    printf("6 - Sair\n");
    printf("\nEscolha: ");
    scanf("%d", &x);
    system("clear");

    switch (x) {
        case 1:
            cadastro();
            break;
        case 2:
            consulta();
            break;
        case 3:
            editar();
            break;
        case 4:
            excluir();
            break;
        case 5:
            configuracoes();
            break;
        case 6:
            finalizar();
            break;
            
        default:
            break;
    }
}

/*Menu de consulta, solicita a entrada de um número inteiro. (não como parâmetro)*/
void consulta(){
    int y;    
    system("clear");
    printf("----- CONSULTA -----\n");
    printf("\n1 - Cliente");
    printf("\n2 - Funcionário");
    printf("\n3 - Peça");
    printf("\n4 - Fornecedor");
    printf("\n5 - Serviço");
    printf("\n6 - Veículos\n");

    printf("\n7 - VOLTAR PARA O MENU");

    printf("\n\nEscolha: ");
    scanf("%d", &y);

    system("clear");

    switch (y){
    case 1:
        consultaCliente();
        break;
    
    case 2:
        consultaFuncionario();
        break;
    
    case 3:
        consultaPeca();
        break;
    
    case 4:
        consultaFornecedor();
        break;
        
    case 5:
        consultaServico();
        break;

    case 6:
        consultaVeiculo();
        break;
    
    case 7:
        menu();
        break;
        
    default:
        printf("Opção inválida. Tente novamente.");
        consulta();
        break;
    }
    menu();
};

int main(){
    system("clear");
    carregarConfiguracoes();
    cadastraOficina();
    menu();
};