#include <iostream>
#include <fstream>
#include <queue>


using namespace std;

int main() {
    ifstream fin;
    ofstream out;
    fin.open("queue.in");
    out.open("queue.out");
    //fin.open("input.txt");
    //out.open("output.txt");
    int m;
    fin >> m;
    queue<int> myQueue;
    for (int i = 0; i < m; i++){
        string com;
        fin >> com;
        if (com == "+"){
            int x;
            fin >> x;
            myQueue.push(x);
        }else{
            out << myQueue.front() << endl;
            myQueue.pop();
        }
    }
    fin.close();
    out.close();
    return 0;
}