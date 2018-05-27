#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class LinkedMap{
public:
    class Value{
    public:
        string key;
        string value;
        Value* next;
        Value* after;
        Value* before;
        Value(string key, string value, Value* before, Value* after):key(key),
                                                                      value(value),
                                                                      next(nullptr),
                                                                      after(after),
                                                                      before(before){}
    };

    int maxSize = 99817;
    vector<Value*> table;
    Value* header;

    LinkedMap(){
        table.resize(maxSize);
        header = new Value("none", "none", nullptr, nullptr);
        header->before = header;
        header->after = header;
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
        Value* node = new Value(key, value, header->before, header);
        header->before->after = node;
        node->next = table[h];
        table[h] = node;
        header->before = node;
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
                node->after->before = node->before;
                node->before->after = node->after;
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

    string get(string& key){
        Value* node = search(key);
        return ((node == nullptr) ? "none" : node->value);
    }

    string next(string& key){
        Value* node = search(key);
        return ((node == nullptr) ? "none" : node->after->value);
    }

    string prev(string& key){
        Value* node = search(key);
        return ((node == nullptr) ? "none" : node->before->value);
    }

};

int main() {
    ifstream fin;
    ofstream out;
    fin.open("linkedmap.in");
    out.open("linkedmap.out");

    LinkedMap linkedMap;

    while (!fin.eof()){
        string str, key, value;
        fin >> str;
        if (str == "put"){
            fin >> key >> value;
            linkedMap.put(key, value);
        }
        else if (str == "get"){
            fin >> key;
            out << linkedMap.get(key) << endl;
        }
        else if (str == "delete"){
            fin >> key;
            linkedMap.deleteKey(key);
        }
        else if (str == "prev"){
            fin >> key;
            out << linkedMap.prev(key) << endl;
        }
        else if (str == "next"){
            fin >> key;
            out << linkedMap.next(key) << endl;
        }
    }

    fin.close();
    out.close();
    return 0;
}