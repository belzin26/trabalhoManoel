#ifndef CONFIG_H
#define CONFIG_H

// Define os tipos de arquivo possíveis
#define FORMATO_TEXTO 1
#define FORMATO_BINARIO 2

// Variável global para armazenar o tipo de arquivo
extern int tipoArquivo;

void carregarConfiguracoes();

#endif