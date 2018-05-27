#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin;
    ofstream out;
    fin.open("stack.in");
    out.open("stack.out");
    //fin.open("input.txt");
    //out.open("output.txt");
    int m;
    fin >> m;
    vector<int> stack;
    for (int i = 0; i < m; i++){
        string com;
        fin >> com;
        if (com == "+"){
            int x;
            fin >> x;
            stack.push_back(x);
        }else{
            out << stack.back() << endl;
            stack.pop_back();
        }
    }
    fin.close();
    out.close();
    return 0;
}