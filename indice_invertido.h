#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>
#include "arvore_b_plus.h"

class IndiceInvertido
{
private:
    ArvoreBPlus *arvore;
    std::vector<std::string> tokenizar(const std::string &texto);

public:
    IndiceInvertido(ArvoreBPlus *arvore_bplus);

    // Agora recebe o RRN numérico direto e o textão
    void adicionarRegistro(int rrn, const std::string &texto_conteudo);

    // A busca devolve um vetor de RRNs
    std::vector<int> buscar(const std::string &termo_busca);
};

#endif