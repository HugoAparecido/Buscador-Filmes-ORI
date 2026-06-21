#ifndef TESTE_PREFIXO_H
#define TESTE_PREFIXO_H

#include <iostream>
#include "arvore_b_plus.h"

class TestePrefixo
{
public:
    static void executar()
    {
        std::cout << "\n==============================================\n";
        std::cout << "      TESTE DE STRESS: PREFIXO SIMPLES\n";
        std::cout << "==============================================\n";

        // Grau 3: Os nós suportam no máximo 2 palavras.
        // A terceira palavra sempre causará um split (divisão).
        ArvoreBPlus arvore(3);

        std::cout << "[+] Inserindo chaves com radicais idênticos...\n";

        arvore.inserir("cachoeira", 1);
        arvore.inserir("cachorro", 2);

        // Aqui o nó vai lotar e dividir!
        // A árvore terá que achar o prefixo para separar "cachoeira" e "cachorro".
        arvore.inserir("cacto", 3);

        arvore.inserir("cadeira", 4);
        arvore.inserir("cadeado", 5);

        // Testando outra família de palavras
        arvore.inserir("guerra", 6);
        arvore.inserir("guerreiro", 7);
        arvore.inserir("guerrilha", 8);

        std::cout << "\n[!] IMPRIMINDO A ESTRUTURA DA ARVORE:\n";
        std::cout << "----------------------------------------------\n";
        arvore.bpt_print();
        std::cout << "----------------------------------------------\n";

        std::cout << "COMO LER O RESULTADO:\n";
        std::cout << "1. Os nós folhas (que possuem os RRNs entre parênteses) devem conter a PALAVRA INTEIRA.\n";
        std::cout << "2. Os nós internos (sem parênteses) devem conter apenas os PREFIXOS MÍNIMOS (ex: 'cact', 'cad', 'guerre').\n";
        std::cout << "==============================================\n\n";
    }
};

#endif