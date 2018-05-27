#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int binsearchLeft(vector<int> &arr, int x){
    int left = 0;
    int right = arr.size();
    while (left < right){
        int middle = (left + right)/2;
        if (arr[middle] < x)
            left = middle + 1;
        else
            right = middle;
    }
    return arr[left] == x ? left + 1 : -1;
};

int binsearchRight(vector<int> &arr, int x){
    int left = 0;
    int right = arr.size();
    while(left < right){
        int middle = (left+right)/2;
        if (x < arr[middle])
            right = middle;
        else
            left = middle + 1;
    }
    return arr[left - 1] == x ? left : -1;
}

int main() {
    fstream fin;
    ofstream out;
    fin.open("binsearch.in");
    out.open("binsearch.out");
    //fin.open("input.txt");
    //out.open("output.txt");

    int n;
    fin >> n;
    vector<int> arr;
    arr.resize(n);
    for (int i = 0; i < n; i++){
        fin >> arr[i];
    }
    int m;
    fin >> m;
    for (int i = 1; i <= m; i++){
        int x;
        fin >> x;
        out << binsearchLeft(arr, x) <<" " << binsearchRight(arr, x) << endl;
    }
    fin.close();
    out.close();
    return 0;
}