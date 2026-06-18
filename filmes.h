#ifndef FILME_H
#define FILME_H

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

// Tamanhos fixos dos campos de texto, em bytes, com folga sobre o dataset atual.
// Registros de tamanho fixo permitem calcular o offset de cada filme pelo RRN
// (relative record number) e ler/gravar direto no disco, o que e necessario
// para indexar com a Arvore B+ e com o indice invertido.
constexpr int TAM_ID            = 12;
constexpr int TAM_TITULO        = 256;
constexpr int TAM_CLASSIFICACAO = 16;
constexpr int TAM_DIRETOR       = 128;
constexpr int TAM_GENERO        = 192;

// Valor usado quando um campo monetario ou a nota nao existe no dataset.
constexpr long long DESCONHECIDO = -1;

class Filme{
public:
    Filme(){
        zerar();
    }

    // Preenche o registro a partir dos campos ja separados de uma linha do CSV.
    // Os indices seguem o cabecalho do arquivo do IMDb.
    void carregar_de_csv(const std::vector<std::string>& campos){
        zerar();
        if(campos.size() < 16) return;

        copia_texto(id, campos[0], TAM_ID);
        copia_texto(titulo, campos[1], TAM_TITULO);
        ano = texto_para_inteiro(campos[3], 0);
        duracao_min = duracao_para_minutos(campos[4]);
        copia_texto(classificacao, campos[5], TAM_CLASSIFICACAO);
        nota_imdb = texto_para_real(campos[6], static_cast<float>(DESCONHECIDO));
        orcamento = texto_para_longo(campos[8], DESCONHECIDO);
        bilheteria_mundial = texto_para_longo(campos[9], DESCONHECIDO);
        copia_texto(diretor, campos[12], TAM_DIRETOR);
        copia_texto(genero, campos[15], TAM_GENERO);
    }

    // Grava o registro inteiro na posicao atual do arquivo binario.
    void gravar(std::ostream& arquivo) const{
        arquivo.write(reinterpret_cast<const char*>(this), sizeof(Filme));
    }

    // Le um registro da posicao atual. Retorna false ao chegar no fim do arquivo.
    bool ler(std::istream& arquivo){
        arquivo.read(reinterpret_cast<char*>(this), sizeof(Filme));
        return arquivo.gcount() == static_cast<std::streamsize>(sizeof(Filme));
    }

    // Le o registro de numero rrn com acesso direto, usando o tamanho fixo.
    bool ler_rrn(std::istream& arquivo, long long rrn){
        arquivo.seekg(rrn * static_cast<long long>(sizeof(Filme)), std::ios::beg);
        return ler(arquivo);
    }

    // Getters usados pelos indices e pela camada de busca.
    const char* obter_id() const{ return id; }
    const char* obter_titulo() const{ return titulo; }
    const char* obter_classificacao() const{ return classificacao; }
    const char* obter_diretor() const{ return diretor; }
    const char* obter_genero() const{ return genero; }
    int obter_duracao_min() const{ return duracao_min; }
    float obter_nota() const{ return nota_imdb; }
    long long obter_orcamento() const{ return orcamento; }
    long long obter_bilheteria_mundial() const{ return bilheteria_mundial; }
    int obter_ano() const{ return ano; }

    // Tamanho do registro em disco, util para o gerenciador de armazenamento.
    static constexpr long long tamanho_registro(){
        return sizeof(Filme);
    }

    void imprimir() const{
        std::cout << id << " | " << titulo << " (" << ano << ")"
                  << " | " << classificacao
                  << " | nota " << nota_imdb
                  << " | " << duracao_min << " min\n"
                  << "  genero: " << genero << "\n"
                  << "  diretor: " << diretor << "\n";
    }

private:
    // Campos numericos.
    int ano;
    int duracao_min;            // duracao convertida para minutos
    float nota_imdb;            // nota do IMDb, -1 quando ausente
    long long orcamento;        // -1 quando ausente
    long long bilheteria_mundial;

    // Campos de texto com tamanho fixo.
    char id[TAM_ID];
    char titulo[TAM_TITULO];
    char classificacao[TAM_CLASSIFICACAO];
    char diretor[TAM_DIRETOR];
    char genero[TAM_GENERO];

    // Zera todos os campos para garantir registros consistentes em disco.
    void zerar(){
        std::memset(this, 0, sizeof(Filme));
        nota_imdb = static_cast<float>(DESCONHECIDO);
        orcamento = DESCONHECIDO;
        bilheteria_mundial = DESCONHECIDO;
    }

    // Copia o texto truncando no limite do campo e garantindo o terminador nulo.
    static void copia_texto(char* destino, const std::string& origem, int tamanho){
        int n = static_cast<int>(origem.size());
        if(n > tamanho - 1) n = tamanho - 1;
        std::memcpy(destino, origem.data(), n);
        destino[n] = '\0';
    }

    static int texto_para_inteiro(const std::string& texto, int padrao){
        if(texto.empty()) return padrao;
        return std::atoi(texto.c_str());
    }

    static long long texto_para_longo(const std::string& texto, long long padrao){
        if(texto.empty()) return padrao;
        return std::atoll(texto.c_str());
    }

    static float texto_para_real(const std::string& texto, float padrao){
        if(texto.empty()) return padrao;
        return static_cast<float>(std::atof(texto.c_str()));
    }

    // Converte uma duracao no formato "1h 38m" para minutos inteiros.
    static int duracao_para_minutos(const std::string& texto){
        int horas = 0;
        int minutos = 0;
        int numero = 0;
        for(size_t i = 0; i < texto.size(); i++){
            char c = texto[i];
            if(c >= '0' && c <= '9'){
                numero = numero * 10 + (c - '0');
            }else if(c == 'h'){
                horas = numero;
                numero = 0;
            }else if(c == 'm'){
                minutos = numero;
                numero = 0;
            }
        }
        return horas * 60 + minutos;
    }
};

#endif