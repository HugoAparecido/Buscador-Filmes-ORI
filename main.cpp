#include <iostream>
#include "teste_prefixo.h"
#include "terminal.h"

int main()
{
    // Executa o teste de stress de prefixos
    TestePrefixo::executar();
    std::cout << "Inicializando o Buscador de Filmes...\n";

    // Instancia o controlador principal.
    // Neste exato momento, o construtor do Terminal entra em ação e:
    // 1. Cria a Arvore B+ e o Indice Invertido na memoria.
    // 2. Abre o arquivo binario 'filmes.dat'.
    // 3. Se estiver vazio, le o 'filmes.csv' e converte os dados.
    // 4. Varre o 'filmes.dat' e carrega os prefixos na Arvore B+.
    Terminal terminal;

    // Inicia o loop interativo do menu (o programa fica rodando aqui dentro)
    terminal.iniciar();
    return 0;
}