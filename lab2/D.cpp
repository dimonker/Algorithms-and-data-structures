#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



void Antiqs(int *arr, int n){
    int tmp;
    for (int i = 0; i < n; i++){
        tmp = arr[i];
        arr[i] = arr[i/2];
        arr[i/2] = tmp;
    }
}

int main() {
    ifstream fin;
    ofstream out;
    fin.open("antiqs.in");
    out.open("antiqs.out");
    //fin.open("input.txt");
    //out.open("output.txt");
    int n;
    fin >> n;
    int arr[n];

    for (int i = 0; i < n; i++){
        arr[i] = i + 1;
    }

    Antiqs(arr, n);

    for (int i = 0; i < n; i++){
        out << arr[i] << " ";
    }

    fin.close();
    out.close();
    return 0;
}