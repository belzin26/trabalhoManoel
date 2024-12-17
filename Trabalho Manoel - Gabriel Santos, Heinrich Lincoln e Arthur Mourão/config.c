#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int tipoArquivo;

void carregarConfiguracoes() {
    FILE *arq = fopen("configuracoes.txt", "r");
    char conf[20];
    const char *padrao = "TEXTO";

    if (arq == NULL) {
        // Cria o arquivo com a configuração padrão
        arq = fopen("configuracoes.txt", "w");
        if (arq) {
            fprintf(arq, "%s", padrao);
            fclose(arq);
        }
        tipoArquivo = FORMATO_TEXTO;
        return;
    }

    // Lê o formato do arquivo
    if (fscanf(arq, "%19s", conf) == 1) {
        if (strcmp(conf, "TEXTO") == 0) {
            tipoArquivo = FORMATO_TEXTO;
        } else if (strcmp(conf, "BINARIO") == 0) {
            tipoArquivo = FORMATO_BINARIO;
        } else {
            // Caso inválido, redefine o arquivo para o padrão
            fclose(arq);
            arq = fopen("configuracoes.txt", "w");
            if (arq) {
                fprintf(arq, "%s", padrao);
                fclose(arq);
            }
            tipoArquivo = FORMATO_TEXTO;
        }
    }
    fclose(arq);
}
