#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node{
public:
    int key;
    Node* left;
    Node* right;
    Node(){
        key = NULL;
        left = nullptr;
        right = nullptr;
    }
};



bool check(Node* node, int min, int max){
    if (node == nullptr){
        return true;
    }

    if (node->key <= min || node->key >= max)
        return false;

    return (check(node->left, min, node->key) &&
            check(node->right, node->key , max));
}

int main() {
    ifstream fin;
    ofstream out;
    //fin.open("check.in");
    //out.open("check.out");
    fin.open("input.txt");
    out.open("output.txt");
    int n, x, l, r;
    fin >> n;
    if (n != 0){
        vector<Node*> tree;
        tree.resize(n+1);
        for (int i = 0; i <= n; i++)
            tree[i] = new Node();

        for (int i = 1; i <= n; i++){
            fin >> x >> l >> r;
            tree[i]->key = x;
            if (l != 0){
                tree[i]->left = tree[l];
            }
            if (r != 0){
                tree[i]->right = tree[r];
            }
        }
        out << ((check(tree[1], -1000000001, 1000000001)) ? "YES" : "NO") << endl;
    }
    else out << "YES" << endl;


    fin.close();
    out.close();
    return 0;
}