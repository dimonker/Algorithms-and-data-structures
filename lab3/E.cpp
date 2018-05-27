#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin;
    ofstream out;
    //fin.open("isheap.in");
    //out.open("isheap.out");
    fin.open("input.txt");
    out.open("output.txt");

    int n;
    fin >> n;
    int arr[n + 1];
    for (int i = 1; i <= n; i++){
        fin >> arr[i];
    }
    bool flag = true;
    for (int i = 1; i <= n/2; i++){
        if (!(arr[i] <= arr[2*i])){
            flag = false;
            break;
        }
        if (!(arr[i] <= arr[2*i + 1]) && 2*i + 1 <= n){
            flag = false;
            break;
        }
    }
    out << (flag ? "YES" : "NO");
    fin.close();
    out.close();
    return 0;
}