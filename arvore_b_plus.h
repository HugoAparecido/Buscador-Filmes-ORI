#ifndef ARVORE_B_PLUS_H
#define ARVORE_B_PLUS_H

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
    Node(size_t _degree) {
        this->is_leaf = false;
        this->degree = _degree;
        this->size = 0;

        this->item = new string[degree - 1];
        for (int i = 0; i < degree - 1; i++) {
            this->item[i] = "";
        }

        this->rrns = new int[degree - 1];
        for (int i = 0; i < degree - 1; i++) {
            this->rrns[i] = -1; // -1 means unassigned/empty
        }

        this->children = new Node*[degree];
        for (int i = 0; i < degree; i++) {
            this->children[i] = nullptr;
        }

        this->parent = nullptr;
    }

    ~Node() {
        delete[] item;
        delete[] rrns;
        delete[] children;
    }
};

class BPlusTree {
    Node* root;
    size_t degree;

public:
    BPlusTree(size_t _degree) {
        this->root = nullptr;
        this->degree = _degree;
    }
    
    ~BPlusTree() {
        clear(this->root);
    }

    Node* getroot() {
        return this->root;
    }

    Node* BPlusTreeSearch(Node* node, string key) {
        if (node == nullptr) return nullptr;
        Node* cursor = node;
        while (!cursor->is_leaf) {
            for (int i = 0; i < cursor->size; i++) {
                if (key < cursor->item[i]) {
                    cursor = cursor->children[i];
                    break;
                }
                if (i == (cursor->size) - 1) {
                    cursor = cursor->children[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->item[i] == key) return cursor;
        }
        return nullptr;
    }

    Node* BPlusTreeRangeSearch(Node* node, string key) {
        if (node == nullptr) return nullptr;
        Node* cursor = node;
        while (!cursor->is_leaf) {
            for (int i = 0; i < cursor->size; i++) {
                if (key < cursor->item[i]) {
                    cursor = cursor->children[i];
                    break;
                }
                if (i == (cursor->size) - 1) {
                    cursor = cursor->children[i + 1];
                    break;
                }
            }
        }
        return cursor;
    }

    int range_search(string start, string end, int* result_rrns, int arr_length) {
        int index = 0;
        Node* start_node = BPlusTreeRangeSearch(this->root, start);
        Node* cursor = start_node;
        if (cursor == nullptr || cursor->size == 0) return 0;

        string temp = cursor->item[0];

        while (temp <= end) {
            if (cursor == nullptr) break;
            for (int i = 0; i < cursor->size; i++) {
                temp = cursor->item[i];
                if ((temp >= start) && (temp <= end)) {
                    if (index >= arr_length) return index;
                    result_rrns[index] = cursor->rrns[i]; // Accumulate mapped RRN identifiers
                    index++;
                }
            }
            cursor = cursor->children[cursor->size];
        }
        return index;
    }

    bool search(string data, int& found_rrn) {
        Node* res = BPlusTreeSearch(this->root, data);
        if (res != nullptr) {
            for (int i = 0; i < res->size; i++) {
                if (res->item[i] == data) {
                    found_rrn = res->rrns[i];
                    return true;
                }
            }
        }
        return false;
    }

    int find_index(string* arr, string data, int len) {
        for (int i = 0; i < len; i++) {
            if (data < arr[i]) return i;
        }
        return len;
    }

    string* item_insert(string* arr, string data, int len) {
        int index = find_index(arr, data, len);
        for (int i = len; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = data;
        return arr;
    }

    int* rrn_insert(int* arr, int rrn, int len, string key, string* key_arr) {
        int index = find_index(key_arr, key, len);
        for (int i = len; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = rrn;
        return arr;
    }

    Node** child_insert(Node** child_arr, Node* child, int len, int index) {
        for (int i = len; i > index; i--) {
            child_arr[i] = child_arr[i - 1];
        }
        child_arr[index] = child;
        return child_arr;
    }

    Node* child_item_insert(Node* node, string data, Node* child) {
        int item_index = 0;
        int child_index = 0;
        for (int i = 0; i < node->size; i++) {
            if (data < node->item[i]) {
                item_index = i;
                child_index = i + 1;
                break;
            }
            if (i == node->size - 1) {
                item_index = node->size;
                child_index = node->size + 1;
                break;
            }
        }
        for (int i = node->size; i > item_index; i--) {
            node->item[i] = node->item[i - 1];
        }
        for (int i = node->size + 1; i > child_index; i--) {
            node->children[i] = node->children[i - 1];
        }

        node->item[item_index] = data;
        node->children[child_index] = child;
        return node;
    }

    void InsertPar(Node* par, Node* child, string data) {
        Node* cursor = par;
        if (cursor->size < this->degree - 1) {
            cursor = child_item_insert(cursor, data, child);
            cursor->size++;
        } else {
            auto* Newnode = new Node(this->degree);
            Newnode->parent = cursor->parent;

            string* item_copy = new string[cursor->size + 1];
            for (int i = 0; i < cursor->size; i++) {
                item_copy[i] = cursor->item[i];
            }
            item_copy = item_insert(item_copy, data, cursor->size);

            auto** child_copy = new Node*[cursor->size + 2];
            for (int i = 0; i < cursor->size + 1; i++) {
                child_copy[i] = cursor->children[i];
            }
            child_copy[cursor->size + 1] = nullptr;
            child_copy = child_insert(child_copy, child, cursor->size + 1, find_index(item_copy, data, cursor->size + 1));

            cursor->size = (this->degree) / 2;
            if ((this->degree) % 2 == 0) {
                Newnode->size = (this->degree) / 2 - 1;
            } else {
                Newnode->size = (this->degree) / 2;
            }

            for (int i = 0; i < cursor->size; i++) {
                cursor->item[i] = item_copy[i];
                cursor->children[i] = child_copy[i];
            }
            cursor->children[cursor->size] = child_copy[cursor->size];

            for (int i = 0; i < Newnode->size; i++) {
                Newnode->item[i] = item_copy[cursor->size + i + 1];
                Newnode->children[i] = child_copy[cursor->size + i + 1];
                Newnode->children[i]->parent = Newnode;
            }
            Newnode->children[Newnode->size] = child_copy[cursor->size + Newnode->size + 1];
            Newnode->children[Newnode->size]->parent = Newnode;

            string paritem = item_copy[this->degree / 2];
            delete[] item_copy;
            delete[] child_copy;

            if (cursor->parent == nullptr) {
                auto* Newparent = new Node(this->degree);
                cursor->parent = Newparent;
                Newnode->parent = Newparent;
                Newparent->item[0] = paritem;
                Newparent->size++;
                Newparent->children[0] = cursor;
                Newparent->children[1] = Newnode;
                this->root = Newparent;
            } else {
                InsertPar(cursor->parent, Newnode, paritem);
            }
        }
    }

    void insert(string key, int rrn) {
        if (this->root == nullptr) {
            this->root = new Node(this->degree);
            this->root->is_leaf = true;
            this->root->item[0] = key;
            this->root->rrns[0] = rrn;
            this->root->size = 1;
        } else {
            Node* cursor = this->root;
            cursor = BPlusTreeRangeSearch(cursor, key);

            if (cursor->size < (this->degree - 1)) {
                cursor->rrns = rrn_insert(cursor->rrns, rrn, cursor->size, key, cursor->item);
                cursor->item = item_insert(cursor->item, key, cursor->size);
                cursor->size++;
                cursor->children[cursor->size] = cursor->children[cursor->size - 1];
                cursor->children[cursor->size - 1] = nullptr;
            } else {
                auto* Newnode = new Node(this->degree);
                Newnode->is_leaf = true;
                Newnode->parent = cursor->parent;

                string* item_copy = new string[cursor->size + 1];
                int* rrn_copy = new int[cursor->size + 1];
                for (int i = 0; i < cursor->size; i++) {
                    item_copy[i] = cursor->item[i];
                    rrn_copy[i] = cursor->rrns[i];
                }

                rrn_copy = rrn_insert(rrn_copy, rrn, cursor->size, key, item_copy);
                item_copy = item_insert(item_copy, key, cursor->size);

                cursor->size = (this->degree) / 2;
                if ((this->degree) % 2 == 0) {
                    Newnode->size = (this->degree) / 2;
                } else {
                    Newnode->size = (this->degree) / 2 + 1;
                }

                for (int i = 0; i < cursor->size; i++) {
                    cursor->item[i] = item_copy[i];
                    cursor->rrns[i] = rrn_copy[i];
                }
                for (int i = 0; i < Newnode->size; i++) {
                    Newnode->item[i] = item_copy[cursor->size + i];
                    Newnode->rrns[i] = rrn_copy[cursor->size + i];
                }

                Newnode->children[Newnode->size] = cursor->children[this->degree - 1];
                cursor->children[cursor->size] = Newnode;
                cursor->children[this->degree - 1] = nullptr;

                delete[] item_copy;
                delete[] rrn_copy;

                string paritem = Newnode->item[0];
                if (cursor->parent == nullptr) {
                    auto* Newparent = new Node(this->degree);
                    cursor->parent = Newparent;
                    Newnode->parent = Newparent;
                    Newparent->item[0] = paritem;
                    Newparent->size++;
                    Newparent->children[0] = cursor;
                    Newparent->children[1] = Newnode;
                    this->root = Newparent;
                } else {
                    InsertPar(cursor->parent, Newnode, paritem);
                }
            }
        }
    }

    void clear(Node* cursor) {
        if (cursor != nullptr) {
            if (!cursor->is_leaf) {
                for (size_t i = 0; i <= cursor->size; i++) {
                    clear(cursor->children[i]);
                }
            }
            delete cursor;
        }
    }

    void bpt_print() { print(this->root); }

    void print(Node* cursor) {
        if (cursor != nullptr) {
            for (int i = 0; i < (int)cursor->size; ++i) {
                cout << cursor->item[i];
                if(cursor->is_leaf) cout << "(RRN:" << cursor->rrns[i] << ")";
                cout << " ";
            }
            cout << "\n";
            if (!cursor->is_leaf) {
                for (int i = 0; i < (int)cursor->size + 1; ++i) {
                    print(cursor->children[i]);
                }
            }
        }
    }
};

#endif

