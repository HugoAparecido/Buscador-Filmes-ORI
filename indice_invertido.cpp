#include "indice_invertido.h"

IndiceInvertido::IndiceInvertido(ArvoreBPlus *arvore_bplus)
{
    this->arvore = arvore_bplus;
}

std::vector<std::string> IndiceInvertido::tokenizar(const std::string &texto)
{
    std::vector<std::string> tokens;
    std::string palavra_atual;

    for (char c : texto)
    {
        if (std::isalnum(static_cast<unsigned char>(c)))
        {
            palavra_atual += std::tolower(static_cast<unsigned char>(c));
        }
        else if (!palavra_atual.empty())
        {
            tokens.push_back(palavra_atual);
            palavra_atual.clear();
        }
    }
    if (!palavra_atual.empty())
    {
        tokens.push_back(palavra_atual);
    }
    return tokens;
}

void IndiceInvertido::adicionarRegistro(int rrn, const std::string &texto_conteudo)
{
    // Limpa e quebra o texto em palavras
    std::vector<std::string> palavras = tokenizar(texto_conteudo);

    // Manda para a Arvore B+ passando a palavra e o RRN do disco
    for (const std::string &palavra : palavras)
    {
        arvore->inserir(palavra, rrn);
    }
}

std::vector<int> IndiceInvertido::buscar(const std::string &termo_busca)
{
    std::vector<std::string> palavras_busca = tokenizar(termo_busca);
    std::vector<int> resultados_finais;

    if (palavras_busca.empty())
        return resultados_finais;

    // Pede para a Arvore os RRNs da primeira palavra
    std::unordered_set<int> ids_resultado = arvore->buscar(palavras_busca[0]);

    // Intersecao (Early Exit mantido)
    for (size_t i = 1; i < palavras_busca.size(); ++i)
    {
        if (ids_resultado.empty())
            break; 

        std::unordered_set<int> ids_palavra_atual = arvore->buscar(palavras_busca[i]);
        std::unordered_set<int> intersecao;

        for (int rrn : ids_resultado)
        {
            if (ids_palavra_atual.find(rrn) != ids_palavra_atual.end())
            {
                intersecao.insert(rrn);
            }
        }
        ids_resultado = intersecao;
    }

    // Copia os RRNs encontrados para o vetor final
    for (int rrn : ids_resultado)
    {
        resultados_finais.push_back(rrn);
    }

    return resultados_finais;
}