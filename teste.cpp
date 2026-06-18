#include <iostream>
#include "arvore_b_plus.h"
#include "indice_invertido.h"

using namespace std;

int main() {
    cout << "--- TESTANDO A ARVORE B+ E INDICE INVERTIDO ---\n";

    // Cria a árvore com grau 3 (no máximo 3 filhos por nó)
    ArvoreBPlus arvore(3);
    IndiceInvertido indice(&arvore);

    // Simulando a inserção de filmes fictícios (RRN, Texto)
    cout << "Inserindo registros...\n";
    indice.adicionarRegistro(1, "O Senhor dos Aneis Fantasia 2001");
    indice.adicionarRegistro(2, "Guerra nas Estrelas Sci-Fi 1977");
    indice.adicionarRegistro(3, "Guerra dos Mundos Sci-Fi 2005");

    // Testando a busca pela palavra "guerra"
    cout << "\nBuscando pela palavra: 'guerra'\n";
    vector<int> resultados = indice.buscar("guerra");

    if (resultados.empty()) {
        cout << "Nenhum filme encontrado.\n";
    } else {
        cout << "Encontrado nos RRNs: ";
        for (int rrn : resultados) {
            cout << rrn << " ";
        }
        cout << "\n";
    }

    // Você também pode imprimir a árvore inteira para ver a estrutura interna
    cout << "\nEstrutura interna da Arvore B+:\n";
    arvore.bpt_print();

    return 0;
}