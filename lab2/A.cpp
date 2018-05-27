#include <iostream>
#include <fstream>

using namespace std;

void Merge(long *arr, int first, int mid, int last){
    int i = first;
    int j = mid;
    long tmp[last - first];

    for (int k = first; k < last; k++){
        if(j == last || (arr[i] < arr[j] && i < mid)){
            tmp[k - first] = arr[i];
            i++;
        }
        else{
            tmp[k - first] = arr[j];
            j++;
        }
    }
    for (int k = first; k < last; k++){
        arr[k] = tmp[k - first];
    }
}

void MergeSort(long *arr, int first, int last){
    if (first + 1 >= last)
        return;
    int mid = (first + last)/2;
    MergeSort(arr, first, mid);
    MergeSort(arr, mid, last);
    Merge(arr, first, mid, last);
}

int main() {
    ifstream fin;
    ofstream out;
    //fin.open("sort.in");
    //out.open("sort.out");
    fin.open("input.txt");
    out.open("output.txt");

    int n;
    fin >> n;
    long arr[n];

    for (int i = 0; i < n; i++){
        fin >> arr[i];
    }

    MergeSort(arr, 0, n);

    for (int i = 0; i < n; i ++ ){
        out << arr[i] << " ";
    }

    fin.close();
    out.close();
    return 0;
}