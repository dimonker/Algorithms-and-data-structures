#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Set{
public:
    class Value{
    public:
        int key;
        Value* next;
        Value(int key):key(key), next(nullptr){}
    };

    int maxSize = 99817;
    vector<Value*> table;

    Set(){
        table.resize(maxSize);
    }

    int hash(int key){
        return abs(key) % maxSize;
    }

    void insert(int key) {
        if (exist(key))
            return;
        int h = hash(key);
        Value* node = new Value(key);
        node->next = table[h];
        table[h] = node;
    }

    Value* search(int key) {
        Value* node = table[hash(key) % maxSize];
        while(node != nullptr){
            if (node->key == key)
                return node;
            node = node->next;
        }
        return nullptr;
    }


    void deleteVal(int key){
        int h = hash(key);
        Value* node = table[h];
        Value* prevNode = nullptr;
        while(node != nullptr){
            if (node->key == key){
                if (prevNode == nullptr)
                    table[h] = node->next;
                else {
                    prevNode->next = node->next;
                    node->next = nullptr;
                }
                return;
            }
            prevNode = node;
            node = node->next;
        }
    }

    bool exist(int key) {
        return (search(key) != nullptr);
    }

};

int main() {
    ifstream fin;
    ofstream out;
    fin.open("set.in");
    out.open("set.out");

    Set set;

    while (!fin.eof()){
        string str;
        int x;
        fin >> str >> x;
        if (str == "insert"){
            set.insert(x);
        }
        else if (str == "delete"){
            set.deleteVal(x);
        }
        else if (str == "exists"){
            out << ((set.exist(x)) ? "true" : "false") << endl;
        }
    }

    fin.close();
    out.close();
    return 0;
}