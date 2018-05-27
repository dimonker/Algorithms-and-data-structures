#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

void siftDown(vector<int> &arr, int i, int heapSize){
    int tmp = arr[i];
    while (2*i <= heapSize){
        int j = i * 2;
        if((j+1 <= heapSize) && (arr[j] < arr[j+1])){
            j++;
        }
        if(tmp >= arr[j])
            break;
        else{
            arr[i] = arr[j];
            i = j;
        }
    }
    arr[i] = tmp;
}

int main() {
    ifstream fin;
    ofstream out;
    fin.open("sort.in");
    out.open("sort.out");
    //fin.open("input.txt");
    //out.open("output.txt");

    int n;
    fin >> n;
    vector<int> arr;
    arr.resize(n+1);
    for (int i = 1; i <= n; i++){
        fin >> arr[i];
    }

    for (int i = n/2; i >= 1; i--){
        siftDown(arr, i, n);
    }

    int heapSize = n;
    for (int i = 0; i <= n-1; i++){
        swap(arr[1], arr[n - i]);
        heapSize--;
        siftDown(arr, 1, heapSize);
    }

    for(int i = 1; i <= n; i++){
        out << arr[i] << " ";
    }

    fin.close();
    out.close();
    return 0;
}