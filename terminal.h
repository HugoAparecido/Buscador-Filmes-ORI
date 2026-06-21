#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <fstream>
#include "filmes.h"

// Descomente quando for integrar as estruturas:
// #include "BPlusTree.h"
// #include "indice_invertido.h"

class Terminal {
public:
    Terminal();
    ~Terminal();
    
    // O unico metodo que o main() precisa conhecer
    void iniciar();

private:
    // Ponteiros para as estruturas de busca (descomente depois)
    // ArvoreBPlus* arvore;
    // IndiceInvertido* indice;
    
    // Arquivo binario que contem os registros
    std::ifstream arquivo_dados;

    // Metodos internos de organizacao
    void exibir_menu();
    void buscar_filme();
    void inserir_filme();
    void exibir_estatisticas();
    void pausar();
};

#endif