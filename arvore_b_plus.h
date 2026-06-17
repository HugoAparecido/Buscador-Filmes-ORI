#ifndef ARVORE_B_PLUS_H
#define ARVORE_B_PLUS_H

#include <string>
#include <unordered_set>

class ArvoreBPlus
{
public:
    // Ele precisa receber a palavra (string) e o DocID (int)
    virtual void inserir(const std::string &chave, int doc_id) = 0;

    // Ele precisa devolver um conjunto de DocIDs onde a palavra aparece
    virtual std::unordered_set<int> buscar(const std::string &chave) = 0;
};
#endif