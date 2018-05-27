#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Map{
public:
    class Value{
    public:
        string key;
        string value;
        Value* next;
        Value(string key, string value):key(key), value(value), next(nullptr){}
    };

    int maxSize = 99817;
    vector<Value*> table;

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
        Value* x = search(key);
        if (x != nullptr){
            x->value = value;
            return;
        }
        int h = hash(key);
        Value* node = new Value(key, value);
        node->next = table[h];
        table[h] = node;
    }

    Value* search(string& key) {
        Value* node = table[hash(key)];
        while (node != nullptr){
            if (node->key == key){
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }


    void deleteKey(string& key){
        int h = hash(key);
        Value* node = table[h];
        Value* prevNode = nullptr;
        while(node != nullptr){
            if (node->key == key){
                if (prevNode == nullptr)
                    table[h] = node->next;
                else{
                    prevNode->next = node->next;
                    node->next = nullptr;
                }
                return;
            }
            prevNode = node;
            node = node->next;
        }
    }

    std::string get(string& key){
        Value* node = search(key);
        return ((node == nullptr) ? "none" : node->value);
    }

};

int main() {
    ifstream fin;
    ofstream out;
    fin.open("map.in");
    out.open("map.out");

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
            out << hashMap.get(key) << endl;
        }
        else if (str == "delete"){
            fin >> key;
            hashMap.deleteKey(key);
        }
    }

    fin.close();
    out.close();
    return 0;
}