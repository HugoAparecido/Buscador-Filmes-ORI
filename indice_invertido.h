#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H

#include "arvore_b_plus.h"
#include <vector>


class IndiceInvertido {
private:
    ArvoreBPlus* arvore; // Referência para o trabalho do seu colega

    // A função de tokenizar continua igualzinha...
    std::vector<std::string> tokenizar(const std::string& texto) { /* ... */ };

public:
    // Construtor: você recebe a árvore pronta
    IndiceInvertido(ArvoreBPlus* arvore_bplus) : arvore(arvore_bplus) {}

    void construirIndice(const std::string& diretorio) {
        // ... Lógica de abrir os arquivos continua igual ...
        
        // Na hora de salvar, você delega para a árvore dele!
        for (const std::string& palavra : palavras) {
            arvore->inserir(palavra, nome_arquivo); 
        }
    }

    std::unordered_set<std::string> buscar(const std::string& termo_busca) {
        std::vector<std::string> palavras_busca = tokenizar(termo_busca);
        if (palavras_busca.empty()) return {};

        // Em vez de buscar no map, você pede para a árvore do seu colega
        std::unordered_set<std::string> resultado = arvore->buscar(palavras_busca[0]);

        // A lógica de interseção (AND) das outras palavras continua sendo SUA responsabilidade
        for (size_t i = 1; i < palavras_busca.size(); ++i) {
            std::unordered_set<std::string> arquivos_palavra_atual = arvore->buscar(palavras_busca[i]);
            // ... faz a interseção ...
        }
        return resultado;
    }
};

#endif