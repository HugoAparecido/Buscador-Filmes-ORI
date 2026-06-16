#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include "arvore_b_plus.h"

class IndiceInvertido
{
private:
    ArvoreBPlus *arvore; // Referência para o trabalho do seu colega

    // A função de tokenizar continua igualzinha...
    std::unordered_map<int, std::string> mapa_documentos;
    int proximo_doc_id; // Gera IDs únicos
    std::vector<std::string> tokenizar(const std::string &texto);

public:
    // Construtor: você recebe a árvore pronta
    IndiceInvertido(ArvoreBPlus *arvore_bplus);

    void adicionarRegistro(const std::string &identificador_registro, const std::string &texto_conteudo);

    std::vector<std::string> buscar(const std::string &termo_busca);
};

#endif