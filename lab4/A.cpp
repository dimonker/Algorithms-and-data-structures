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

int max(int a, int b){
    if (a > b)
        return a;
    else
        return b;
}

int height(Node* node){
    if (node->left == nullptr && node->right == nullptr)
        return 1;
    return max(node->left == nullptr ? 1 : height(node->left) + 1,
                node->right == nullptr ? 1 : height(node->right) + 1);
}

int main() {
    ifstream fin;
    ofstream out;
    fin.open("height.in");
    out.open("height.out");
    //fin.open("input.txt");
    //out.open("output.txt");
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
        out << height(tree[1]) << endl;
    }
    else out << 0 << endl;


    fin.close();
    out.close();
    return 0;
}