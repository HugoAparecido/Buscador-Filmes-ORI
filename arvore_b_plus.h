#ifndef BPlusTree_H
#define BPlusTree_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
    bool is_leaf;
    size_t degree;   // maximum number of children
    size_t size;     // current number of keys
    string* item;    // Film names (Keys)
    int* rrns;       // Relative Record Numbers (Payloads, leaf level only)
    Node** children;
    Node* parent;

public:
    Node(size_t _degree);
    ~Node();
};

class BPlusTree {
private:
    Node* root;
    size_t degree;

    Node* BPlusTreeSearch(Node* node, string key);
    Node* BPlusTreeRangeSearch(Node* node, string key);
    int find_index(string* arr, string data, int len);
    string* item_insert(string* arr, string data, int len);
    int* rrn_insert(int* arr, int rrn, int len, string key, string* key_arr);
    Node** child_insert(Node** child_arr, Node* child, int len, int index);
    Node* child_item_insert(Node* node, string data, Node* child);
    void InsertPar(Node* par, Node* child, string data);
    void clear(Node* cursor);
    void print(Node* cursor);

public:
    BPlusTree(size_t _degree);
    ~BPlusTree();

    Node* getroot();
    int range_search(string start, string end, int* result_rrns, int arr_length);
    bool search(string data, int& found_rrn);
    void insert(string key, int rrn);
    void bpt_print();
};

#endif
