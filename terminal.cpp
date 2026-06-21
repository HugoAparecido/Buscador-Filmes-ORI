#include "terminal.h"
#include <iostream>
#include <limits>

using namespace std;

Terminal::Terminal()
{
    // 1. Inicialize as estruturas de indexacao aqui no futuro
    arvore = new ArvoreBPlus(50); // Grau da arvore
    indice = new IndiceInvertido(arvore);

    if (arquivo_dados.tellg() == 0)
    {
        cout << "[Sistema] Arquivo de dados vazio.\n";
        // Certifique-se de que o arquivo .csv esta na mesma pasta do executável
        importar_csv_para_dat("filmes.csv");
    }

    // Alimenta a árvore com os filmes que estão no disco
    // carregar_indice_do_disco();
}

Terminal::~Terminal()
{
    if (arquivo_dados.is_open())
    {
        arquivo_dados.close();
    }
    // Liberar memoria das estruturas depois
    // delete indice;
    // delete arvore;
}

void Terminal::iniciar()
{
    int opcao = -1;

    while (opcao != 0)
    {
        exibir_menu();

        // Seguranca: se o usuario digitar uma letra em vez de numero
        if (!(cin >> opcao))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        }

        // Limpa o buffer do '\n' para o getline funcionar corretamente depois
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao)
        {
        case 1:
            buscar_filme();
            break;
        case 2:
            inserir_filme();
            break;
        case 3:
            exibir_estatisticas();
            break;
        case 0:
            cout << "\nEncerrando o buscador. Ate logo!\n";
            break;
        default:
            cout << "\n[!] Opcao invalida. Tente novamente.\n";
            pausar();
            break;
        }
    }
}

void Terminal::exibir_menu()
{
    cout << "\n=========================================\n";
    cout << "        BUSCADOR DE FILMES - ORI         \n";
    cout << "=========================================\n";
    cout << "[1] Buscar filme por palavras-chave\n";
    cout << "[2] Inserir novo filme (Teste)\n";
    cout << "[3] Estatisticas do Indice\n";
    cout << "[0] Sair\n";
    cout << "=========================================\n";
    cout << "Escolha uma opcao: ";
}

void Terminal::buscar_filme()
{
    cout << "\n>>> Digite os termos da busca (ex: star wars): ";
    string termo_busca;
    getline(cin, termo_busca);

    cout << "\nBuscando por: '" << termo_busca << "'...\n\n";

    // --- INTEGRACAO COM O INDICE INVERTIDO ---
    /*
    vector<string> resultados = indice->buscar(termo_busca);

    if (resultados.empty()) {
        cout << "Nenhum filme encontrado para esses termos.\n";
    } else {
        cout << "Encontrados " << resultados.size() << " filmes:\n\n";

        for (const string& doc_id_str : resultados) {
            // Converte o ID retornado pelo indice em RRN numérico
            long long rrn = stoll(doc_id_str);

            Filme f;
            if (f.ler_rrn(arquivo_dados, rrn)) {
                f.imprimir(); // Usa o metodo imprimir() que vcs ja criaram em filmes.h
                cout << "-----------------------------------------\n";
            }
        }
    }
    */

    // Remova a linha abaixo quando integrar o codigo acima
    cout << "[Em construcao: A integracao com a Arvore B+ sera ativada aqui]\n";

    pausar();
}

void Terminal::inserir_filme()
{
    cout << "\n>>> Funcionalidade de insercao manual em construcao...\n";
    // Aqui voce pode futuramente fazer um cin para cada campo (Titulo, Ano, etc.),
    // gravar no .dat usando f.gravar() e adicionar no indice_invertido.
    pausar();
}

void Terminal::exibir_estatisticas()
{
    cout << "\n>>> Estatisticas do Sistema:\n";
    cout << "- Arquivo de dados conectado: " << (arquivo_dados.is_open() ? "Sim" : "Nao") << "\n";
    // cout << "- Total de termos no indice: " << indice->total_termos() << "\n";
    pausar();
}

void Terminal::pausar()
{
    cout << "\nPressione Enter para continuar...";
    string temp;
    getline(cin, temp);
}

vector<string> Terminal::quebrar_linha_csv(const string &linha)
{
    vector<string> campos;
    string campo_atual = "";
    bool dentro_aspas = false;

    for (char c : linha)
    {
        if (c == '"')
        {
            dentro_aspas = !dentro_aspas; // Alterna o estado ao encontrar aspas
        }
        else if (c == ',' && !dentro_aspas)
        {
            campos.push_back(campo_atual);
            campo_atual.clear();
        }
        else
        {
            campo_atual += c;
        }
    }
    campos.push_back(campo_atual); // Adiciona o ultimo campo
    return campos;
}

void Terminal::importar_csv_para_dat(const string &caminho_csv)
{
    ifstream arquivo_csv(caminho_csv);
    if (!arquivo_csv.is_open())
    {
        cout << "[!] Erro: Nao foi possivel abrir o arquivo " << caminho_csv << "\n";
        return;
    }

    cout << "[Sistema] Gerando arquivo binario a partir do CSV...\n";

    string linha;
    // Pula a primeira linha (cabeçalho do CSV)
    getline(arquivo_csv, linha);

    Filme f;
    int filmes_importados = 0;

    // Posiciona o ponteiro de gravação do arquivo binário no final
    arquivo_dados.clear();
    arquivo_dados.seekp(0, ios::end);

    while (getline(arquivo_csv, linha))
    {
        vector<string> campos = quebrar_linha_csv(linha);

        // Usa o SEU método para preencher o objeto
        f.carregar_de_csv(campos);

        // Grava o objeto binário direto no disco
        f.gravar(arquivo_dados);
        filmes_importados++;
    }

    arquivo_csv.close();
    cout << "[Sistema] Sucesso! " << filmes_importados << " filmes convertidos para .dat.\n";
}