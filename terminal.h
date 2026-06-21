#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <fstream>
#include <vector>

#include "filmes.h"
#include "arvore_b_plus.h"
#include "indice_invertido.h"

class Terminal
{
public:
    Terminal();
    ~Terminal();

    // O unico metodo que o main() precisa conhecer
    void iniciar();

private:
    // Ponteiros para as estruturas de busca (descomente depois)
    ArvoreBPlus *arvore;
    IndiceInvertido *indice;

    // Arquivo binario que contem os registros
    std::fstream arquivo_dados;

    // Metodos internos de organizacao
    void exibir_menu();
    void buscar_filme();
    void inserir_filme();
    void exibir_estatisticas();
    void pausar();

    // Le o CSV e gera o arquivo filmes.dat
    void importar_csv_para_dat(const std::string &caminho_csv);

    // Funcao auxiliar para separar a linha do CSV lidando com aspas duplas
    std::vector<std::string> quebrar_linha_csv(const std::string &linha);
};

#endif