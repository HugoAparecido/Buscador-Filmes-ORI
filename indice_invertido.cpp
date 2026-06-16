#include "indice_invertido.h"

std::vector<std::string> IndiceInvertido::tokenizar(const std::string &texto) {};

IndiceInvertido::IndiceInvertido(ArvoreBPlus *arvore_bplus) : arvore(arvore_bplus) {};

void IndiceInvertido::construirIndice(const std::string &diretorio)
{
    // ... Lógica de abrir os arquivos continua igual ...

    // Na hora de salvar, você delega para a árvore dele!
    for (const std::string &palavra : palavras)
    {
        arvore->inserir(palavra, nome_arquivo);
    }
}

std::unordered_set<std::string> IndiceInvertido::buscar(const std::string &termo_busca)
{
    std::vector<std::string> palavras_busca = tokenizar(termo_busca);
    if (palavras_busca.empty())
        return {};

    // Em vez de buscar no map, você pede para a árvore do seu colega
    std::unordered_set<std::string> resultado = arvore->buscar(palavras_busca[0]);

    // A lógica de interseção (AND) das outras palavras continua sendo SUA responsabilidade
    for (size_t i = 1; i < palavras_busca.size(); ++i)
    {
        std::unordered_set<std::string> arquivos_palavra_atual = arvore->buscar(palavras_busca[i]);
        // ... faz a interseção ...
    }
    return resultado;
}
