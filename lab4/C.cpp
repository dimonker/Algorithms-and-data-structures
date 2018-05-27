#include <iostream>
#include <fstream>

using namespace std;

class Node{
public:
    int key;
    Node* left;
    Node* right;
    Node():key(0), left(nullptr), right(nullptr){}
    Node(int key):key(key), left(nullptr), right(nullptr){}
};

Node* insert(Node *tree, int x){
    if (tree == nullptr)
        tree = new Node(x);
    else if (x < tree->key)
        tree->left = insert(tree->left, x);
    else if (x > tree->key)
        tree->right = insert(tree->right, x);
    return tree;
}

bool exists(Node* tree, int x){
    if (tree->key == x)
        return true;
    if (x < tree->key && tree->left != nullptr)
        return exists(tree->left, x);
    if (x > tree->key && tree->right != nullptr)
        return exists(tree->right, x);
    return false;
}

Node* min(Node* node){
    if (node->left == nullptr)
        return node;
    return min(node->left);
}

Node* next(Node* node, int x){
    Node* nextNode = node;
    Node* answer = nullptr;
    while (nextNode != nullptr){
        if (x >= nextNode->key)
            nextNode = nextNode->right;
        else{
            answer = nextNode;
            nextNode = nextNode->left;
        }
    }
    return answer;
}

Node* prev(Node* node, int x){
    Node* prevNode = node;
    Node* answer = nullptr;
    while (prevNode != nullptr){
        if (x <= prevNode->key)
            prevNode = prevNode->left;
        else{
            answer = prevNode;
            prevNode = prevNode->right;
        }
    }
    return answer;
}

Node* deleteNode(Node* node, int x){
    if (node == nullptr)
        return node;
    if (x < node->key)
        node->left = deleteNode(node->left, x);
    else if (x > node->key)
        node->right = deleteNode(node->right, x);
    else if (node->left != nullptr && node->right != nullptr){
        node->key = min(node->right)->key;
        node->right = deleteNode(node->right, node->key);
    }else{
        if (node->left != nullptr)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

int main() {
    ifstream fin;
    ofstream out;
    fin.open("bstsimple.in");
    out.open("bstsimple.out");
    //fin.open("input.txt");
    //out.open("output.txt");

    Node* tree = nullptr;
    while(!fin.eof()){
        string str;
        int x;
        fin >> str >> x;
        if (str == "insert")
            tree = insert(tree, x);
        if (str == "exists")
            out << (tree != nullptr && (exists(tree, x)) ? "true" : "false")  << endl;
        if (str == "next"){
            Node* n = nullptr;
            n = next(tree, x);
            if (n != nullptr)
                out << n->key << endl;
            else
                out << "none" << endl;
        }
        if (str == "prev"){
            Node* n = nullptr;
            n = prev(tree, x);
            if (n != nullptr)
                out << n->key << endl;
            else
                out << "none" <<  endl;
        }
        if (str == "delete"){
            tree = deleteNode(tree, x);
        }

    }

    fin.close();
    out.close();
    return 0;
}