#ifndef ARVORE_B_PLUS_H
#define ARVORE_B_PLUS_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct Node
{
    bool is_leaf;
    size_t degree;
    size_t size;
    string *item;
    std::vector<int> *rrns; // <- CORREÇÃO: Agora guarda múltiplos RRNs por palavra
    Node **children;
    Node *parent;

public:
    Node(size_t _degree);
    ~Node();
};

class ArvoreBPlus
{
private:
    Node *root;
    size_t degree;

    Node *BPlusTreeSearch(Node *node, string key);
    Node *BPlusTreeRangeSearch(Node *node, string key);
    int find_index(string *arr, string data, int len);
    string *item_insert(string *arr, string data, int len);
    string obter_prefixo_minimo(const string &esquerda, const string &direita);

    // Atualizado para lidar com vetor de RRNs
    std::vector<int> *rrn_insert(std::vector<int> *arr, int rrn, int len, string key, string *key_arr);

    Node **child_insert(Node **child_arr, Node *child, int len, int index);
    Node *child_item_insert(Node *node, string data, Node *child);
    void InsertPar(Node *par, Node *child, string data);
    void clear(Node *cursor);
    void print(Node *cursor);

public:
    ArvoreBPlus(size_t _degree);
    ~ArvoreBPlus();

    Node *getroot();
    int range_search(string start, string end, int *result_rrns, int arr_length);

    // Atualizado para o Índice Invertido
    std::unordered_set<int> buscar(string data);
    void inserir(string key, int rrn);

    void bpt_print();
};

#endif