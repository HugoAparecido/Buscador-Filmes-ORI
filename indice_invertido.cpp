#include "indice_invertido.h"

IndiceInvertido::IndiceInvertido(ArvoreBPlus *arvore_bplus)
{
    this->arvore = arvore_bplus;
    this->proximo_doc_id = 1; // Começamos do ID 1
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

void IndiceInvertido::adicionarRegistro(const std::string &identificador_registro, const std::string &texto_conteudo)
{
    // 1. Gera um ID numérico para este registro
    int doc_id = proximo_doc_id++;

    // 2. Salva o mapeamento (Ex: ID 1 -> "Cliente_João")
    mapa_documentos[doc_id] = identificador_registro;

    // 3. Limpa e quebra o texto em palavras
    std::vector<std::string> palavras = tokenizar(texto_conteudo);

    // 4. Manda para a Árvore B+ do seu colega
    for (const std::string &palavra : palavras)
    {
        arvore->inserir(palavra, doc_id);
    }
}

std::vector<std::string> IndiceInvertido::buscar(const std::string &termo_busca)
{
    std::vector<std::string> palavras_busca = tokenizar(termo_busca);
    std::vector<std::string> resultados_finais;

    if (palavras_busca.empty())
        return resultados_finais;

    // 1. Pede para a Árvore os IDs da primeira palavra
    std::unordered_set<int> ids_resultado = arvore->buscar(palavras_busca[0]);

    // 2. Faz a interseção com as outras palavras da busca
    for (size_t i = 1; i < palavras_busca.size(); ++i)
    {
        if (ids_resultado.empty())
            break; // Otimização rápida

        std::unordered_set<int> ids_palavra_atual = arvore->buscar(palavras_busca[i]);
        std::unordered_set<int> intersecao;

        for (int id : ids_resultado)
        {
            if (ids_palavra_atual.find(id) != ids_palavra_atual.end())
            {
                intersecao.insert(id);
            }
        }
        ids_resultado = intersecao;
    }

    // 3. Traduz os IDs que sobraram de volta para os identificadores originais
    for (int id : ids_resultado)
    {
        resultados_finais.push_back(mapa_documentos[id]);
    }

    return resultados_finais;
}
