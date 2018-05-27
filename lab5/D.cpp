#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



class Tree{
public:
    string value;
    Tree* left;
    Tree* right;
    Tree():value(""), left(nullptr), right(nullptr){}
    Tree(string key):value(key), left(nullptr), right(nullptr){}

    void insert(string& x){
        insert_(this, x);
    }


    Tree* deleteNode(string& x){
        return deleteNode_(this, x);
    }

    vector<string> str;

    vector<string> getAllValue(Tree* tree){
        str.resize(0);
        getAllValue_(tree);
        return str;
    }

    void getAllValue_(Tree* tree){
        if (tree == nullptr)
            return;
        getAllValue_(tree->left);
        str.push_back(tree->value);
        getAllValue_(tree->right);
    }

private:
    Tree* insert_(Tree *tree, string x){
        if (tree == nullptr)
            tree = new Tree(x);
        else if (x < tree->value)
            tree->left = insert_(tree->left, x);
        else if (x > tree->value)
            tree->right = insert_(tree->right, x);
        return tree;
    }


    Tree* min_(Tree *node){
        if (node->left == nullptr)
            return node;
        return min_(node->left);
    }

    Tree* deleteNode_(Tree *node, string& x){
        if (node == nullptr)
            return node;
        if (x < node->value)
            node->left = deleteNode_(node->left, x);
        else if (x > node->value)
            node->right = deleteNode_(node->right, x);
        else if (node->left != nullptr && node->right != nullptr){
            node->value = min_(node->right)->value;
            node->right = deleteNode_(node->right, node->value);
        }else{
            if (node->left != nullptr)
                node = node->left;
            else
                node = node->right;
        }
        return node;
    }

};





class Map{
public:
    class Element{
    public:
        string key;
        Tree* tree;
        Element* next;
        Element(string key, string& value):key(key), next(nullptr){
            tree = new Tree(value);
        }
    };

    int maxSize = 17011;
    vector<Element*> table;

    Map(){
        table.resize(maxSize);
    }

    int hash(string &str){
        int mult = 367;
        int hash = 0;
        for (int i = 0; i < str.size(); i++){
            hash = (hash * mult + str[i]) % maxSize;
        }
        return hash;
    }

    void put(string& key, string& value) {
        Element* elem = search(key);
        if (elem != nullptr){
            elem->tree->insert(value);
            return;
        }
        int h = hash(key);
        Element* node = new Element(key, value);
        node->next = table[h];
        table[h] = node;
    }

    Element* search(string& key) {
        Element* elem = table[hash(key)];
        while (elem != nullptr){
            if (elem->key == key){
                return elem;
            }
            elem = elem->next;
        }
        return nullptr;
    }


    void deleteValue(string &key, string &value){
        int h = hash(key);
        Element* elem = table[h];
        Element* prevNode = nullptr;
        while(elem != nullptr){
            if (elem->key == key){
                elem->tree = elem->tree->deleteNode(value);
                if (elem->tree == nullptr){
                    if (prevNode == nullptr)
                        table[h] = elem->next;
                    else{
                        prevNode->next = elem->next;
                        elem->next = nullptr;
                    }
                }
                return;
            }
            if (elem->key == key){
                prevNode = elem;
            }
            elem = elem->next;
        }
    }

    void deleteAll(string& key){
        int h = hash(key);
        Element* elem = table[h];
        Element* prevNode = nullptr;
        while(elem != nullptr){
            if (elem->key == key){
                if (prevNode == nullptr)
                    table[h] = elem->next;
                else{
                    prevNode->next = elem->next;
                    elem->next = nullptr;
                }
            }
            if (elem->key == key){
                prevNode = elem;
            }
            elem = elem->next;
        }
    }

    vector<string> get(string& key){
        vector<string> str;
        Element* elem = table[hash(key)];
        while (elem != nullptr){
            if(elem->key == key){
                return elem->tree->getAllValue(elem->tree);
            }
            elem = elem->next;
        }
        return str;
    }



};

int main() {
    ifstream fin;
    ofstream out;
    fin.open("multimap.in");
    out.open("multimap.out");

    Map hashMap;

    while (!fin.eof()){
        string str, key, value;
        fin >> str;
        if (str == "put"){
            fin >> key >> value;
            hashMap.put(key, value);
        }
        else if (str == "get"){
            fin >> key;
            vector<string> getting = hashMap.get(key);
            out << getting.size();
            for (int i = 0; i < getting.size(); i++)
                out << " " << getting[i];
            out << endl;
        }
        else if (str == "delete"){
            fin >> key >> value;
            hashMap.deleteValue(key, value);
        }
        else if (str == "deleteall"){
            fin >> key;
            hashMap.deleteAll(key);
        }
    }

    fin.close();
    out.close();
    return 0;
}